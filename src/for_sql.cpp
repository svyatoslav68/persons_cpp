#include <iostream>
#include <string>
#include "for_sql.hpp"

Connector::Connector()
:m_typeserver("postgres"),m_host_name("localhost"),
		m_database_name(""),m_user_name(""),m_password(""){
		}

Connector::Connector(std::string _typeserver, std::string _host_name,
		std::string _database_name, std::string _user_name,
		std::string _password) :m_typeserver(_typeserver),
		m_host_name(_host_name), m_database_name(_database_name),
		m_user_name(_user_name), m_password(_password){
		}

void Connector::method() {
	std::cout << "method" << std::endl;
}
