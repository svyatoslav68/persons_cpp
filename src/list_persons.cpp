#include <vector>
#include <iostream>
#include <soci/soci.h>
#include "db_connection.hpp"
#include "person.hpp"
#include "list_persons.hpp"

ListPersons::ListPersons(std::shared_ptr<Db::Connect> conn, int id_unit):
	m_conn{conn}, m_idUnit{id_unit}{
    soci::session *ses = conn->getSession();
	std::vector<int>::size_type count_records;
	(*ses) << "SELECT COUNT(idperson) FROM persons WHERE current_unit = " << id_unit, soci::into(count_records);	
	m_persons.resize(count_records);
	std::cout << "Кол-во сотрудников: " << count_records << std::endl;
	(*ses) << "SELECT idperson FROM persons WHERE current_unit = " << id_unit, soci::into(m_persons);	
}

/*
ListPersons::ListPersons(Db::Connect& conn, string SQL_query):
	m_conn{std::make_shared<Db::Connect>(conn)}, m_idUnit{-1}{
    soci::session *ses = conn.getSession();
	(*ses) << SQL_query, soci::into(m_persons);	
}
*/

int ListPersons::display_list() const {
	int result;
	int number = 0;
	for (int i: m_persons){
		Person member(m_conn, i);
		std::cout << number++ << ": " << member.getFamily() << " " << member.getName() << std::endl;
		//std::cout << number << ": " << i <<std::endl;
	}
	return result;
}
