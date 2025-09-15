#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include "cli_options.hpp"
#include "version.hpp"

CliOptions::CliOptions(std::string name_file_settings):m_name_file_settings(name_file_settings),m_typeserver(CliOptions::PostgreSQL){
}

CliOptions::CliOptions(const int argc, const char *argv[], std::string name_file_settings):m_name_file_settings(name_file_settings),m_typeserver(CliOptions::PostgreSQL){
    po::options_description op_all("Allowed options");
    po::options_description op_common("Learn options of command line");	
    po::options_description op_db_server("Options of Database server");
    po::options_description op_units_options("Options for units");
	po::options_description op_persons_options("Options for person");
    po::options_description op_backend("Options for develop");
	op_common.add_options()
		("help,h", "show this message")
        ("version,v", "version of application")
    ;
    op_db_server.add_options()
        ("sql-server", po::value<std::string>(), "type sql-server (Postgres or MySQL)")
		("dbname", po::value<std::string>(&m_db_name), "name of database")
		("hostname,H", po::value<std::string>(&m_hostname), "name or address server host")
		("user,U", po::value<std::string>(&m_username), "username")
		("password,W", po::value<std::string>(&m_password), "password")
    ;
    op_units_options.add_options()
        ("unitid,u", po::value<int>(&m_id_unit), "id units")
		("showidunit", "show idunit")
    ;
	op_persons_options.add_options()
		("list-persons,l", "list of persons for unit")
		("personid,p", po::value<int>()->implicit_value(-1),
													"id_person")
	;
    op_all.add(op_common).add(op_db_server).add(op_backend).add(op_units_options).add(op_persons_options);
    po::options_description op_visible("Allowed options");
    op_visible.add(op_common).add(op_db_server).add(op_units_options).add(op_persons_options);
	po::positional_options_description pos_desc;
	pos_desc.add("dbname", 1);
	po::command_line_parser parser{argc, argv};
	parser.options(op_all);
	parser.positional(pos_desc);
	auto parsed_result = parser.run();
	po::store(parsed_result, m_vm);
	po::notify(m_vm);
	if (m_vm.count("help")){
			std::cout << op_visible << std::endl;
			exit(0);
	}   
    if (m_vm.count("version")){
        std::cout << "version of " << argv[0] << " is " << version << std::endl;
        exit(0);
    }
	/*
	if (!m_vm["dbname"].empty()){
		m_db_name = m_vm["dbname"].as<std::string>();
	}
	if (!m_vm["hostname"].empty()){
		m_hostname = m_vm["hostname"].as<std::string>();
	}
	if (!m_vm["user"].empty()){
		m_username = m_vm["user"].as<std::string>();
	}
	if (!m_vm["password"].empty()){
		m_password = m_vm["password"].as<std::string>();
	}
    if (!m_vm["unitid"].empty()){
        m_id_unit = m_vm["unitid"].as<int>();
    }
	*/
	if(!m_vm["personid"].empty()){
		m_id_person = m_vm["personid"].as<int>();
	}
	else {
		m_id_person = -2;
	}
	
	if (m_vm.count("showidunit")){
		m_show_idunit = true;
	}
	if (m_vm.count("list-persons")){
		m_list_persons = true;
	}
    if (!m_vm["sql-server"].empty()){
        std::string input_value = m_vm["sql-server"].as<std::string>();
        std::cout << "input_value = " << input_value <<std::endl;
        if (input_value.find("ostgre") < input_value.size()) {
            std::cout << "find postgres = " << input_value.find("ostgre") <<std::endl;
            m_typeserver = CliOptions::PostgreSQL;
            goto exit_if;
        }
        if ((input_value.find("ySQL") < input_value.size()) || 
                (input_value.find("ysql") > 0) ||
                (input_value.find("ySql") > 0) ) {
            //std::cout << input_value <<std::endl;
            std::cout << "find mysql = " << input_value.find("ysql") <<std::endl;
            m_typeserver = CliOptions::MySQL;
            goto exit_if;
        } 
exit_if:;
    }
}

std::string CliOptions::get_all_parametrs()const{
    std::stringstream ss;
	if (!m_db_name.empty())
		ss << "dbname=" << m_db_name << " ";
	if (!m_hostname.empty())
		ss << "hostname=" << m_hostname << " ";
	if (!m_username.empty())
		ss << "user=" << m_username << " ";
	if (!m_password.empty())
		ss << "password=" << m_password;
	return ss.str();
}

std::string CliOptions::get_string_typeserver() const {
    switch (m_typeserver) {
    case(CliOptions::PostgreSQL):
        return "postgresql";
    case(CliOptions::MySQL):
        return "mysql";
    default:
        return "none";
    }
}

int CliOptions::getUnitId() const{
    return m_id_unit;
}

bool CliOptions::getShowIdUnit() const {
	return m_show_idunit;
}
