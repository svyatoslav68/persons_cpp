#pragma once
/********* Заголовочный файл для функций доступа к базам данных ***********
 * ************************************************************************/

class Connector {
private:
	std::string m_typeserver;
	std::string m_host_name;
	std::string m_database_name;
	std::string m_user_name;
	std::string m_password;
public:
	//Connector() delete;
	Connector();
	Connector(std::string _typeserver, std::string _host_name,
		std::string _database_name, std::string _user_name,
		std::string _password);
	void method();
};

