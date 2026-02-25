#pragma once 

namespace s_classes {

template <class TupleClass>
class Stuple {
/* Класс кортежа, добавляющий кортежу некоторые полезные функции
 * А именно:
 *    - преобразование кортежа в строку;
 *    - вывод кортежа в поток;
 *    */
    private:
        TupleClass tuple_data;
    public:
        Stuple() = delete;
        Stuple(const TupleClass& t):tuple_data(t){}
        TupleClass& tuple() {return tuple_data;}
};
}
