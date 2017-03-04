#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

// шаблоны пока делать не будем
class Array
{
public:
    typedef value_type int;

    Array();
    Array(size_t size);
    Array(const Array& that); // Саша
    ~Array();

    size_t size() const { return size_; }

    bool empty() const;
    value_type& operator[](size_t n);
    const Array& operator=(const Array &that);
    const bool operator==(const Array &arr1, const Array &arr2); // Саша
    const Array operator+(const Array &arr1, const Array &arr2);
    const Array operator-(const Array &arr1, const Array &arr2);

    bool empty() const;
    value_type first() const;
    value_type last() const;
    value_type at(const size_t pos) const;  // Саша
    size_t erase(const size_t pos); // Саша
    size_t insert(const size_t pos, const value_type n); // Таня
    void dump() const; // Саша
    bool resize(const size_t new_size);

private:
    value_type *data_;

    size_t size_;
};


#endif // ARRAY_H_INCLUDED
