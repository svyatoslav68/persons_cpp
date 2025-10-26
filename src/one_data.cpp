#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "one_data.hpp"

Quoting::Quoting(std::string &res):m_result(res){
	}

void Quoting::operator()(const std::string &input){
		m_result +=  '\"'+boost::lexical_cast<std::string>(input)+'\"'+',';
	}

void Quoting::operator()(const int &input){
		m_result +=  boost::lexical_cast<std::string>(input)+',';
	}
