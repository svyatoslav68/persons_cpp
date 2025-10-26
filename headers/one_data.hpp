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

struct Quoting {
	explicit Quoting(std::string &res);	//template <typename T>
	void operator()(const std::string &input);
	void operator()(const int &input);
private: 
	// Этот член будет модифицироваться в операторе operator()
	std::string & m_result;
};

/*template <typename T>
std::string quote(T &input) {
	return boost::lexical_cast<std::string>(input);
}

template <>
std::string quote<std::string>(std::string &input) {
	return '\"' + input + '\"';
}*/

template <typename Sequence>
std::string tuple_to_string(const Sequence &seq){
	std::string result;
	boost::fusion::for_each(seq, Quoting(result)); 
	result.pop_back();
	return result;
}

template <typename TupleData>
class One_Data : DataFromBD {
public:
	One_Data(std::shared_ptr<Connect> conn):DataFromBD(conn) {}
	One_Data(std::shared_ptr<Connect> conn, const std::string &SQL, const int idrecord):DataFromBD(conn),
	/* Конструктор заполняет член класса m_tuple_contents данными полученными из запроса 
	 * SQL. Члену m_id_record присваивается значение идентификатора, по которому получены
	 * данные запросом к БД. */
	m_id_record(idrecord){
		m_tuple_contents = get_tuple_from_SQL(SQL + boost::lexical_cast<std::string>(idrecord));
	}
	One_Data(std::shared_ptr<Connect> conn, const std::string &name_table, const TupleData &contents,
		const std::string *fields, size_t number_fields)
				:DataFromBD(conn), m_id_record(-1),m_tuple_contents(contents) {
		std::ostringstream SelectSQL;
		SelectSQL << "SELECT " << get_commastring_from_array(fields, number_fields) << " FROM " << name_table; 
		std::ostringstream InsertSQL;
		InsertSQL << "INSERT into " << name_table << " (" << 
			get_commastring_from_array(fields, number_fields) << ") VALUES" <<
			boost::tuples::set_open('(') << boost::tuples::set_close(')') << 
			boost::tuples::set_delimiter(',') << contents;
		std::cout << "SelectSQL = " << SelectSQL.str() << std::endl;
		std::cout << "InsertSQL = " << InsertSQL.str() << std::endl;
	}

	One_Data(const One_Data & data) = default;
	void displayContent() const {
		std::cout << *this;
	}
	void setShowID(bool with_id = true) {m_with_id = with_id;}
	friend std::ostream & operator << (std::ostream & out, const One_Data<TupleData> & data){
		if (data.m_with_id) {
			out << "(" << data.m_id_record << ") ";
		}
		out << tuple_to_string(data.m_tuple_contents);
		out << std::endl;
		return out;
	};
private:
	int m_id_record;
	//std::string m_Base_SQL;
	//std::string m_Insert_SQL;
	TupleData m_tuple_contents;
	bool m_with_id = false;
	TupleData get_tuple_from_SQL(const std::string & SQL){
	/* Возвращает boost::tuple с результатами запроса */
		TupleData result;
		if (m_ses){
			try {
				(*m_ses) << SQL, soci::into(result);
				if (!m_ses->got_data()){
					m_id_record = -1;
					std::cout << "record is not found!\n";
				}
			}
			catch (std::exception const & e) {
				m_id_record = -1;
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

};

