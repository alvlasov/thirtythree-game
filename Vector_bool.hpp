/*!
    @file Vector_bool.hpp
    @brief Реализация частичной специализации шаблона класса Vector <bool>
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Апрель 2017
*/

#include <cmath>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

namespace thirtythree
{

    Vector<bool>::Vector() :
        data_(nullptr),
        size_(0),
        reserve_(0)
    {
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;
    }

    Vector<bool>::Vector(size_t size) :
        size_(size),
        reserve_(size_ + RESERVED_),
        data_(new Bitset(reserve_))
    {
        for (size_t i = 0; i < size_; i++)
        {
            (*data_)[i] = false;
        }
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;
    }

    Vector<bool>::Vector(const std::initializer_list<bool>& init):
        size_(init.size()),
        reserve_(size_ + RESERVED_),
        data_(new Bitset(reserve_))

    {
        bool *data = new bool [reserve_];
        std::copy(init.begin(), init.end(), data);
        for (size_t i = 0; i < size_; i++)
        {
            (*data_)[i] = data[i];
        }
        delete [] data;
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;
    }


    Vector<bool>::~Vector()
    {
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;

        delete data_;

        data_ = NULL;
        size_ = 0;
    }


    Vector<bool>::Vector(const Vector<bool> &that) :
        size_(that.size_),
        reserve_(that.size_ + RESERVED_),
        data_(new Bitset(reserve_))
    {
        if (DEV_MESSAGES)
            cout << __PRETTY_FUNCTION__ << endl;
        for (size_t i = 0; i < size_; i++)
        {
            (*data_)[i] = (*that.data_)[i];
        }
    }

    size_t Vector<bool>::resize(const size_t new_size)
    {
        if (new_size < size_)
        {
            throw 1;
        }

        if (new_size <= reserve_)
        {
            for (size_t i = size_; i < new_size; i++)
            {
                (*data_)[i] = 0;
            }
            size_ = new_size;
            return size_;
        }

        Bitset *newdata_ = new Bitset(new_size + RESERVED_);

        for (size_t i = 0; i < size_; i++)
        {
            (*newdata_)[i] = (*data_)[i];
        }

        for (size_t i = size_; i < new_size; i++)
        {
            (*newdata_)[i] = 0;
        }

        delete data_;

        size_ = new_size;
        reserve_ = new_size + RESERVED_;
        data_ = newdata_;
        return size_;
    }

// Далее то же, что и в Vector.hpp

    bool operator ==(const Vector<bool>& arr1, const Vector<bool>& arr2)
    {
        if (arr1.size() != arr2.size())
        {
                return false;
        }
        for ( unsigned int i=0; i < arr1.size(); i++ )
        {
            if (arr1[i] != arr2[i])
            {
                return false;
            }
        }
        return true;
    }

    bool Vector<bool>::empty() const
    {
        if (size_ == 0)
        {
            return true;
        }

        return false;
    }

    const bool Vector<bool>::operator [](size_t n) const
    {
        return at(n);
    }

    Bitset::reference Vector<bool>::operator [](size_t n)
    {
       return at(n);
    }

    Vector<bool> operator +(const Vector<bool> &arr1, const Vector<bool> &arr2)
    {
        size_t arr_size = arr1.size() + arr2.size();
        Vector <bool> new_Vector(arr_size);
        for (unsigned int i = 0; i < arr1.size(); i++ )
        {
            new_Vector[i] = arr1[i];
        }

        for (unsigned int i = arr1.size(); i < arr_size; i++ )
        {
            new_Vector[i] = arr2[i - arr1.size()];
        }
        return new_Vector;
    }

    bool Vector<bool>::first() const
    {
        if (empty())
        {
            throw 0;
        }
        return at(0);
    }

    bool Vector<bool>::last() const
    {
        if (empty())
        {
            throw 0;
        }
        return at(size_ - 1);
    }

    Bitset::reference Vector<bool>::at(const size_t pos)
    {
        if (pos >= size_)
        {
            throw 0;
        }
        return (*data_)[pos];
    }

    const bool Vector<bool>::at(const size_t pos) const
    {
        if (pos >= size_)
        {
            throw 0;
        }
        return (*data_)[pos];
    }

    size_t Vector<bool>::insert(const size_t pos, const bool n)
    {
        if (pos > size_)
        {
            throw 0;
        }

        if (size_ == reserve_)
        {
            resize(size_);
        }

        for (size_t i = size_; i > pos; i--)
        {
            (*data_)[i] = (*data_)[i - 1];
        }

        (*data_)[pos] = n;

        size_++;
        return size_;
    }

    size_t Vector<bool>::erase(const size_t pos)
    {
        if (pos >= size_)
        {
            throw 0;
        }

        for (size_t i = pos; i < size_ - 1; i++)
        {
            (*data_)[i] = (*data_)[i + 1];
        }

        size_--;
        return size_;
    }

    void Vector<bool>::dump() const
    {
        cout << "Vector";
        cout << "\t{" << endl;
        cout << "\tsize_\t\t= " << size_ << endl;
        cout << "\treserve_\t\t= " << reserve_ << endl;
        cout << "\tdata_ [" << size_ << "]:" << endl;
        cout << "\t\t{" << endl;
        for (unsigned int i = 0; i < size_; i++)
        {
            cout << "\t\t" << "[" << i << "] = " << (*data_)[i] << endl;
        }
        cout << "\t\t}" << endl;
        cout << "\t}" << endl;
    }


}


