/*!
    @file Stack.h
    @brief Реализация класса Stack
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#ifndef STACKH
#define STACKH

#include "Array.h"

template <typename T>
class Stack
{
public:

    //! Инициализирует стек нулевого размера
    Stack();

    //! Явно инициализирует стек размера capacity
    //! @param capacity Размер стека
    Stack(size_t capacity);

    //! Освобождает память
    ~Stack();

    //! Возвращает размер стека
    //! @return Размер стека
    size_t size() const { return size_; }

    //! Возвращает вместимость стека
    //! @return Вместимость стека
    size_t capacity() const { return capacity_; }

    //! Проверяет, пуст ли стек
    //! @return true/false
    bool empty() const;

    //! Заполняет следующий элемент стека
    //! @return true/false
    bool push(T value);

    //! Возвращает крайний элемент стека
    //! @return крайний элемент
    T top() const;

    //! Удаляет крайний элемент стека
    //! @return true/false
    bool pop();

    //! Проверяет соответствие размера и вместимости стека
    //! @return true/false
    bool ok() const;

    //! Выводит ошибку и данные о стеке при несоответствии размера и вместимости стека
    void dump() const;

private:

    //! Константа для деструктора
    static const int POISON_VAR = 660660;

    //! Стандартная емкость стека(если не указывать размер в конструкторе)
    static const size_t def_capacity_ = 10;

    //! Хранилище данных стека
    Array <T> data_;

    //! Размер стека
    size_t size_;

    //! Вместимость стека
    size_t capacity_;
};


#endif
