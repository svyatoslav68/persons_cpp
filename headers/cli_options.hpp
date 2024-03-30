#pragma once

namespace po = boost::program_options;
class CliOptions {
enum TypeServer {PostgreSQL, MySQL, Oracle, DB2};
public:
    CliOptions() = delete;
    CliOptions(std::string name_file_settings);
    CliOptions(const int argc, const char *argv[], 
            std::string name_file_settings="settings.ini");
	po::variables_map get_variables_map () {return m_vm;}
	std::string get_all_parametrs();
    std::string get_string_typeserver();
private:
    std::string m_name_file_settings;
    TypeServer m_typeserver;
    po::variables_map m_vm;
	std::string m_db_name;
	std::string m_hostname;
	std::string m_username;
	std::string m_password;
};
