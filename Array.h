#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

typedef int value_type;

class Array
{
public:

    Array();
    explicit Array(size_t size);
    Array(Array& that);
    ~Array();

    size_t size() const { return size_; }

    bool empty() const;
    value_type& operator [](size_t n);
    Array& operator =(Array &that);
    bool empty_() const;
    value_type first() const;
    value_type last() const;
    value_type at(const size_t pos) const;
    size_t erase(const size_t pos);
    size_t insert(const size_t pos, const value_type n);
    void dump() const;
    bool resize(const size_t new_size);

private:
    value_type *data_;

    size_t size_;
};

bool operator ==(const Array &arr1, const Array &arr2);
Array operator +(const Array &arr1, const Array &arr2);
Array operator-(const Array &arr1, const Array &arr2);
#endif // ARRAY_H_INCLUDED
