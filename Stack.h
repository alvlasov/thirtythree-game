//--------------------------------------------------
//! @file Stack.h
//! Implements a stack class
//!
//! @author Vlasov Alexander, Feb. 2017
//--------------------------------------------------

#ifndef STACKH
#define STACKH

class Stack
{
public:

    typedef float value_type;

    Stack(size_t capacity);
    ~Stack();
    size_t size();
    size_t capacity();
    bool empty();
    bool push(value_type value);
    value_type top();
    bool pop();
    bool ok();
    bool dump();

private:
    static const int POISON_VAR = 666666;
    static const size_t def_capacity_ = 10;
    value_type *data_;
    size_t size_;
    size_t capacity_;
};
#endif
