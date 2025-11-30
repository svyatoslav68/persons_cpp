#include <string>
#include <iostream>
#include <memory>
#define SOCI_USE_BOOST
#include <soci/soci.h>
#include <db_connection.hpp>
#include <boost/program_options.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include "libmenu.hpp"
#include "menu_persons.hpp"

using ConsoleMenu::Menu;
using ConsoleMenu::Item;
using ConsoleMenu::Pager;
 
namespace PersonsMenu {

void MenuPersons::m_ShowMembers(std::string caption){
}

void MenuPersons::m_ShowServe(std::string caption){
}

MenuPersons::MenuPersons(){
	using std::cin, std::cout, std::endl;
	using Db::Connect;
	m_mainMenu.addSubMenu(m_subMenuView);
	m_mainMenu.addSubMenu(m_subMenuEdit);
	m_person_pager.setMenu(&m_mainMenu);
}

MenuPersons::MenuPersons(const int id_person):MenuPersons(){
	m_id_person = id_person;
	Item view_members(std::string("Члены семьи"), m_id_person);
	view_members.setAction(m_ShowMembers); 
	Item view_serve(std::string("Карьера"), m_id_person);
	view_serve.setAction(m_ShowServe);
	m_subMenuView.addItem(view_members);
	m_subMenuView.addItem(view_serve);
}

std::string MenuPersons::exec(){
	return m_person_pager.exec(Pager::ACTION, false);
}

}
