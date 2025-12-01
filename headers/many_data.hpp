#pragma once 

#define SOCI_USE_BOOST
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/fusion/include/for_each.hpp"
#include <boost/lexical_cast.hpp>
#include <soci/soci.h>
#include <array>
#include <vector>
#include <memory>
#include "db_connection.hpp"

using Db::Connect;
using Db::DataFromBD;
using boost::get;
using std::string;

template <typename TypeField>
/* Шаблонный класс, предоставляющий возможность работы с результами выполнения
 * SQL-оператора, возвращающего набор однотипных данных типа TypeField */
class Many_Data : public DataFromBD {
public:
	Many_Data() = delete;
	Many_Data(std::shared_ptr<Connect> conn):DataFromBD(conn) {}
	Many_Data(std::shared_ptr<Connect> conn, string SQL_Select):DataFromBD(conn) {
		soci::rowset<TypeField> value = (m_ses->prepare << SQL_Select);
	}
private:
	std::vector<TypeField> m_content;
};
