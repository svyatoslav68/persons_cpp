#include <iostream>
#include <soci/soci.h>
#include <db_connection.hpp>
#include <boost/program_options.hpp>
#include "cli_options.hpp"
#include "unit.hpp"

using std::cin, std::cout, std::endl;
using Db::Connect;

int main(int argc, const char **argv){
	CliOptions options(argc, argv);
	Connect conn(options.get_all_parametrs(), options.get_string_typeserver());
    if (conn.open()){
        cout << "Выполнено подключение к базе данных" << endl;
    }
	else{
		cout << "Подключение к базе данных не удалось.\n" 
			<< "Подключение выполнялось строками: "
			<< conn.getCommandConnect() 
            << "; "
            << conn.getStringTypeServer()
            << endl;
	}
    Unit root_unit(3, conn);
    cout << "Unit name = " << root_unit.getName() << "\n" <<
        "sizeof(" << root_unit.getName() << ") = " << sizeof(root_unit) << endl;
    std::vector<int> symbols;
    cout << root_unit.display_children(symbols) << endl;
    conn.close();
}


