#pragma once 

#define SOCI_USE_BOOST
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/fusion/include/for_each.hpp"
#include <boost/lexical_cast.hpp>
#include <soci/soci.h>
#include <array>
#include <memory>
#include "db_connection.hpp"

using Db::Connect;
using Db::DataFromBD;
//using boost::tuple_size;
using boost::get;

struct Joined {
	/* Функтор, который применяется к boost:tuple с помощью функции for_each, 
	 * объединяя все его члены с помощью пробела */
	explicit Joined(std::string &res, const std::string*, const int);
	template <typename T>
	void operator()(const T &input){
		m_result += boost::lexical_cast<std::string>(input)+ ' ';
	}
private: 
	// Этот член будет модифицироваться в операторе operator()
	std::string & m_result;
};

struct Quoted {
	/* Функтор, который применяется к boost:tuple с помощью функции for_each, 
	 * и делает из него строку такую что, каждый из его членов, если это  строка
	 * или дата заключается в одинарные кавычки, а числа в кавычки не заключаются.
	 * При этом все члены в результирующей строке разделяются запятыми */
	explicit Quoted(std::string &res,const std::string*, const int);	//template <typename T>
	void operator()(const std::string &input);
	void operator()(const std::tm &input);
	void operator()(const int &input);
private: 
	// Этот член будет модифицироваться в операторе operator()
	std::string & m_result;
};

struct Pairs_Field_Value {
	/* Функтор, который применяется к boost:tuple с помощью функции for_each, 
	 * и делает из него строку такую что, каждый из его членов, если это  строка
	 * или дата заключается в одинарные кавычки, а числа в кавычки не заключаются.
	 * При этом образуются пары, состоящие из имен полей соединенных со значениями
	 * знаками '=', все эти пары в результирующей строке разделяются запятыми */
	explicit Pairs_Field_Value(std::string &res, const std::string *fields, const int numberfilds);
	void operator()(const std::string &input);
	void operator()(const std::tm &input);
	void operator()(const int &input);
private:
	std::string & m_result;
	const std::string *m_fields;
	const int m_numberfields;
	int m_current_field;
};

/*template <typename T>
std::string quote(T &input) {
	return boost::lexical_cast<std::string>(input);
}

template <>
std::string quote<std::string>(std::string &input) {
	return '\"' + input + '\"';
}*/

template <typename Sequence, typename Functor>
std::string tuple_to_string(const Sequence &seq, const std::string *fields = nullptr, const int numberfilds = 0){
	std::string result, tmp_result;
	Functor functor(tmp_result, fields, numberfilds);
	boost::fusion::for_each(seq, functor); 
	result = tmp_result.substr(0, tmp_result.rfind(','));
	tmp_result = std::move(result);
	result = tmp_result.substr(0, tmp_result.rfind(" AND "));
	return result;
}

template <typename TupleData>
class One_Data : public DataFromBD {
public:
	One_Data(std::shared_ptr<Connect> conn):DataFromBD(conn) {}
	One_Data(std::shared_ptr<Connect> conn, const std::string &SQL, const int idrecord):DataFromBD(conn),
	/* Конструктор заполняет член класса m_tuple_contents данными полученными из запроса 
	 * SQL. Члену m_id_record присваивается значение идентификатора, по которому получены
	 * данные запросом к БД. */
	m_id_record(idrecord){
		m_tuple_contents = get_tuple_from_SQL<TupleData>(SQL + boost::lexical_cast<std::string>(idrecord));
	}
	One_Data(std::shared_ptr<Connect> conn, const std::string &name_table, const TupleData &contents,
		const std::string *fields, const size_t number_fields, const bool insert_record_on_BD = true)
				:DataFromBD(conn), m_id_record(-1),m_tuple_contents(contents) {
	/* Конструктор создает объект заполняя m_tuple_contents параметрами конструктора. Затем 
	 * проверяет, есть ли такая запись в базе данных. И, если нет, и insert_record_on_BD == true,
	 * добавляет такую запись в базу данных, присваивая m_id_record значение идентификатора записи 
	 */
		std::ostringstream SelectSQL;
		SelectSQL << //"SELECT " << get_commastring_from_array(fields, number_fields) << " FROM " << name_table; 
					 get_SQL_for_idrecord(name_table, contents, fields, number_fields);
		std::cout << "SelectSQL = " << SelectSQL.str() << std::endl;
		m_id_record = boost::get<0>(get_tuple_from_SQL<boost::tuples::tuple<int> >(SelectSQL.str()));
		if (m_result_SQL > 0) {
			std::cout << "m_id_record = " << m_id_record << std::endl;
		}
		else {
			if (insert_record_on_BD){
				std::ostringstream InsertSQL;
				InsertSQL << "INSERT into " << name_table << " (" << 
					get_commastring_from_array(fields, number_fields) << ") VALUES" <<
					"(" << tuple_to_string<TupleData, Quoted>(contents) << ")";
				std::cout << "InsertSQL = " << InsertSQL.str() << std::endl;
				get_tuple_from_SQL<boost::tuples::tuple<int> >(InsertSQL.str());
				m_id_record = boost::get<0>(get_tuple_from_SQL<boost::tuples::tuple<int> >(SelectSQL.str()));
			}
			else{
				m_id_record = -1;
			}
			std::cout << "m_result_SQL = " << m_result_SQL << "; ";
			std::cout << "m_id_record = " << m_id_record << std::endl;
		}
	}

	One_Data(const One_Data & data) = default;
	One_Data(One_Data && data) = default;
	void displayContent() const {
		std::cout << *this;
	}
	int getId() const {return m_id_record;}
	void setShowID(bool with_id = true) {m_with_id = with_id;}
	friend std::ostream & operator << (std::ostream & out, const One_Data<TupleData> & data){
		if (data.m_with_id) {
			out << "(" << data.m_id_record << ") ";
		}
		out << tuple_to_string<TupleData, Joined>(data.m_tuple_contents);
		out << std::endl;
		return out;
	};
private:
	int m_id_record;
	//std::string m_Base_SQL;
	//std::string m_Insert_SQL;
	TupleData m_tuple_contents;
	bool m_with_id = false;
	int m_result_SQL;
	template<typename T>
	T get_tuple_from_SQL(const std::string & SQL){
	/* Возвращает boost::tuple с результатами запроса */
		T result;
		if (m_ses){
			soci::indicator ind;
			try {
				(*m_ses) << SQL, soci::into(result, ind);
				if (m_ses->got_data()){
					switch (ind) {
						case soci::i_ok:
							m_result_SQL = 1;
							break;
						case soci::i_null:
							m_result_SQL = 0;
							break;
						case soci::i_truncated:
							break;
					}
				}
				else {
					m_result_SQL = -1;
					//std::cout << "record is not found!\n";
				}
			}
			catch (std::exception const & e) {
				m_result_SQL = -2;
				std::cerr << "ses = " << m_ses << std::endl;
				std::cerr << "From get_tuple_from_SQL() " << e.what() << std::endl; 
			}
		}
		return result;
	}
	std::string get_commastring_from_array(const std::string *c_array, const size_t number){
	/* Возвращается строка разделенная запятыми из С-шного массива std::string */
		std::ostringstream ListFields;
		for (size_t i = 0; i < number; ++i){
			ListFields << c_array[i] << (i + 1 == number?"":", ");
		}
		return ListFields.str();
	}

	std::string get_SQL_for_idrecord(const std::string &name_table, 
				const TupleData &contents, const std::string *fields, size_t number_fields){
		if (number_fields > 0) {
			std::ostringstream stream_SQL;
			std::string name_field_primary_key = "id"+name_table.substr(0, name_table.rfind('s'));
			stream_SQL << "SELECT " << name_field_primary_key << " FROM " << name_table << " WHERE ";
			stream_SQL << tuple_to_string<TupleData, Pairs_Field_Value>(m_tuple_contents, fields, number_fields);
			return stream_SQL.str();
		}
		else
			return std::string();
	}
};

