#include <iostream> // Количество пунктов меню, отобржаемых на странице
#include <sstream>
#include <unistd.h>
#include <functional>
/*#define SOCI_USE_BOOST
#include <soci/soci.h>
#include <boost/format.hpp>
#include "connection.hpp"*/
#include "item.hpp"
#include "pager.hpp"
#include "term.hpp"

namespace ConsoleMenu {

Pager::Pager(const Pager::TYPE_RESULT type, const Menu *menu):m_type(type),m_displayingMenu(menu),m_numberPage(0)
{
	if (m_type == Pager::LIST){
		m_result_strings = new std::vector<std::string>;
		m_result_strings->reserve(m_displayingMenu->m_size);
	}
}


std::string Pager::exec(bool with_clean)
{
BEGIN_SELECT:
	char symbol;
	set_input_mode();
	while(true){
		with_clean?display():display_without_clean();
		read(0, &symbol, 1);
		if (symbol == 'q') {
			reset_input_mode();
			return std::string();
		}
		if (symbol == 'n'){ // Переход к предыдущей странице
			next();
			continue;
		}
		if (symbol == 'p'){ // Переход к следующей странице
			prev();
			continue;
		} 
		if (symbol == 'c'){ // Стирание экрана и перерисовывание текущего меню
			clearscr();
			continue;
		}
		if (symbol==0x1b){ // <Esc> Возврат к меню-предку
			if (m_displayingMenu->menuStack.size() > 0){
				m_displayingMenu = m_displayingMenu->exitMenu();
				m_numberPage = 0;
			}
			else {
				if (m_type == Pager::LIST){
					if (!m_result_strings->empty()){
						reset_input_mode();
						return m_result_strings->at(0);
					}
				}
			}
			continue;
		}
		if ((symbol >= '0') && (symbol <= '9'))
		{
			auto const_it = m_displayingMenu->m_items.cbegin();
			// Подвигаем итератор const_it на пункт меню, выбранный нажатием на клавишу
			for (unsigned i = 0; i < m_numberPage*m_number_rows+(symbol - '0'); ++i){
				//std::cout << "i = " << i << std::endl;
				if(++const_it > m_displayingMenu->m_items.cend() - 1){
					reset_input_mode();
					goto BEGIN_SELECT;
				}
			}
			if (const_it->isMenu()){
				m_displayingMenu->enterMenu(m_displayingMenu);//const_it->getMenu());
				m_displayingMenu = const_it->getMenu();
				m_numberPage = 0;
			}
			else {
				if (m_type == Pager::TEXT){
					reset_input_mode();
					return const_it->getText();
				}
				else {
					if (m_type == Pager::LIST){
						m_result_strings->push_back(const_it->getText());
					}
					else {
						const_it->m_action(const_it->getText());
						std::cout << "Press any alphanumeric key...\n";
						char a;
						std::cin >> a;
					}
				}
			}
		}
	}
	std::cout << "Reset terminal Mode\n";
	reset_input_mode();
	return std::string();
}

std::string Pager::exec(Pager::TYPE_RESULT type, bool with_clean)
{
	m_type=type;
	if (m_type == Pager::LIST){
		if (m_result_strings)
			delete m_result_strings;
		m_result_strings = new std::vector<std::string>;
		m_result_strings->reserve(m_displayingMenu->m_size);
	}
	return exec(with_clean);
}

void Pager::display() const
{
	clearscr();
	display_without_clean();
}

void Pager::display_without_clean() const
{
	//std::cout << m_displayingMenu->menuStack.top()->getName() << std::endl;
	std::cout << m_displayingMenu->getName() << std::endl;
	unsigned int number = 0;
	auto item = m_displayingMenu->m_items.cbegin()+m_numberPage*m_number_rows;
	while ((item < m_displayingMenu->m_items.cbegin() + m_number_rows*(m_numberPage+1))
						&& (item < m_displayingMenu->m_items.cend())){
		std::cout << number++ << ":" << item->getText() << std::endl;
		++item;
	}
	if ((m_type == Pager::LIST) && (!m_result_strings->empty())){
		std::cout << "Уже выбрано: " << std::endl;
		for (auto field: *m_result_strings) {
			std::cout << field << ": ";
		}
		std::cout << std::endl;
	}
	if (m_displayingMenu->m_size > m_number_rows)
		std::cout << "Next page(n); Prev page(p)\n";
}


void Pager::clearscr() const
{
	std::cout << std::string(100, '\n') << std::flush;
}

bool Pager::next()
{
	if (m_displayingMenu->m_items.cbegin()+(m_number_rows*(m_numberPage+1)) < 
			m_displayingMenu->m_items.cend()){
		++m_numberPage;
		return true;
	}
	else{
		return false;
	}
}

bool Pager::prev()
{
	if(m_numberPage > 0){
		--m_numberPage;
		return true;
	}
	else {
		m_numberPage = 0;
		return false;
	}
}

void Pager::setMenu(const Menu *menu, const int numberPage)
{
	m_displayingMenu = menu;
	m_numberPage = numberPage;
}

} // namespace
