#include <iostream>
#include <memory>
#include <soci/soci.h>
#include <db_connection.hpp>
#include <boost/program_options.hpp>
#include "list_persons.hpp"
#include "person.hpp"
#include "cli_options.hpp"
#include "unit.hpp"

using std::cin, std::cout, std::endl;
using Db::Connect;

int main(int argc, const char **argv){
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
			list.display_list();
	}
	else {
		// cout << "Unit name = " << root_unit.getName() << "\n" <<
		//     "sizeof(" << root_unit.getName() << ") = " << sizeof(root_unit) << endl;
		if (options.getIdPerson() > -1){
			cout << "Информация о ...:\n";
			Person person(conn, options.getIdPerson());
			person.displayPerson();
		}
		else {
			std::vector<int> symbols;
			//root_unit.setShowIdUnit(options.getShowIdUnit());
			cout << root_unit.display_children(symbols) << endl;
		}
	}
    conn->close();
}


