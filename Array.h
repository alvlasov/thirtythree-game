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

    bool empty() const;
    value_type& operator[](size_t n); // Алена
    const Array& operator=(const Array &that); // Таня
    const bool operator==(const Array &arr1, const Array &arr2); // Саша

    value_type first() const; // Алена
    value_type last() const; // Таня
    value_type at(const size_t pos) const;  // Саша
    size_t erase(const size_t pos); // Саша
    size_t insert(const size_t pos, const value_type n); // Таня
    void dump() const; // Саша

private:
    value_type *data_;

    bool resize(); // Таня

    size_t size_;
};


#endif // ARRAY_H_INCLUDED
