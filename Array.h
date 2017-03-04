#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

// шаблоны пока делать не будем
class Array
{
public:
    typedef value_type int;

    Array(); // конструктор по умолчанию выделяет память на capacity_step элементов
    Array(const Array& that);
    ~Array();

    size_t size() const { return size_; }

    value_type& operator[](size_t n);
    const Array& operator=(const Array &that);
    const bool operator==(const Array &arr1, const Array &arr2);

    value_type first() const;
    value_type last() const;
    value_type at(const size_t pos) const;
    size_t insert(const size_t pos, const value_type n);
    size_t erase(const size_t pos);

private:
    static const size_t capacity_step = 10;
    value_type *data_;

    bool resize(); // ресайзим массив сразу на capacity_step элементов

    size_t size_;
    size_t capacity_;
};


#endif // ARRAY_H_INCLUDED
