#include <cassert>
#include <cmath>
#include "Array.h"
#include <iostream>

Array::Array()
{
    size_=0;
    cout << __PRETTY_FUNCTION__ << endl;
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

bool Array::empty() const
{
    if (size_ == 0) {
        return true;
    }
    return false;
}

Array::value_type& Array::operator[](size_t n)
{
assert(0 <= index && index < size_);
return data_[index];
}

const Array::Array& Array::operator=(const Array &that)
{

}

const bool Array::operator==(const Array &arr1, const Array &arr2)
{

}


Array::value_type Array::first() const
{
    if (empty())
    {
        assert(0);
    }
    return data_[0];
}

Array::value_type Array::last() const
{

}

Array::value_type Array::at(const size_t pos) const
{

}

size_t Array::insert(const size_t pos, const value_type n)
{

}

size_t Array::erase(const size_t pos)
{

}

bool Array::resize()
{

}

bool Array::dump() const
{

}

