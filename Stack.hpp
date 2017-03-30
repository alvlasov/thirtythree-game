/*!
    @file Stack.hpp
    @brief Реализация класса Stack
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

namespace thirtythree
{

    template <typename T>
    Stack<T>::Stack() :
        data_(def_capacity_),
        size_(0),
        capacity_(def_capacity_)
    {
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;
    }

    template <typename T>
    Stack<T>::Stack(size_t capacity) :
        data_(capacity),
        size_(0),
        capacity_(capacity)
    {
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;
    }

    template <typename T>
    Stack<T>::~Stack()
    {
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;
        capacity_ = 0;
        size_ = -1;
    }

    template <typename T>
    bool Stack<T>::empty() const
    {
        return (size_ == 0);
    }

    template <typename T>
    void Stack<T>::push(T value)
    {
        if (size_ >= capacity_)
        {
            data_.insert(size_++, value);
            capacity_ = size_;
        }
        else
        {
            data_[size_++] = value;
        }
    }

    template <typename T>
    T Stack<T>::top()
    {
        if (size_ != 0)
            return data_[size_ - 1];
        else
            throw 2;
    }

    template <typename T>
    bool Stack<T>::pop()
    {
        if (size_ != 0)
        {
            size_--;
            return true;
        }
        return false;
    }

    template <typename T>
    bool Stack<T>::ok() const
    {
        return (size_ <= capacity_);
    }

    template <typename T>
    void Stack<T>::dump() const
    {
        cout << "Stack (";
        if (ok())
            cout << "OK)" << endl;
        else
            cout << "ERROR!)" << endl;
        cout << "\t{" << endl;
        cout << "\tsize_\t\t= " << size() << endl;
        cout << "\tcapacity_\t= " << capacity() << endl;
        cout << "\tdata_ [" << capacity() << "]:"<< endl;
        cout << "\t\t{" << endl;
        for (size_t i = 0; i < capacity(); i++)
        {
            if (i < size())
                cout << "\t*\t" << "[" << i << "] = " << data_[i];
            else
                cout << "\t\t" << "[" << i << "] = " << data_[i];
            cout << endl;
        }
        cout << "\t\t}" << endl;
        cout << "\t}" << endl;
    }

}
