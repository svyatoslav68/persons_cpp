/* Файл реализации функций предназначенных для проверки 
 * работоспособности библиотеки boost */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "from_boost.hpp"
#include "version.hpp"

namespace po = boost::program_options;

po::variables_map get_option(const int argc, const char *argv[]){
// Declare the supported options.
po::options_description desc("Allowed options");	
desc.add_options()
    ("help", "produce help message")
    ("number", po::value<int>(), "some integer value")
    ("sql-host", po::value<std::string>(), "sql-server hostname")
    ("sql-database-name", po::value<std::string>(), "name of database")
    ("username", po::value<std::string>(), "sql-server user name")
    ("password", po::value<std::string>(), "sql-server password")
    ("sql-server", po::value<std::string>(), "type sql-server")
    ("version", "version of application")
//   ("compression", po::value<int>(), "set compression level")
;
po::variables_map vm;
po::store(po::parse_command_line(argc, argv, desc), vm);
po::notify(vm);    

if (vm.count("help")) {
	std::cout << desc << "\n";
	exit(0);
}

if (vm.count("version")){
	std::cout << "version of " << argv[0] << " is " << g_version << std::endl;
	exit(0);
}

return vm;
}

