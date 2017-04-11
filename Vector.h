/*!
    @file Vector.h
    @brief Реализация класса Vector
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#ifndef Vector_H_INCLUDED
#define Vector_H_INCLUDED

#include <stdexcept>
#include "GlobalOptions.h"

using std::cout;
using std::endl;

namespace thirtythree
{

    template <typename T>
    class Vector
    {
    public:

        //! Переопределение итератора для массива
        class iterator
        {
        public:

            //! Пустой итератор
            //! Присваивает указателю значение NULL
            iterator():
                p_index(nullptr)
            {
            }

            //! Конструктор итератора с передачей параметра
            //! Передает значение указателя
            iterator(T *p_newindex):
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
            iterator& operator ++()
            {
                ++p_index;
                return *this;
            }

            //! Переопределение оператора -- префикс
            //! @return следующий итератор
            iterator& operator --()
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
            bool operator == (const iterator& that) const
            {
                return (p_index == that.p_index);
            }

            //! Переопределение операции неравенства
            //! @param that - итератор, с которым сравниваем
            //! @return TRUE/FALSE
            bool operator != (const iterator& that) const
            {
                return (p_index != that.p_index);
            }

            //! Переопределение операции пост-инкремента
            //! @return Возвращает итератор
            iterator operator ++(int)
            {
                return iterator(p_index++);
            }

            //! Переопределение операции пост-декремента
            //! @return Возвращает итератор
            iterator operator --(int)
            {
                return iterator(p_index--);
            }

        private:

            //! Указатель на элемент массива
            T *p_index;
        };

        //! Инициализирует массив нулевого размера
        Vector();

        //! Явно инициализирует массив размера size
        //! @param size Размер массива
        explicit Vector(size_t size);

        //! Инициализирует массив другим массивом (создает копию)
        //! @param that Другой массив
        Vector(const Vector& that);

        //! Инициализирует массив списком инициализации
        //! @param init Список инициализации
        Vector(const std::initializer_list<T>& init);

        //! Освобождает память
        ~Vector();

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

        //! Оператор присваивания
        //! @param that Другой массив
        //! @return Ссылка на this
        Vector& operator =(const Vector &that);

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
        T& at(const size_t pos);

        //! Возвращает элемент массива с индексом pos для константных объектов
        //! @param pos Индекс элементаl
        //! @return Элемент массива с индексом pos
        const T& at(const size_t pos) const;

        //! Удаляет элемент с индексом pos
        //! @param pos Индекс элемента
        //! @return Новый размер массива
        size_t erase(const size_t pos);

        //! Вставляет элемент на позицию pos
        //! @param pos Индекс элемента
        //! @param n Вставляемый элемент
        size_t insert(const size_t pos, const T n);

        //! Выводит на экран дамп массива
        void dump() const;

        //! Изменяет размер массива
        //! @param new_size Новый размер массива
        size_t resize(const size_t new_size);

        //! @return Итератор на начало массива
        iterator begin()
        {
            iterator begin_iterator(&data_[0]);
            return begin_iterator;
        }

        //! @return Итератор на конец массива
        iterator end()
        {
            return end_iterator;
        }

    private:

        //! Размер дополительно резервируемой памяти
        static const size_t RESERVED_ = 10;

        //! Размер массива
        size_t size_;

        //! Зарезервированное место
        size_t reserve_;

        //! Указатель на область памяти, в которой хранятся данные
        T *data_;

    };

    //! Оператор сравнения
    //! @param arr1,arr2 Два массива
    //! @return Равны ли массивы
    template <typename T>
    bool operator ==(const Vector<T>& arr1, const Vector<T>& arr2);

    //! Оператор присоединения второго массива к первому
    //! @param arr1,arr2 Два массива
    //! @return Новый массив
    template <typename T>
    Vector<T> operator +(const Vector<T>& arr1, const Vector<T>& arr2);

    class Bitset
    {
    public:

        class reference
        {
        public:

            template <typename T>
            friend class Vector<T>::iterator;

            reference(Bitset& b, size_t pos) :
                parent_ (&b),
                pos_ (pos),
                value_ (parent_->get(pos))
            {
            }

            ~reference()
            {
            }

            reference& operator=(bool x)
            {
                value_ = x;
                parent_->set(value_, pos_);
                return *this;
            }

            reference& operator=(const reference& x)
            {
                value_ = (bool) x;
                parent_->set(value_, pos_);
                return *this;
            }

            operator bool() const
            {
                return value_;
            }

            bool operator == (const reference& that) const
            {
                return (value_ == that.value_);
            }

            bool operator != (const reference& that) const
            {
                return (value_ != that.value_);
            }

        private:

            Bitset *parent_;
            size_t pos_;
            bool value_;

        };

        Bitset(size_t size) :
            size_ (size),
            data_ (new unsigned char [size / 8 + 1])
        {
            if (DEV_MESSAGES)
                cout << __PRETTY_FUNCTION__ << endl;
            for (size_t i = 0; i < size_; i++)
            {
                set(false, i);
            }
        }

        ~Bitset()
        {
            if (DEV_MESSAGES)
                cout << __PRETTY_FUNCTION__ << endl;
            delete [] data_;
            data_ = nullptr;
            size_ = 0;
        }

        reference operator[] (size_t pos)
        {
            if (pos >= size_)
            {
                throw std::runtime_error("Index out of bounds");
            }
            return reference(*this, pos);
        }

        bool operator[] (size_t pos) const
        {
            return get(pos);
        }

        void dump() const
        {
            cout << "Bitset [" << size_ << "]"<< endl;
            for (size_t i = 0; i < size_; i++)
            {
                cout << "\tdata_[" << i << "] = " << get(i) << endl;
            }
        }

        size_t size() const { return size_; }

        size_t resize(const size_t new_size)
        {
            if (new_size < size_)
            {
                throw std::runtime_error("New size is smaller than current size");
            }

            size_t new_charsize = new_size / 8 + 1;
            size_t charsize = size_ / 8 + 1;
            size_t num = new_size - size_;

            unsigned char *newdata = new unsigned char [new_charsize];

            for (size_t i = 0; i < charsize; i++)
            {
                newdata[i] = data_[i];
            }

            delete [] data_;
            data_ = newdata;
            size_ = new_size;

            for (size_t i = size_ - num; i < size_; i++)
            {
                set(false, i);
            }

            return size_;
        }

    private:

        bool get(size_t pos) const
        {
            if (pos >= size_)
            {
                throw std::runtime_error("Index out of bounds");
            }
            int bit = data_[pos/8] & 1 << (pos % 8);
            return !!bit;
        }

        void set(bool value, size_t pos)
        {
            if (pos >= size_)
            {
                throw std::runtime_error("Index out of bounds");
            }
            if (value)
            {
                data_[pos / 8] |= 1 << (pos % 8);
            }
            else
            {
                data_[pos / 8] &= ~(1 << (pos % 8));
            }
        }

        size_t size_;
        unsigned char *data_;

    };

    template <>
    class Vector<bool>
    {
    public:

        class iterator
        {
        public:

            iterator()
            {
                if (DEV_MESSAGES)
                    cout << __PRETTY_FUNCTION__ << endl;
            }

            iterator(Bitset &bitset, size_t pos):
                bitset_ (&bitset),
                pos_ (pos)
            {
                if (DEV_MESSAGES)
                    cout << __PRETTY_FUNCTION__ << endl;
            }

            iterator& operator =(const iterator& that)
            {
                bitset_ = that.bitset_;
                pos_ = that.pos_;
                return *this;
            }

            iterator& operator =(const Bitset::reference& ref)
            {
                pos_ = ref.pos_;
                return *this;
            }

            Bitset::reference operator *()
            {
                return (*bitset_)[pos_];
            }


            iterator& operator ++()
            {
                pos_++;
                return *this;
            }

            iterator& operator --()
            {
                pos_--;
                return *this;
            }

            bool operator == (const iterator& that) const
            {
                return (pos_ == that.pos_);
            }

            bool operator != (const iterator& that) const
            {
                return (pos_ != that.pos_);
            }

            iterator operator ++(int)
            {
                return iterator(*bitset_, pos_++);
            }

            iterator operator --(int)
            {
                return iterator(*bitset_, pos_--);
            }

        private:

            Bitset *bitset_;
            size_t pos_;

        };

        Vector();
        explicit Vector(size_t size);
        Vector(const Vector& that);
        Vector(const std::initializer_list<bool>& init);
        ~Vector();

        size_t size() const { return size_; }
        Bitset::reference operator [](size_t n);
        const bool operator [](size_t n) const;
        Vector& operator =(const Vector &that);
        bool empty() const;
        bool first() const;
        bool last() const;
        Bitset::reference at(const size_t pos);
        const bool at(const size_t pos) const;
        size_t erase(const size_t pos);
        size_t insert(const size_t pos, const bool n);
        void dump() const;
        size_t resize(const size_t new_size);

        iterator begin()
        {
            return iterator(data_, 0);
        }

        iterator end()
        {
            return iterator(data_, size_);
        }

    private:

        static const size_t RESERVED_ = 10;
        size_t size_;
        size_t reserve_;
        Bitset data_;

    };

}

#include "Vector.hpp"
#include "Vector_bool.hpp"

#endif // Vector_H_INCLUDED
