#include <string>
#include <iostream>
#include <soci/soci.h>
#include <memory>
#include "db_connection.hpp"
#include "libmenu.hpp"
#include "person.hpp"

using Db::Connect;
using Db::DataFromBD;

Person::Person(std::shared_ptr<Connect> conn, int idperson):DataFromBD(conn){
/* С помощью данного конструктора заполняются поля объекта данными
 * полученными из базы данных.
 * Если соответствующей идентификатору записи в базе данных нет, то полю
 * m_idperson присваивается значение -1, что соответствует невалидности
 * соответсвующего объекта */
	//if (conn.open()){
		//std::cout << "Working Person(Connect &, int)\n";
		if (m_ses){
			try {
			(*m_ses) << "SELECT idperson, family, name, parent FROM persons WHERE idperson = " << 
				idperson, soci::into(m_idperson), soci::into(m_family), soci::into(m_name), soci::into(m_parent);
			}
			catch (std::exception const & e) {
				std::cerr << "ses = " << m_ses << std::endl;
				std::cerr << "From Person() " << e.what() << std::endl; 
			}
		}
	//}
}

/* С помощью данного конструктора заполняются поля объекта класса,
 * одновременно создается соответсвующая запись в таблице базы данных */
/*Person::Person(Connect &conn, string family, string name, string parent):
	m_conn(std::make_shared<Connect>(conn)),
	m_idperson{-1}, m_family{family}, m_name{name}, m_parent{parent} {
	soci::session *ses = conn.getSession();
}*/

int Person::displayPerson(bool with_id) {
	using ConsoleMenu::Menu;
	using ConsoleMenu::Item;
	using ConsoleMenu::Pager;

	m_with_id  = with_id;
	int result = 1;
	std::cout << *this;
	Menu menu_person("----------- Действия ----------");
	Item members_item("Семья");
	//members_item.setAction(std::bind(&Person::_getMembersFamily, std::placeholders::_1));
	std::vector<int> vec_results(10);
	members_item.setAction(
            [&](std::string str){
                //std::string result;
                (*m_ses) << "SELECT id_member from members WHERE cod_person =" << 
                                m_idperson, soci::into(vec_results);
            }
    );
	Item actions_item("Карьера");
	//actions_item.setAction(&Person::_getActions);
	Item learn_item("Учеба");
	//learn_item.setAction(_getLearn);
	menu_person.addItem(members_item);
	menu_person.addItem(actions_item);
	menu_person.addItem(learn_item);
	Pager person_pager(&menu_person);
	std::cout << person_pager.exec(Pager::ACTION, false) << std::endl;
	return result;
}

void Person::_getMembersFamily(std::string) const{
}

void Person::_getActions(std::string) const{
}

void Person::_getLearn(std::string) const{
}

std::ostream & operator <<(std::ostream & out, const Person & person){
	if (person.m_with_id) {
		out << "(" << person.m_idperson << ") ";
	}
	out << person.m_family << " " << person.m_name << " " << person.m_parent << std::endl;
	return out;
}

