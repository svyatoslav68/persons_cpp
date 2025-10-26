#pragma once
#include <functional>

namespace ConsoleMenu {

class Menu;
class Item{
public:
	Item();
	Item(const int id_data);
	Item(const std::string text, const int id_data = -1);
	Item(const std::string text, const Menu *subMenu);
	std::string getText() const {return m_text_item;}
	//void action() const;
	void setAction(std::function<void(std::string)> action);
	void setAction(std::function<void(int, std::string)> action);
	void setAction(std::function<void(std::string)> action, const std::string str);
	//std::function<void(const std::string)> action;
	const Menu *getMenu() const {return m_subMenu;}
	bool isMenu() const {return this->m_subMenu!=nullptr;}
	std::function<void(std::string)> m_action;
	~Item();
private:
	const int m_id_data = -1; // Идентификатор связанных с пунктом меню данных
	std::string m_text_item;
	const Menu *m_subMenu;
	//void *(
};

}
