#include <iostream>
#include <string> 
#include <sstream> 
#include <soci/soci.h>
#include "db_connection.hpp"

namespace Db {

Connect::Connect(std::string for_server,std::string typeserver)
    :m_typeserver(typeserver),m_connect_string(for_server),m_is_connected(0){
}

Connect::Connect(std::string typeserver,std::string name_DB, std::string user, std::string password){
    std::stringstream ss;
   ss << "dbname=" << name_DB << " user=" << user << " password=" << password;
   m_connect_string = ss.str();
    std::cout << "Before connect. ------\nm_connect_string: " << m_connect_string << "\n ----------" << std::endl;
    m_is_connected = 0;
}

Connect::Connect(Connect &conn):m_typeserver(conn.m_typeserver),m_connect_string(conn.m_connect_string),m_is_connected(conn.m_is_connected){
}

Connect::~Connect(){
    close();
}

bool Connect::open() {
    if (!m_is_connected){
        try {
            soci::indicator ind;
            std::cout << "m_connect_string: " << m_connect_string << std::endl;
            m_session.open(m_typeserver, m_connect_string);
            m_session << "SELECT 1", soci::into(m_is_connected, ind);
            std::cout << "Connect is open and right.\n" << "ind = " << ind << "; m_is_connected = " 
                << m_is_connected << "."  << std::endl;
            return true;
        }
        catch (std::exception const & e) {
            std::cerr << e.what() << std::endl; 
            return false;
        }
    }
    else 
        return true;
}

bool Connect::close(){
    m_session.close();
    m_is_connected = 0;
    return true;
}

soci::session *Connect::getSession() {
    if (m_is_connected)
        return &m_session;
    else {
        return nullptr;
    }
}
} // namespace Db
