#pragma once

using ConsoleMenu::Menu;
using ConsoleMenu::Item;
using ConsoleMenu::Pager;
 
namespace PrivateMenu {

class MenuPersons {
public:
	MenuPersons();
	MenuPersons(const int id_person);
	std::string exec();
private:
	int m_id_person;
	Menu m_mainMenu{std::string("Сотрудник")};
	Menu m_subMenuView{std::string("Просмотр")};
	Menu m_subMenuEdit{std::string("Редактирование")};
	Pager m_person_pager;
	// Actions for items MenuPersons
	static void m_ShowMembers(std::string caption);
	static void m_ShowServe(std::string caption);
};

class MenuMembers {
};

}
