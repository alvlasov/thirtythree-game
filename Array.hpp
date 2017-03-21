/*!
    @file Array.hpp
    @brief Реализация класса Array
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#include <cmath>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::copy;
using std::swap;


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
Array<T>::~Array()
{
    cout << __PRETTY_FUNCTION__ << endl;

    delete [] data_;

    data_ = NULL;
    size_ = 0;
}

template <typename T>
<<<<<<< Updated upstream:Array.hpp
Array<T>& Array<T>::operator =(const Array &that)
{
    if(&that == this)
        return *this;
    Array victum(that);
    std::swap(size_,victum.size);
    std::swap(data_,victum.data);
    return *this;
}

template <typename T>
void* Array<T>::operator new(size_t size)
{
    return malloc(size);
}

template <typename T>
Array<T>::Array(const Array &that) :
    size_(that.size_),
    data_(new T [that.size_])
{
    cout << __PRETTY_FUNCTION__ << endl;
    std::copy(that.data_, that.data_ + that.size_, data_);
=======
const Array<T>& Array<T>::operator =(const Array &that)
{
    if (&that == this) return *this;
    Array victum(that);
    swap(size_, victum.size_);
    swap(data_,victum.data);
}

void* Array<T>& Array<T>::operator new(size_t size,size_t n)
{
    cout<< &n << endl;
    return malloc(size *n);
>>>>>>> Stashed changes:Array.cpp
}

template <typename T>
Array::Array(const Array& that)
{
    size_(that.size);
    data_(new value_type [that.size]);
    copy(that.data_, that.data_+that.size_,data_);
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
T& Array<T>::operator [](size_t n)
{
    if (!(0 <= n && n < size_))
    {
        throw 0;
    }

    return data_[n];
}

template <typename T>
Array<T> operator +(const Array<T> &arr1, const Array<T> &arr2)
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
Array<T> operator -(const Array<T> &arr1, const Array<T> &arr2)
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

