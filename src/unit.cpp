/* Source file of class Unit.
 *
 * */


#include <memory>
#include <vector>
#include <iostream>
#include <soci/soci.h>
#include <codecvt>
#include <boost/lexical_cast.hpp>
#include "db_connection.hpp"
#include "unit.hpp"

using Db::Connect;

Unit::Unit(const int idUnit, std::shared_ptr<Connect> conn, bool showidunit):m_idUnit{idUnit},
m_conn{conn}, m_counter_inner{0}, 
	m_order_number{0}, m_show_idunit{showidunit}{
    soci::session *ses = conn->getSession();
    (*ses) << "SELECT number, name, parent, type, visualization FROM units WHERE idunit = " << idUnit, soci::into(m_number), soci::into(m_name), soci::into(m_parent),soci::into(m_type), soci::into(m_visualization);
    /*, soci::into(m_type);
     , soci::into(m_visualization); */
    std::vector<int> v_children(15);
    (*ses) << "SELECT  idUnit FROM units WHERE parent = " << idUnit << " ORDER BY number", soci::into(v_children);
    //std::cout << "Children of " << m_idUnit;
    //std::cout << getName();
	int counter = 0;
    for (auto it: v_children){
        //std::cout << it << ": ";
        ++m_counter_inner;
		Unit new_unit(it, conn, m_show_idunit);
		new_unit.setShowIdUnit(m_show_idunit);
		if (++counter == (v_children.size()))
			new_unit.m_is_last = true;
        m_children.push_back(new_unit);//Unit(it, conn));
    }
    //std::cout << std::endl;
        }

Unit::~Unit(){
}

std::string Unit::getName() const{
    std::string result{m_name.empty()?boost::lexical_cast<std::string>(m_number):m_name};
    if (m_visualization.compare("before") ==  0){
        result = m_type + " " + result;
    }
    if (m_visualization.compare("after") ==  0){
        result += " " + m_type;
    }
	if (m_show_idunit) {
		result += "("+boost::lexical_cast<std::string>(m_idUnit)+")";
	}
    return result;//+boost::lexical_cast<std::string>(result.length());
}

std::string Unit::getFullName() const{
    std::string result = {getName()};
 //   while (m_parent w
    return result;
}

std::vector<int> Unit::getPersons(){
	std::vector<int> result;
	return result;
}

std::string Unit::display_children(std::vector<int> symbols, int otstup) {
	//std::cout << "Show id Unit = " << m_show_idunit << std::endl;
	std::string result("");
	result += std::string(getName());
	int length_string_parent ; // Длина строки предка
	if (m_children.size() == 0){
			result += std::string("\n");
	}
	else {
		int order = 0;
		if (m_children.size() > 1){
			result += std::string("-+-");		
			length_string_parent = otstup + length_w_string(result);
			symbols.push_back(length_string_parent - 2);
			}
		else {
			result += std::string("---");
			length_string_parent = otstup + length_w_string(result);
			}
		for (auto child = m_children.begin(); child < m_children.end();
		child++, ++order){
				child->m_order_number = order;
				if (order > 0){
				for (int l = 0; l < length_string_parent-2; l++){
					if (std::find(symbols.cbegin(), symbols.cend(), l) ==
					std::cend(symbols))
						result += std::string(" ");
					else
						if (l != *(symbols.crbegin() + 1)) {
							result += std::string("|");
						}
						else 
							if(!m_is_last){
								result += std::string("|");
							}
							else {
								result += std::string(" ");
							}
				}
				if (order < (m_children.size() - 1)) {
					  result += std::string("|-");
					}
				else
					  result += std::string("`-");
				}
				result += child->display_children(symbols, length_string_parent);
		}
	}
	return result;
}

size_t Unit::length_w_string(const std::string str){
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>{}.from_bytes(str).size();
}



