#include <iostream>
#include <memory>
#include <tuple>
#include <string>
#define SOCI_USE_BOOST
#include <soci/soci.h>
#include <db_connection.hpp>
#include <boost/program_options.hpp>
#include <boost/tuple/tuple.hpp>
#include "printtuple.hpp"
#include "one_data.hpp"
#include "many_data.hpp"
#include "cli_options.hpp"

using std::cin, std::cout, std::endl;
using std::tm;
using Db::Connect;

int main(int argc, const char **argv){
	using std::string;
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
	One_Data<boost::tuple<string, string> > person{conn, string("SELECT family, name FROM persons WHERE idperson = "), 1};
	person.setShowID(true);
	std::cout << person;
	One_Data<boost::tuple<int, int, string> > unit{conn, string("SELECT idunit, number, type FROM units WHERE idunit = "), 31};
	std::cout << unit;
	One_Data<boost::tuple<int, int, string> > std_unit{conn, string("SELECT idunit, number, type FROM units WHERE idunit = "), 31};
	string person_fields[4] = {string("family"), string("name"), string("parent"), string("current_unit")}; 
	boost::tuple<string, string, string, int> tuple_Zhuravlev = {string("Журавлев"), string("Дмитрий"), string("Витальевич"), 26};
	//std::tuple<string, string, string, int> std_tuple_Zhuravlev = {string("Журавлев"), string("Дмитрий"), string("Витальевич"), 26};
	One_Data<boost::tuple<string, string, string, int> > person_too = {conn, string("persons"), tuple_Zhuravlev, person_fields, 4}; 
	person_too.setShowID(true);
	std::cout << person_too;
	One_Data<boost::tuple<string, string, string, int> > person_zharov = {conn, string("persons"), boost::tuple<string, string, string, int>{string("Жаров"), string("Александр"), string("Владимирович"), 26}, person_fields, 4, false};//sizeof(person_fields)}; 
	person_zharov.setShowID();
	std::cout << person_zharov;
	One_Data<boost::tuple<string, string, string, int> > person_batenkov = {conn, string("persons"), boost::tuple<string, string, string, int>{string("Батенков"), string("Кирилл"), string("Александрович"), 31}, person_fields, 4};//sizeof(person_fields)}; 
	//std::tuple<string, string, string, int> std_tuple_Zhuravlev = boost::asStdTuple(tuple_Zhuravlev);
	//std::cout << "tuple_Zhuravlev: " << tuple_Zhuravlev << std::endl;
	//std::cout << "Copyed tuple_Zhuravlev: " << person_too << std::endl;
	//std::cout << "Family: " << boost::get<0>(tuple_Zhuravlev) << std::endl;
	
	/*
	One_Data<boost::tuple<string, string, string, int, tm> > person_date{conn, string("SELECT family, name, parent, current_unit, birthday FROM persons WHERE idperson = "), 6};
	cout << "Id Record = 6; " << person_date << std::endl;
	*/
	Many_Data<string> data_persons = {conn, string("SELECT family FROM persons")};
}

