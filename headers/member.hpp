#pragma one

using Db::Connect;

class Member {
	public:
		Member() = delete;
		Member(std::shared_ptr<Connect> conn, int id);
		friend std::ostream & operator <<(std::ostream & out, const Member & member);
	private:
		std::shared_ptr<Connect> m_conn;
		int m_id;
		std::string family;
		std::string name;
		std::string parent;
}
;
