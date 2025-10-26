# pragma once
using std::vector;
using std::string;
//using std::
using Db::Connect;
using Db::DataFromBD;

class ListPersons:DataFromBD{
public:
    ListPersons() = delete;
	ListPersons(std::shared_ptr<Db::Connect> conn, int id_unit);
    //ListPersons(Db::Connect* conn, int id_unit);
    //ListPersons(Db::Connect& conn, string SQL_query);
	int display_list(bool show_idperson = false) const;
private:
	//std::shared_ptr<Db::Connect> m_conn;
	const int m_idUnit;
	bool m_recursive = false;
	std::vector<int> m_persons;
    //DB_connection;
};
