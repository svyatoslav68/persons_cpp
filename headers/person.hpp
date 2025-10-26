# pragma once
//using std::vector;
using std::string;

using Db::Connect;
using Db::DataFromBD;

class Person:DataFromBD{
public:
	Person() = delete;
	Person(std::shared_ptr<Connect> conn, int idperson);
	//Person(Connect &conn, string family, string name, string parent);
	int getIdPerson() const {return m_idperson;}
	std::string getFamily() const {return m_family;}
	std::string getName() const {return m_name;}
	std::string getParent() const {return m_parent;}
	int displayPerson(bool with_id = false) ;
	void setShowID(bool with_id = true) {m_with_id = with_id;}
	friend std::ostream & operator <<(std::ostream & out, const Person & person);
private:
	//std::shared_ptr<Db::Connect> m_conn;
	int m_idperson;
	string m_family;
	string m_name;
	string m_parent;
	int m_current_unit;
	bool m_with_id = false;
	// Функции возвращающие данные о сотруднике 
	void _getMembersFamily(std::string) const;
	void _getActions(std::string) const;
	void _getLearn(std::string) const;
};

