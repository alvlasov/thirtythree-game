#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

// шаблоны пока делать не будем
class Array
{
public:
    typedef value_type int;

    // конструктор по умолчанию выделяет память на capacity_step элементов
    Array(); // Алена
    Array(size_t size); // Таня
    Array(const Array& that); // Саша
    ~Array(); // Алена

    size_t size() const { return size_; }

    value_type& operator[](size_t n); // Алена
    const Array& operator=(const Array &that); // Таня
    const bool operator==(const Array &arr1, const Array &arr2); // Саша

    value_type first() const; // Алена
    value_type last() const; // Таня
    value_type at(const size_t pos) const;  // Саша
    size_t erase(const size_t pos); // Алена
    size_t insert(const size_t pos, const value_type n); // Таня
    bool dump() const; // Саша
    bool ok() const; // Алена

private:
    static const size_t capacity_step = 10;
    value_type *data_;

    // ресайзим массив сразу на capacity_step элементов
    bool resize(); // Таня

    size_t size_;
    size_t capacity_;
};


#endif // ARRAY_H_INCLUDED
