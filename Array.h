/*!
    @file Array.h
    @brief Реализация класса Array
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

class Array
{
public:

    typedef float value_type;

    //! Инициализирует массив нулевого размера
    Array();

    //! Явно инициализирует массив размера size
    //! @param size Размер массива
    explicit Array(size_t size);

    //! Инициализирует массив другим массивом (создает копию)
    //! @param that Другой массив
    Array(Array& that);

    //! Освобождает память
    ~Array();

    //! Возвращает размер массива
    //! @return Размер массива
    size_t size() const { return size_; }

    //! Обращение к элементам массива через []
    //! @param n Индекс элемента
    //! @return Значение в ячейке массива с индексом n
    value_type& operator [](size_t n);

    //! Обращение к элементам массива через [] для константных объектов
    //! @param n Индекс элемента
    //! @return Значение в ячейке массива с индексом n
    const value_type& operator [](size_t n) const;

    //! Оператор присваивания
    //! @param that Другой массив
    //! @return Ссылка на this
    Array& operator =(Array &that);

    //! Проверяет, пуст ли массик
    //! @return true/false
    bool empty() const;

    //! Возвращает первый элемент массива
    //! @return Первый элемент массива
    value_type first() const;

    //! Возвращает последный элемент массива
    //! @return Последний элемент массива
    value_type last() const;

    //! Возвращает элемент массива с индексом pos
    //! @param pos Индекс элемента
    //! @return Элемент массива с индексом pos
    value_type at(const size_t pos) const;

    //! Удаляет элемент с индексом pos
    //! @param pos Индекс элемента
    //! @return Новый размер массива
    size_t erase(const size_t pos);

    //! Вставляет элемент на позицию pos
    //! @param pos Индекс элемента
    //! @param n Вставляемый элемент
    //! @return Новый размер массива
    size_t insert(const size_t pos, const value_type n);

    //! Выводит на экран дамп массива
    void dump() const;

    //! Изменяет размер массива в большую сторону
    //! @param new_size Новый размер массива
    //! @return Статус операции
    bool resize(const size_t new_size);

private:

    //! Указатель на область памяти, в которой хранятся данные
    value_type *data_;

    //! Размер массива
    size_t size_;

};

//! Оператор сравнения
//! @param arr1,arr2 Два массива
//! @return Равны ли массивы
bool operator ==(const Array& arr1, const Array& arr2);

//! Оператор поэлементного сложения двух массивов одинакового размера
//! @param arr1,arr2 Два массива
//! @return Новый массив
Array& operator +(const Array& arr1, const Array& arr2);

//! Оператор поэлементного вычитания двух массивов одинакового размера
//! @param arr1,arr2 Два массива
//! @return Новый массив
Array& operator -(const Array& arr1, const Array& arr2);

#endif // ARRAY_H_INCLUDED
