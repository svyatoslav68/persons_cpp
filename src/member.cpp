#include <iostream>
#include <soci/soci.h>
#include <db_connection.hpp>
#include "member.hpp"

using Db::Connect;

Member::Member(std::shared_ptr<Connect> conn, int id):m_conn(conn){
}

std::ostream & operator <<(std::ostream & out, const Member & member){
	return out;
}
