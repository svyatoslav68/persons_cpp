#ifndef _MENU_HPP
#define _MENU_HPP
/*****************************************************************************
 *****************  файл menu.hpp ********************************************
 ****************************************************************************/
#include <stack>
#include <vector>
/*#define SOCI_USE_BOOST
#include <soci/soci.h>
#include "connection.hpp"*/

namespace ConsoleMenu {

class Pager;
class Item;

class Menu {
public:
	Menu() = delete;
	Menu(const std::string name);
	Menu(const std::string name, std::vector<std::string> &content);
	//Menu(std::string name, socibd::Connection &con, std::string SQL);
	static std::stack<const Menu *> menuStack;
	void addItem(const Item& newitem, const int after = -1);
	void addSubMenu(const Menu& submenu, const int after = -1);
	~Menu();
	std::string getName() const {return m_string_name;}
	friend class Pager;
	//Item *getBeginItem() {return &(m_items->at(0));}
	static void enterMenu(const Menu *); // вход в меню, меню помещается на стек
	static const Menu* exitMenu(); // выход из меню, меню снимается со стека
	bool isActiveMenu(); // true, если на вершине menuStack есть меню
private:
	std::string m_string_name;
	unsigned int m_size;
	//Menu *m_parent;
	std::vector<Item> m_items;
};

}

#endif //_MENU_HPP
