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

    Stack();
    Stack(size_t capacity);
    ~Stack();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    bool push(value_type value);
    value_type top() const;
    bool pop();
    bool ok() const;
    bool dump() const;

private:
    static const int POISON_VAR = 666666;
    static const size_t def_capacity_ = 10;
    value_type *data_;
    size_t size_;
    size_t capacity_;
};
#endif
