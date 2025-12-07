#pragma once 

#define SOCI_USE_BOOST
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/fusion/include/for_each.hpp"
#include <boost/lexical_cast.hpp>
#include <soci/soci.h>
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <chrono>
#include <ctime>
#include "db_connection.hpp"

using Db::Connect;
using Db::DataFromBD;
using boost::get;
using std::string;
using soci::rowset;

//std::ostream & operator << (std::ostream & out, const std::tm & data);

std::ostream & operator << (std::ostream & out, const std::tm & data){
		out << data.tm_mday << "." << data.tm_mon << "." << data.tm_year;
		return out;
	}

template <typename TypeField>
/* Шаблонный класс, предоставляющий возможность работы с результами выполнения
 * SQL-оператора, возвращающего набор однотипных данных типа TypeField */
class Many_Data : public DataFromBD {
public:
	Many_Data() = delete;
	Many_Data(std::shared_ptr<Connect> conn):DataFromBD(conn) {}
	Many_Data(std::shared_ptr<Connect> conn, string SQL_Select, const int):DataFromBD(conn) {
		//std::cout << "Constructor Many_Data(int)\n";
		rowset<int> result_query = (m_ses->prepare << SQL_Select);
		for (auto it = result_query.begin(); it != result_query.end(); ++it){
			m_content.push_back(*it);
		}
	}
	Many_Data(std::shared_ptr<Connect> conn, string SQL_Select, const string):DataFromBD(conn) {
		//std::cout << "Constructor Many_Data(string)\n";
		rowset<string> result_query = (m_ses->prepare << SQL_Select);
		for (auto it = result_query.begin(); it != result_query.end(); ++it){
			m_content.push_back(*it);
		}
	}
	Many_Data(std::shared_ptr<Connect> conn, string SQL_Select, const std::tm):DataFromBD(conn) {
		//std::cout << "Constructor Many_Data(std::tm)\n";
		rowset<std::tm> result_query = (m_ses->prepare << SQL_Select);
		for (auto it = result_query.begin(); it != result_query.end(); ++it){
			m_content.push_back(*it);
		}
		
	}
	friend std::ostream & operator << (std::ostream & out, const Many_Data<TypeField> & data){
		out << "Content:\n";
		for (auto it = data.m_content.begin(); it != data.m_content.end(); ++it){
			out << boost::lexical_cast<string>(*it);
			if (it < (data.m_content.end() - 1))
				out <<  ", ";
		}
		//out << *it;
		out << std::endl;
		return out;
	}
private:
	std::vector<TypeField> m_content;
};
