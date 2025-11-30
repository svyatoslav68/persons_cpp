#include <iostream>
#include <memory>
#define SOCI_USE_BOOST
#include <soci/soci.h>
#include <db_connection.hpp>
#include <boost/program_options.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "list_persons.hpp"
#include "libmenu.hpp"
#include "one_data.hpp"
#include "person.hpp"
#include "cli_options.hpp"
#include "unit.hpp"
#include "menu_persons.hpp"

using std::cin, std::cout, std::endl;
using Db::Connect;

int main(int argc, const char **argv){
	using ConsoleMenu::Menu;
	using ConsoleMenu::Item;
	using ConsoleMenu::Pager;

	CliOptions options(argc, argv);
	std::shared_ptr<Connect> conn = std::make_shared<Connect>(options.get_all_parametrs(), options.get_string_typeserver());
    if (conn->open()){
        cout << "Выполнено подключение к базе данных" << endl;
    }
	else{
		cout << "Подключение к базе данных не удалось.\n" 
			<< "Подключение выполнялось строками: "
			<< conn->getCommandConnect() 
            << "; "
            << conn->getStringTypeServer()
            << endl;
	}
	Unit root_unit(options.getUnitId(), conn, options.getShowIdUnit());
	if (options.getIdPerson() == -1){
			cout << "Список л/с " << root_unit.getFullName() << ":" << std::endl;
			ListPersons list(conn, options.getUnitId());
			list.display_list(options.getShowIdUnit());
	}
	else {
		if (options.getIdPerson() > -1){
			cout << "Информация о ...:\n";
			if (options.getOrderOption()) {
				cout << "Карьера:\n";
			}
			else {
			One_Data<boost::tuple<string, string, string> > person{conn, 
				string("SELECT family, name, parent FROM persons WHERE idperson = "), 
					options.getIdPerson()};
			person.displayContent();
			PersonsMenu::MenuPersons menu_persons(options.getIdPerson());
			cout << menu_persons.exec() << endl;
			}
		}
		else {
			std::vector<int> symbols;
			cout << root_unit.display_children(symbols) << endl;
		}
	}
    conn->close();
}


