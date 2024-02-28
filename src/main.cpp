#include <iostream>
#include <boost/program_options.hpp>
#include "from_boost.hpp"
#include "for_sql.hpp"

namespace po = boost::program_options;

int main(int argc, const char **argv){
Connector *db_connector = nullptr;
po::variables_map op_map = get_option(argc, argv); 

if (op_map.count("number") > 0){
	std::cout << "number = " << op_map["number"].as<int>() << std::endl;
}

if (op_map.count("sql-server")){
if (op_map["sql-server"].as<std::string>() == "none") {
}
else{
	    std::cout << "Type SQL server: " << op_map["sql-server"].as<std::string>() << std::endl;
	    if (op_map.count("sql-database-name"))
		std::cout << "Database name: " << op_map["sql-database-name"].as<std::string>() << std::endl;
	    if (op_map.count("username"))
		std::cout << "User name: " << op_map["username"].as<std::string>() << std::endl;
	    if (op_map.count("password"))
		std::cout << "Password: " << op_map["password"].as<std::string>() << std::endl;
	db_connector = new Connector();
    }
}
}


