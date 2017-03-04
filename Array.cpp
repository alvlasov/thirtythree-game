#include <cassert>
#include <cmath>
#include "Array.h"
#include <iostream>

Array::Array():
    data_(nullptr);
    size_=0;
{
    cout << __PRETTY_FUNCTION__ << endl;
}


Array::Array(size_t size) :
    data_(new value_type [size]),
    size_(size),
{
    for (unsigned int i = 0; i < size_; i++ )
    {
        data_[i] = 0;
    }
}

Array::Array(const Array& that)
{

}

Array::~Array()
{
    delete [] data_;
    data_ = NULL;
    size_ = 0;
}


const Array& Array::operator=(const Array &that)
{
    this -> resize(that.size());

    for (unsigned int i = 0; i < size_; i++ )
    {
        data_[i] = that.data_[i];
    }

    return *this;
}

const bool Array::operator==(const Array &arr1, const Array &arr2)
{
  
}

bool Array::empty() const
{
    if (size_ == 0) {
        return true;
    }
    return false;
}

value_type& Array::operator[](size_t n)
{
    assert(0 <= index && index < size_);
    return data_[index];
}



const Array Array::operator+(const Array &arr1, const Array &arr2)
{
    if (arr1.size() != arr2.size())
    {
        assert(0);
    }

    size_t arr_size = arr1.size();

    Array new_array(arr_size);

    for (unsigned int i = 0; i < arr_size; i++ )
    {
        new_array.data_[i] = arr1.data_[i] + arr2.data_[i];
    }

    return new_array;
}

const Array Array::operator-(const Array &arr1, const Array &arr2)
{
    if (arr1.size() != arr2.size())
    {
        assert(0);
    }

    size_t arr_size = arr1.size();

    Array new_array(arr_size);

    for (unsigned int i = 0; i < arr_size; i++ )
    {
        new_array.data_[i] = arr1.data_[i] - arr2.data_[i];
    }
  
    return new_array;
}


value_type Array::first() const
{
    if (empty())
    {
        assert(0);
    }
    return data_[0];
}

value_type Array::last() const
{
    if (empty())
    {
        assert(0);
    }

    return data_[size_-1];
}

value_type Array::at(const size_t pos) const
{

}

size_t Array::insert(const size_t pos, const value_type n)
{

    if (pos >= size_)
    {
        assert(0);
    }

    value_type *newdata_ = new value_type [size_ - pos];

    for (unsigned int i = pos ; i < size_; i++)
    {
        newdata_[i - pos ] = data_[i];
    }

    data_[pos] = n;

    this ->resize(size_+1);

    for (unsigned int i = pos + 1; i < size_; i++)
    {
          data_[i] = newdata_[i - pos - 1];
    }


    return size_;
}

size_t Array::erase(const size_t pos)
{

}

bool Array::resize(const size_t new_size)
{
    if (new_size < size_)
    {
        return false;
    }
    else
    {
        value_type *newdata_ = new value_type [new_size];

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

bool Array::dump() const
{

}

