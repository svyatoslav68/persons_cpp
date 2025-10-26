#ifndef _PAGER_HPP
#define _PAGER_HPP

#include "menu.hpp"

namespace ConsoleMenu {

class Pager {
public:
	enum TYPE_RESULT {
		TEXT,
		ACTION,
		LIST
	};
	const unsigned int m_number_rows = 10; // Количество пунктов меню, отобржаемых на странице
	//Pager() = 0;
	Pager(TYPE_RESULT type, const Menu *menu);
	Pager(const Menu *menu):m_type(TEXT),m_displayingMenu(menu),m_numberPage(0){}
	~Pager(){if (m_result_strings) delete m_result_strings;}
	std::string exec(bool with_clean = true);
	std::string exec(TYPE_RESULT type, bool with_clean = true);
	void display_without_clean() const;
	void display() const;
	bool next(); // возвращает False, если вызывается на последней странице
	bool prev(); // возвращает False, если вызывается на первой странице
	void setMenu(Menu *menu, int numberPage);
	std::vector<std::string> *getResultVector() {return m_result_strings;}
private:
	void clearscr() const;
	TYPE_RESULT m_type;
	const Menu *m_displayingMenu; // указатель на отображаемое меню
	int m_numberPage; // номер отображаемой страницы
	std::vector<std::string> *m_result_strings = nullptr;
	//std::pair<std::vector<Item *>::const_iterator, std::vector<Item *>::const_iterator> sequence;
};

} // namespace

#endif //_PAGER_HPP
