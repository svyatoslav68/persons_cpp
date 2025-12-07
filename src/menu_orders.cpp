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
#include "menu_orders.hpp"

using ConsoleMenu::Menu;
using ConsoleMenu::Item;
using ConsoleMenu::Pager;
 
namespace OrdersMenu {

MenuOrders::MenuOrders(){
	using std::cin, std::cout, std::endl;
	using Db::Connect;
	m_order_pager.setMenu(&m_mainMenu);
}

MenuOrders::MenuOrders(const int cod_person):MenuOrders(){
}

}

