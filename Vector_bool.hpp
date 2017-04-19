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
        data_(0),
        size_(0),
        reserve_(0)
    {
        LOG_DEV(__PRETTY_FUNCTION__);
    }

    Vector<bool>::Vector(size_t size) :
        size_(size),
        reserve_(size_ + RESERVED_),
        data_(reserve_)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            *it = false;
        }
        LOG_DEV(__PRETTY_FUNCTION__);
    }

    Vector<bool>::Vector(const std::initializer_list<bool>& init):
        size_(init.size()),
        reserve_(size_ + RESERVED_),
        data_(reserve_)

    {
        bool *data = new bool [reserve_];
        std::copy(init.begin(), init.end(), data);
        int i = 0;
        for (iterator it = begin(); it != end(); it++)
        {
            *it = data[i++];
        }
        delete [] data;
        LOG_DEV(__PRETTY_FUNCTION__);
    }

    Vector<bool>::~Vector()
    {
        LOG_DEV(__PRETTY_FUNCTION__);

        size_ = 0;
    }

    Vector<bool>::Vector(const Vector<bool> &that) :
        size_(that.size_),
        reserve_(that.size_ + RESERVED_),
        data_(reserve_)
    {
        LOG_DEV(__PRETTY_FUNCTION__);
        int i = 0;
        for (iterator it = begin(); it != end(); it++)
        {
            *it = that[i++];
        }
    }

    size_t Vector<bool>::resize(const size_t new_size)
    {
        if (new_size < size_)
        {
            throw std::runtime_error("New size is smaller than current size");
        }

        if (new_size <= reserve_)
        {
            for (size_t i = size_; i < new_size; i++)
            {
                data_[i] = 0;
            }
            size_ = new_size;
            return size_;
        }

        data_.resize(new_size + RESERVED_);

        for (size_t i = size_; i < new_size; i++)
        {
            data_[i] = 0;
        }

        size_ = new_size;
        reserve_ = new_size + RESERVED_;
        return size_;
    }

    Bitset::reference Vector<bool>::at(const size_t pos)
    {
        if (pos >= size_)
        {
            throw std::runtime_error("Index out of bounds");
        }
        return data_[pos];
    }

    Bitset::reference Vector<bool>::operator [](size_t n)
    {
        return at(n);
    }

// Далее то же, что и в Vector.hpp

    bool operator ==(const Vector<bool>& arr1, const Vector<bool>& arr2)
    {
        if (arr1.size() != arr2.size())
        {
                return false;
        }
        for ( unsigned int i = 0; i < arr1.size(); i++ )
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
            throw std::runtime_error("Vector is empty");
        }
        return at(0);
    }

    bool Vector<bool>::last() const
    {
        if (empty())
        {
            throw std::runtime_error("Vector is empty");
        }
        return at(size_ - 1);
    }

    const bool Vector<bool>::at(const size_t pos) const
    {
        if (pos >= size_)
        {
            throw std::runtime_error("Index out of bounds");
        }
        return data_[pos];
    }

    size_t Vector<bool>::insert(const size_t pos, const bool n)
    {
        if (pos > size_)
        {
            throw std::runtime_error("Index out of bounds");
        }

        if (size_ == reserve_)
        {
            resize(size_);
        }

        for (size_t i = size_; i > pos; i--)
        {
            data_[i] = data_[i - 1];
        }

        data_[pos] = n;

        size_++;
        return size_;
    }

    size_t Vector<bool>::erase(const size_t pos)
    {
        if (pos >= size_)
        {
            throw std::runtime_error("Index out of bounds");
        }

        for (size_t i = pos; i < size_ - 1; i++)
        {
            data_[i] = data_[i + 1];
        }

        size_--;
        return size_;
    }

    void Vector<bool>::dump() const
    {
        cout << "Vector<bool>" << endl;
        cout << "\t{" << endl;
        cout << "\tsize_\t\t= " << size_ << endl;
        cout << "\treserve_\t\t= " << reserve_ << endl;
        cout << "\tdata_ [" << size_ << "]:" << endl;
        cout << "\t\t{" << endl;
        for (size_t i = 0; i < size_; i++)
        {
            cout << "\t\t" << "[" << i << "] = " << data_[i] << endl;
        }
        cout << "\t\t}" << endl;
        cout << "\t}" << endl;
    }

}


