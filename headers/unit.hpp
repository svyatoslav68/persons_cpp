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
        Unit();
        Unit(int idUnit);
        bool addChild();
        bool addChild(int codUnit);
        ~Unit();
    private:
        int m_idUnit;
        int m_type;
        int m_parent_unit;
        int m_counter_inner;
        std::string m_name;
};
