/*!
    @file Stack.h
    @brief Реализация класса Stack
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#ifndef STACKH
#define STACKH

#include "Array.h"

template <typename T>
class Stack
{
public:

    Stack();
    Stack(size_t capacity);
    ~Stack();
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const;
    bool push(T value);
    T top() const;
    bool pop();
    bool ok() const;
    void dump() const;

private:
    static const int POISON_VAR = 660660;
    static const size_t def_capacity_ = 10;
    Array <T> data_;
    size_t size_;
    size_t capacity_;
};

#include "Stack.hpp"

#endif
