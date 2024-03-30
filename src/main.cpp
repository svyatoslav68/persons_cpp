#include <iostream>
#include <soci/soci.h>
#include <db_connection.hpp>
#include <boost/program_options.hpp>
#include "cli_options.hpp"

using std::cin, std::cout, std::endl;

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
    conn.close();
}


