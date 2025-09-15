#include <string>
#include <iostream>
#include <soci/soci.h>
#include <memory>
#include "db_connection.hpp"
#include "person.hpp"

using Db::Connect;

Person::Person(std::shared_ptr<Connect> conn, int idperson):
	m_conn(conn){
/* С помощью данного конструктора заполняются поля объекта данными
 * полученными из базы данных.
 * Если соответствующей идентификатору записи в базе данных нет, то полю
 * m_idperson присваивается значение -1, что соответствует невалидности
 * соответсвующего объекта */
	//if (conn.open()){
		soci::session *ses = conn->getSession();
		std::cout << "Working Person(Connect &, int)\n";
		if (ses){
			try {
			(*ses) << "SELECT family, name, parent FROM persons WHERE idperson = " << 
				idperson, soci::into(m_family), soci::into(m_name), soci::into(m_parent);
			}
			catch (std::exception const & e) {
				std::cerr << "ses = " << ses << std::endl;
				std::cerr << "From Person() " << e.what() << std::endl; 
			}
		}
	//}
}

Person::Person(Connect &conn, string family, string name, string parent):
	m_conn(std::make_shared<Connect>(conn)),
	m_idperson{-1}, m_family{family}, m_name{name}, m_parent{parent} {
	/* С помощью данного конструктора заполняются поля объекта класса,
	 * одновременно создается соответсвующая запись в таблице базы данных */
	soci::session *ses = conn.getSession();
}

int Person::displayPerson() const {
	int result;
	std::cout << m_family << " " << m_name << " " << m_parent << std::endl;
	return result;
}
