#pragma once

using ConsoleMenu::Menu;
using ConsoleMenu::Item;
using ConsoleMenu::Pager;
 
namespace OrdersMenu {

class MenuOrders {
public:
	MenuOrders();
	MenuOrders(const int cod_person);
private:
	Pager m_order_pager;
	Menu m_mainMenu{std::string("Приказы:")};
};

}

