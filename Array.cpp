/*!
    @file Array.cpp
    @brief Реализация класса Array
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#include <cmath>
#include <iostream>
#include "Array.h"

using std::cout;
using std::endl;

template <typename T>
Array<T>::Array():
    data_(NULL),
    size_(0)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
Array<T>::Array(size_t size):
    data_(new T [size]),
    size_(size)
{
    for (unsigned int i = 0; i < size_; i++ )
    {
        data_[i] = 0;
    }

    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
Array<T>::Array(Array& that)
{
    size_ = that.size();
    data_ = new T [size_];

    for (unsigned int i = 0; i < size_; i++)
    {
        data_[i] = that[i];
    }
    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
Array<T>::~Array()
{
    cout << __PRETTY_FUNCTION__ << endl;

    delete [] data_;

    data_ = NULL;
    size_ = 0;
}

template <typename T>
Array<T>& Array<T>::operator =(Array &that)
{
    this -> resize(that.size());

    for (unsigned int i = 0; i < size_; i++ )
    {
        data_[i] = that.data_[i];
    }

    cout << __PRETTY_FUNCTION__ << endl;

    return *this;
}

template <typename T>
bool operator ==(const Array<T>& arr1, const Array<T>& arr2)
{
    if (arr1.size() != arr2.size())
            return false;
    else
    {
        for (unsigned int i = 0; i < arr1.size(); i++)
        {
            if (arr1.at(i) != arr2.at(i))
                return false;
        }
    }
    return true;
}

template <typename T>
bool Array<T>::empty() const
{
    if (size_ == 0)
    {
        return true;
    }

    return false;
}

template <typename T>
const T& Array<T>::operator [](size_t n) const
{
    if (!(0 <= n && n < size_))
    {
        throw 0;
    }

    return data_[n];
}

template <typename T>
Array<T>& operator +(const Array<T> &arr1, const Array<T> &arr2)
{
    if (arr1.size() != arr2.size())
    {
        throw 0;
    }

    size_t arr_size = arr1.size();

    Array <T> new_array(arr_size);

    for (unsigned int i = 0; i < arr_size; i++ )
    {
        new_array[i] = arr1.at(i) + arr2.at(i);
    }

    return new_array;
}

template <typename T>
Array<T>& operator -(const Array<T> &arr1, const Array<T> &arr2)
{
    if (arr1.size() != arr2.size())
    {
        throw 0;
    }

    size_t arr_size = arr1.size();

    Array <T> new_array(arr_size);

    for (unsigned int i = 0; i < arr_size; i++ )
    {
        new_array[i] = arr1.at(i)- arr2.at(i);
    }

    return new_array;
}

template <typename T>
T Array<T>::first() const
{
    if (empty())
    {
        throw 0;
    }

    return data_[0];
}

template <typename T>
T Array<T>::last() const
{
    if (empty())
    {
        throw 0;
    }

    return data_[size_-1];
}

template <typename T>
T Array<T>::at(const size_t pos) const
{
    if (pos >= size_)
    {
        throw 0;
    }
    return data_[pos];
}

template <typename T>
size_t Array<T>::insert(const size_t pos, const T n)
{
    if (pos >= size_)
    {
        throw 0;
    }
    T *newdata_ = new T [size_ - pos];

    for (unsigned int i = pos ; i < size_; i++)
    {
        newdata_[i - pos] = data_[i];
    }

    data_[pos] = n;

    this->resize(size_ + 1);

    for (unsigned int i = pos + 1; i < size_; i++)
    {
          data_[i] = newdata_[i - pos - 1];
    }

    return size_;
}

template <typename T>
size_t Array<T>::erase(const size_t pos)
{
    if (pos >= size_)
    {
        throw 0;
    }

    T *datanew_ = new T [size_-1];

    for (unsigned int i = 0; i < pos; i++)
    {
        datanew_[i] = data_[i];
    }

    for (unsigned int i = pos + 1; i < size_; i++)
    {
        datanew_[i-1] = data_[i];
    }
    delete[] data_;
    data_ = datanew_;
    size_--;
    return size_;
}

template <typename T>
void Array<T>::dump() const
{
    cout << "Array";
    cout << "\t{" << endl;
    cout << "\tsize_\t\t= " << size_ << endl;
    cout << "\tdata_ [" << size_ << "]:" << endl;
    cout << "\t\t{" << endl;
    for (unsigned int i = 0; i < size_; i++)
    {
        cout << "\t\t" << "[" << i << "] = " << data_[i] << endl;
    }
    cout << "\t\t}" << endl;
    cout << "\t}" << endl;
}

template <typename T>
bool Array<T>::resize(const size_t new_size)
{
    if (new_size < size_)
    {
        return false;
    }
    else
    {
        T *newdata_ = new T [new_size];

        for (unsigned int i = 0; i < size_; i++)
        {
            newdata_[i] = data_[i];
        }

        for (unsigned int i = size_; i < new_size; i++)
        {
            newdata_[i] = 0;
        }

        size_ = new_size;
        data_ = newdata_;

        return true;
    }

}

