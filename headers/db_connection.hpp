#pragma once

class Connect {
public:
    Connect() = delete;
    Connect(std::string for_server,std::string typeserver="postgresql");
    Connect(std::string typeserver, std::string name_DB, std::string user, std::string password);
    ~Connect();
    bool open();
    bool close();
    soci::session *getConnect();
	std::string getCommandConnect() {return m_connect_string;}
    std::string getStringTypeServer() {return m_typeserver;}
private:
    std::string m_typeserver;
    std::string m_connect_string;
    int m_is_connected;
    soci::session m_session;
};

