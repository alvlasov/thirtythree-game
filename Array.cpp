#include <cassert>
#include <cmath>
#include <iostream>
#include "Array.h"

using std::cout;
using std::endl;

Array::Array()
{

}

Array::Array(const Array& that);
{
    size_ = that.size();
    data_ = new value_type[size_];
    for (int i = 0; i < size_; i++)
    {
        data_[i] = that[i];
    }
}

Array::~Array();
{

}

Array::value_type& Array::operator[](size_t n);
{

}

const Array::Array& Array::operator=(const Array &that);
{

}

const bool Array::operator==(const Array &arr1, const Array &arr2);
{
    if (arr1.size() != arr2.size())
        return false;
    else
    {
        for (int i = 0; i < arr1.size(); i++)
        {
            if (arr1[i] != arr2[i])
                return false;
        }
    }
    return true;
}


Array::value_type Array::first() const;
{

}

Array::value_type Array::last() const;
{

}

Array::value_type Array::at(const size_t pos) const;
{
    if (pos >= size_)
        assert(0);
    else
    {
        return data_[pos];
    }
}

size_t Array::insert(const size_t pos, const value_type n);
{

}

size_t Array::erase(const size_t pos);
{
    if (pos >= size_)
    {
        assert(0);
    }
    value_type *dataNew_;
    dataNew_ = new value_type[size_-1];
    for (int i = 0; i < pos; i++)
    {
        dataNew_[i] = data_[i];
    }
    for (int i = pos+1; i < size_; i++)
    {
        dataNew_[i-1] = data_[i];
    }
    delete[] data_;
    data_ = dataNew_;
    size_--;
    return size_;
}

bool Array::resize()
{

}

void Array::dump() const
{
    cout << "Array";
    cout << "\t{" << endl;
    cout << "\tsize_\t\t= " << size_ << endl;
    cout << "\tdata_ [" << size_ << "]:" << endl;
    cout << "\t\t{" << endl;
    for (int i = 0; i < size_; i++)
    {
        cout << "\t\t" << "[" << i << "] = " << data_[i] << endl;
    }
    cout << "\t\t}" << endl;
    cout << "\t}" << endl;
}

