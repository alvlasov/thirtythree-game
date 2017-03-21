/*!
    @file Array.h
    @brief Реализация класса Array
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

template <typename T>

class Array
{
public:

    //! Переопределение итератора для массива
    class Array_iterator
    {
    public:

        //! Пустой итератор
        //! Присваивает указателю значение NULL
        Array_iterator():
            p_index(nullptr)
        {
        }

        //! Конструктор итератора с передачей параметра
        //! Передает значение указателя
        Array_iterator(T *p_newindex):
            p_index(p_newindex)
        {
        }

        //! Переопределение оператора *()
        //! @return объект, на который указывает
        T& operator *() const
        {
            return *p_index;
        }

        //! Переопределение оператора ++ префикс
        //! @return следующий итератор
        Array_iterator& operator ++()
        {
            ++p_index;
            return *this;
        }

        //! Переопределение оператора -- префикс
        //! @return следующий итератор
        Array_iterator& operator --()
        {
            --p_index;
            return *this;
        }

        //! Переопределение оператора ->
        //! @return указатель на элемент массива
        T* operator ->() const
        {
            return p_index;
        }

        //! Переопределение операции сравнения двух итераторов
        //! @param that - итератор, с которым сравниваем
        //! @return TRUE/FALSE
        bool operator == (const Array_iterator& that) const
        {
            return (p_index == that.p_index);
        }

        //! Переопределение операции неравенства
        //! @param that - итератор, с которым сравниваем
        //! @return TRUE/FALSE
        bool operator != (const Array_iterator& that) const
        {
            return (p_index != that.p_index);
        }

        //! Переопределение операции пост-инкремента
        //! @return Возвращает итератор
        Array_iterator operator ++(int)
        {
            return Array_iterator(p_index++);
        }

        //! Переопределение операции пост-декремента
        //! @return Возвращает итератор
        Array_iterator operator --(int)
        {
            return Array_iterator(p_index--);
        }

    private:

        //! Указатель на элемент массива
        T *p_index;
    };

    //! Инициализирует массив нулевого размера
    Array();

    //! Явно инициализирует массив размера size
    //! @param size Размер массива
    explicit Array(size_t size);

    //! Инициализирует массив другим массивом (создает копию)
    //! @param that Другой массив
    Array(const Array& that);

    //! Инициализирует массив списком инициализации
    //! @param init Список инициализации
    Array(const std::initializer_list<T>& init);

    //! Освобождает память
    ~Array();

    //! Возвращает размер массива
    //! @return Размер массива
    size_t size() const { return size_; }

    //! Обращение к элементам массива через []
    //! @param n Индекс элемента
    //! @return Значение в ячейке массива с индексом n
    T& operator [](size_t n);

    //! Обращение к элементам массива через [] для константных объектов
    //! @param n Индекс элемента
    //! @return Значение в ячейке массива с индексом n
    const T& operator [](size_t n) const;

    //! Выделение памяти
    //! @param n Индекс элемента
    //! @return указатель на начало блока
    void* operator new(size_t size);

    //! Оператор присваивания
    //! @param that Другой массив
    //! @return Ссылка на this
    Array& operator =(const Array &that);

    //! Проверяет, пуст ли массик
    //! @return true/false
    bool empty() const;

    //! Возвращает первый элемент массива
    //! @return Первый элемент массива
    T first() const;

    //! Возвращает последный элемент массива
    //! @return Последний элемент массива
    T last() const;

    //! Возвращает элемент массива с индексом pos
    //! @param pos Индекс элементаl
    //! @return Элемент массива с индексом pos
    T at(const size_t pos) const;

    //! Удаляет элемент с индексом pos
    //! @param pos Индекс элемента
    //! @return Новый размер массива
    size_t erase(const size_t pos);

    //! Вставляет элемент на позицию pos
    //! @param pos Индекс элемента
    //! @param n Вставляемый элемент
    //! @return Новый размер массива
    size_t insert(const size_t pos, const T n);

    //! Выводит на экран дамп массива
    void dump() const;

    //! Изменяет размер массива в большую сторону
    //! @param new_size Новый размер массива
    //! @return Статус операции
    bool resize(const size_t new_size);

    //! @return Итератор на начало массива
    Array_iterator begin()
    {
        Array_iterator begin_iterator(&data_[0]);
        return begin_iterator;
    }

    //! @return Итератор на конец массива
    Array_iterator end()
    {
        Array_iterator begin_iterator(&data_[size_-1]);
        return begin_iterator;
    }

private:

    //! Указатель на область памяти, в которой хранятся данные
    T *data_;

    //! Размер массива
    size_t size_;

};

//! Оператор сравнения
//! @param arr1,arr2 Два массива
//! @return Равны ли массивы
template <typename T>
bool operator ==(const Array<T>& arr1, const Array<T>& arr2);

//! Оператор поэлементного сложения двух массивов одинакового размера
//! @param arr1,arr2 Два массива
//! @return Новый массив
template <typename T>
Array<T> operator +(const Array<T>& arr1, const Array<T>& arr2);

//! Оператор поэлементного вычитания двух массивов одинакового размера
//! @param arr1,arr2 Два массива
//! @return Новый массив
template <typename T>
Array<T> operator -(const Array<T>& arr1, const Array<T>& arr2);

#include "Array.hpp"

#endif // ARRAY_H_INCLUDED
