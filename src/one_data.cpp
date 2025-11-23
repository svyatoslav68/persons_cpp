#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#include <boost/lexical_cast.hpp>
#include "one_data.hpp"

Joined::Joined(std::string &res, const std::string* fields=nullptr, const int number=0):
	m_result(res){
	}

Quoted::Quoted(std::string &res, const std::string* fields=nullptr, const int number=0):m_result(res){
	}

void Quoted::operator()(const std::string &input){
	m_result +=  '\''+boost::lexical_cast<std::string>(input)+'\''+',';
}

void Quoted::operator()(const std::tm &input){
	char str_date[11];
	if (std::strftime(str_date, 20, "%F", &input) > 11)
		std::strcpy(str_date, "Error");
	m_result +=  '\''+boost::lexical_cast<std::string>(str_date)+'\''+',';
}

void Quoted::operator()(const int &input){
	m_result +=  boost::lexical_cast<std::string>(input)+',';
}

Pairs_Field_Value::Pairs_Field_Value(std::string &res, const std::string *fields, 
		const int numberfilds):m_result(res),m_fields(fields),m_numberfields(numberfilds),
		m_current_field(0){
			//std::cout << "From Constructor:" << m_fields[2] <<std::endl;
}

void Pairs_Field_Value::operator()(const std::string &input){
	m_result +=  m_fields[m_current_field++]+'='+'\''+boost::lexical_cast<std::string>(input)+'\''+" AND ";
}

void Pairs_Field_Value::operator()(const std::tm &input){
	char str_date[30];
	if (std::strftime(str_date, 20, "%F", &input) > 11)
		std::strcpy(str_date, "Error");
	m_result +=  m_fields[m_current_field++]+'='+'\''+boost::lexical_cast<std::string>(str_date)+'\''+" AND ";
}

void Pairs_Field_Value::operator()(const int &input){
	m_result += m_fields[m_current_field++]+'='+boost::lexical_cast<std::string>(input)+" AND ";
}


