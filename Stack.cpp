//--------------------------------------------------
//! @file Stack.cpp
//! Implements a stack class
//!
//! @author Vlasov Alexander, Feb. 2017
//--------------------------------------------------

#include <cassert>
#include <iostream>
#include "Stack.h"

#define ASSERT_OK() \
    if (!ok())      \
    {               \
        dump();     \
        assert(0);  \
    }               \

using std::cout;
using std::endl;

class Stack;

Stack::Stack(size_t capacity = def_capacity_) :
    size_(0),
    capacity_(capacity)
{
    data_ = new value_type[capacity];
}

Stack::~Stack()
{
    delete[] data_;
    size_ = POISON_VAR;
    capacity_ = 1;
}

size_t Stack::size() const
{
    return size_;
}

size_t Stack::capacity() const
{
    return capacity_;
}

bool Stack::empty() const
{
    return (size() == 0);
}

bool Stack::push(value_type value)
{
    ASSERT_OK();
    if (size_>=capacity())
        return false;
    data_[size_++] = value;
    ASSERT_OK();
    return true;
}

Stack::value_type Stack::top() const
{
    ASSERT_OK();
    if (size()!=0)
        return data_[size_-1];
    else
        assert(!"Stack is empty!");
}

bool Stack::pop()
{
    ASSERT_OK();
    if (size()!=0)
    {
        data_[--size_] = POISON_VAR;
        ASSERT_OK();
        return true;
    }
    return false;
}

bool Stack::ok() const
{
    return (size() <= capacity());
}

bool Stack::dump() const
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
    for (int i=0; i<capacity(); i++)
    {
        if (i<size())
            cout << "\t*\t" << "[" << i << "] = " << data_[i];
        else
            cout << "\t\t" << "[" << i << "] = " << data_[i];
        if (data_[i] == POISON_VAR)
            cout << " (POISON_VAR)" << endl;
        else
            cout << endl;
    }
    cout << "\t\t}" << endl;
    cout << "\t}" << endl;
}
