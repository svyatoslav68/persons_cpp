#pragma once 

#define SOCI_USE_BOOST
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/fusion/include/for_each.hpp"
#include <boost/lexical_cast.hpp>
#include <soci/soci.h>
#include <iostream>
#include <iomanip>
#include <typeinfo>
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

inline std::ostream & operator << (std::ostream & out, const std::tm & data){
	out << std::setw(2) << std::right<< std::setfill('0') << data.tm_mday << "." 
		<< std::setw(2) << std::right << std::setfill('0') << data.tm_mon + 1 << "." 
		<< std::setw(4) 
		<< 1900+data.tm_year;
	return out;
}

enum class TypeDisplay {
	DISPLAY_ROW,
	DISPLAY_COLUMN
};

template <typename TypeField>
/* Шаблонный класс, предоставляющий возможность работы с результами выполнения
 * SQL-оператора, возвращающего набор однотипных данных типа TypeField */
class Many_Data : public DataFromBD {
public:
	Many_Data() = delete;
	Many_Data(std::shared_ptr<Connect> conn):DataFromBD(conn) {}
	/* Шаблонный конструктор класса. В результате заполняется полученными значениями
	 * вектор m_content */
	Many_Data(std::shared_ptr<Connect> conn, string SQL_Select, const TypeDisplay td,
			const TypeField var):DataFromBD(conn) {
		/*
		std::cout << "Conn = " << conn <<std::endl;
		std::cout << SQL_Select <<std::endl;
		*/
		m_td = td;
		rowset<TypeField> result_query = (m_ses->prepare << SQL_Select);
		int count_rows = 0;
		for (auto it = result_query.begin(); it != result_query.end(); ++it){
			++count_rows;
		}
		m_content.reserve(count_rows);
		result_query = (m_ses->prepare << SQL_Select);
		for (auto it = result_query.begin(); it != result_query.end(); ++it){
			//std::cout << *it << std::endl;
			m_content.push_back(*it);
		}
	}
	void setName(string name) {m_name = name;}
	bool operator == (const Many_Data<TypeField> & data) const {
		if (m_content.size() != data.m_content.size()){
			return false;
		}
		return (m_name == data.m_name) && 
			std::equal(m_content.begin(), m_content.end(), data.m_content.begin());
	}
	bool operator != (const Many_Data<TypeField> & data) const {
		return !operator==(data);
	}
	friend std::ostream & operator << (std::ostream & out, const Many_Data<TypeField> & data){
		out << "Content";
		if (!data.m_name.empty())
			out << " of " << data.m_name;
		out << ":\n";
		for (auto it = data.m_content.begin(); it != data.m_content.end(); ++it){
			out << boost::lexical_cast<string>(*it);
			if (it < (data.m_content.end() - 1)){
				if (data.m_td == TypeDisplay::DISPLAY_ROW)
					out <<  ", ";
				else
					out << "\n";
			}
		}
		//out << *it;
		out << std::endl;
		return out;
	}
private:
	std::vector<TypeField> m_content;
	string m_name;
	TypeDisplay m_td;
};
