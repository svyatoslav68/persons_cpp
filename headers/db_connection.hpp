#pragma once

namespace Db {
class Connect {
public:
    Connect() = delete;
    Connect(Connect &);
    Connect(std::string for_server,std::string typeserver="postgresql");
    Connect(std::string typeserver, std::string name_DB, std::string user, std::string password);
    ~Connect();
    bool open();
    bool close();
    soci::session *getSession();
	std::string getCommandConnect() const {return m_connect_string;}
    std::string getStringTypeServer() const {return m_typeserver;}
private:
    std::string m_typeserver;
    std::string m_connect_string;
    int m_is_connected;
    soci::session m_session;
};

class DataFromBD {
public:
	virtual ~DataFromBD() {}
protected:
	DataFromBD(std::shared_ptr<Connect> conn):m_conn(conn){
		m_ses = conn->getSession();
	}
	std::shared_ptr<Db::Connect> m_conn;
	soci::session *m_ses;
private:
};
}
