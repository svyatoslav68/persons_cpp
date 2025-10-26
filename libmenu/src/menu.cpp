#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <functional>
/*#define SOCI_USE_BOOST
#include <soci/soci.h>
#include "connection.hpp"*/
#include "item.hpp"
#include "pager.hpp"

namespace ConsoleMenu {

// Определение статической переменной-члена класса
std::stack<const Menu *> Menu::menuStack;

void Menu::enterMenu(const Menu *menu){
	menuStack.push(menu);
}

const Menu *Menu::exitMenu(){
	const Menu *result = nullptr;
	if (!menuStack.empty()) {
		//std::cout << "Size of stack = " << menuStack.size() << std::endl;
		/*Сначала извлекаем с верхушки стека сохраненное меню,
		 *затем продвигаем стек наверх */
		result = menuStack.top(); 
		menuStack.pop();
		//std::cout << "Size of stack = " << menuStack.size() << std::endl;
		//std::cout << "exitMenu() return " << result->getName() << "\n";
		return result;
	}
	else 
		return nullptr;
}

bool Menu::isActiveMenu(){
	return ! menuStack.empty();
}

//Menu::

Menu::Menu(std::string name):m_string_name(name),m_size(0){
	//m_items = new std::vector<Item>();
}

Menu::Menu(std::string name, std::vector<std::string> &content):Menu(name)
{
	for (std::string item: content) {
		m_items.push_back(item);
	}
	m_size = m_size+content.size();
}

/*Menu::Menu(std::string name, socibd::Connection &con, std::string SQL):Menu(name)
{
	std::vector<std::string> values_from_bd;
	values_from_bd = con.getColumn<std::string>(SQL);
	for (std::string item: values_from_bd) {
		m_items.push_back(item);
	}
	m_size = m_size+values_from_bd.size();
}
*/

void Menu::addItem(const Item& newitem, const int after){
	m_items.push_back(newitem);
	++m_size;
}

void Menu::addSubMenu(const Menu& submenu, const int after){
	//Item *newItem = new Item(submenu.getName(), &submenu);
	Item newItem(submenu.getName(), &submenu);
	addItem(newItem);
}

Menu::~Menu(){
	//delete m_items;
}

} // namespace
