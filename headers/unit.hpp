#pragma once

/* Header file for class Unit.
 * Class for stored information about Unit.
 * */
/* Concept of class Unit:
 * Класс должен содержать данные о подразделении и уметь предоставлять их
 * приложению.
 * Для позиционирования в дереве подразделений, в классе имеется указатель
 * на родительское подразделение.
 * Должен быть счетчик входящих подразделений, равенство нулю которого
 * говорит об отсутсвии входящих подразделений.
 * Необходимые методы должны делать следующее:
 *  - возвращать список входящих подразделений;
 *  - возвращать список сотрудников подразделения;
 *  - возвращать штатное расписание (то есть, в т.ч. вакансии);
 * */

class Unit{
    public:
        Unit() = delete;
        Unit(const Unit &unit) = default;
        Unit(Unit &&unit) = default;
        Unit(const int idUnit, Db::Connect &conn);
        Unit &operator=(const Unit &unit) = default;
        Unit &operator=(Unit &&unit) = default;
        std::string getName() const;
        std::string getFullName() const;
        bool addChild();
        bool addChild(const int codUnit);
        std::string display_children(std::vector<int>, int otstup = 0);
        ~Unit();
    private:
        const int m_idUnit;
        std::string m_type;
        std::shared_ptr<Db::Connect> m_conn;
        int m_counter_inner;
        int m_order_number; // Порядковый номер в иерархии при отображении дерева
        std::string m_name;
        std::string m_number;
        int m_parent;
        std::string m_visualization;
        std::vector<int> m_parent_indent;
        std::vector<Unit> m_children;
        size_t length_w_string(const std::string);
};
