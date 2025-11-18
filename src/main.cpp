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
			One_Data<boost::tuple<string, string, string> > person{conn, string("SELECT family, name, parent FROM persons WHERE idperson = "), options.getIdPerson()};
			person.displayContent();
			Menu menu_person("----------- Действия ----------");
			Item members_item("Семья");
			//members_item.setAction(std::bind(&Person::_getMembersFamily, std::placeholders::_1));
			std::vector<int> vec_results(10);
			members_item.setAction(
					[&](std::string str){
						//std::string result;
						(*(person.getSession())) << "SELECT id_member from members WHERE cod_person =" << 
										person.getId(), soci::into(vec_results);
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
			cout << person_pager.exec(Pager::ACTION, false) << endl;
					/*Person person(conn, options.getIdPerson());
					person.displayPerson(options.getShowIdUnit());*/

				}
				else {
					std::vector<int> symbols;
					//root_unit.setShowIdUnit(options.getShowIdUnit());
					cout << root_unit.display_children(symbols) << endl;
				}
	}
    conn->close();
}


