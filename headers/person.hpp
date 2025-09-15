# pragma once
//using std::vector;
using std::string;

using Db::Connect;

class Person{
public:
	Person() = delete;
	Person(std::shared_ptr<Connect> conn, int idperson);
	Person(Connect &conn, string family, string name, string parent);
	std::string getFamily() const {return m_family;}
	std::string getName() const {return m_name;}
	std::string getParent() const {return m_parent;}
	int displayPerson() const;
private:
	std::shared_ptr<Db::Connect> m_conn;
	int m_idperson;
	string m_family;
	string m_name;
	string m_parent;
	int m_current_unit;
};
