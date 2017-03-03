#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

class Array
{
private:
    int *pData;

    unsigned int nSize;
    unsigned int nReserve;

    Array() {};

    void clr();

public:
    Array(const unsigned int _nSize);
    Array (const Array& _copy);

    unsigned int getSize() const {return nSize;}
    int& operator[](const unsigned int _n);

    Array& operator=(const Array &_copy);
    void resize(const unsigned int _n);

    unsigned int add(const unsigned int _idx, const int _n);
    unsigned int remove(const unsigned int _idx);


    ~Array();
};


#endif // SMARTARRAY_H_INCLUDED
