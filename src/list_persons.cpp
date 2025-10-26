#include <vector>
#include <iostream>
#include <soci/soci.h>
#include "db_connection.hpp"
#include "person.hpp"
#include "list_persons.hpp"

using Db::Connect;
using Db::DataFromBD;

ListPersons::ListPersons(std::shared_ptr<Db::Connect> conn, int id_unit):DataFromBD(conn),
	m_idUnit{id_unit}{
	std::vector<int>::size_type count_records;
	(*m_ses) << "SELECT COUNT(idperson) FROM persons WHERE current_unit = " << id_unit, soci::into(count_records);	
	m_persons.resize(count_records);
	std::cout << "Кол-во сотрудников: " << count_records << std::endl;
	if (count_records) {
		(*m_ses) << "SELECT idperson FROM persons WHERE current_unit = " << id_unit, soci::into(m_persons);	
	}
}

/*
ListPersons::ListPersons(Db::Connect& conn, string SQL_query):
	m_conn{std::make_shared<Db::Connect>(conn)}, m_idUnit{-1}{
    soci::session *ses = conn.getSession();
	(*ses) << SQL_query, soci::into(m_persons);	
}
*/

int ListPersons::display_list(bool show_idperson) const {
	int result;
	int number = 0;
	for (int i: m_persons){
		Person member(m_conn, i);
		if (show_idperson) {
			std::cout << "(" << member.getIdPerson() << ")";
		} 
		else {
		std::cout << number++;
		}
		std::cout << ": " << member.getFamily() << " " << member.getName() << std::endl;
		//std::cout << number << ": " << i <<std::endl;
	}
	return result;
}
