#include <iostream>
#include <string>
#include <functional>
/*#define SOCI_USE_BOOST
#include <soci/soci.h>
#include "connection.hpp"*/
#include "menu.hpp"
#include "item.hpp"

namespace ConsoleMenu {

Item::Item():m_id_data{-1}, m_text_item{std::string("")}, m_subMenu{nullptr} {
}

Item::Item(const int id_data):m_id_data{id_data}, m_text_item{std::string("")}, m_subMenu{nullptr} {
}

Item::Item(const std::string text, const int id_data):m_id_data{id_data}, m_text_item(text), m_subMenu(nullptr) {
}

Item::Item(const std::string text, const Menu *subMenu):m_id_data{-1}, m_text_item(text),
				m_subMenu(subMenu) {
}

Item::~Item() {
}

void Item::setAction(std::function<void(std::string)> _action){//, const std::string str) {
	//action = _action;//
	//std::cout << "Выбрано setAction(std::function<void(std::string)> _action, const std::string str)\n";
	m_action = std::bind(_action, std::placeholders::_1);
	//m_action = _action;
	//m_argument = str;
//	m_action("wiwiwiw");
}

void Item::setAction(std::function<void(int, std::string)> _action){//, const std::string str) {
	m_action = std::bind(_action, m_id_data, std::placeholders::_1);
	//std::cout << "Выбрано setAction(std::function<void(int, std::string)> _action, const std::string str)\n";
}

void Item::setAction(std::function<void(std::string)> _action, const std::string str){
	//m_action = std::bind(_action, m_id_data, str);
	m_action = std::bind(_action, str);
}

}
