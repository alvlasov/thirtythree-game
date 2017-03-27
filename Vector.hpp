/*!
    @file Vector.hpp
    @brief Реализация класса Vector
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#include <cmath>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

namespace thirtythree
{

    template <typename T>
    Vector<T>::Vector():
        data_(NULL),
        size_(0)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    template <typename T>
    Vector<T>::Vector(size_t size):
        size_(size),
        data_(new T [reserve_])
    {
        for (Vector_iterator it = begin(); it != end(); ++it )
        {
            *it = 0;
        }

        cout << __PRETTY_FUNCTION__ << endl;
    }

    template <typename T>
    Vector<T>::Vector(const std::initializer_list<T>& init):
        size_(init.size()),
        data_(new T [reserve_])

    {
        std::copy(init.begin(), init.end(), data_);
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        cout << __PRETTY_FUNCTION__ << endl;

        delete [] data_;

        data_ = NULL;
        size_ = 0;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator =(const Vector &that)
    {
        if(&that == this)
            return *this;
        Vector victum(that);
        std::swap(size_,victum.size);
        std::swap(data_,victum.data);
        return *this;
    }


    template <typename T>
    Vector<T>::Vector(const Vector &that) :
        size_(that.size_),
        data_(new T [reserve_])
    {
        cout << __PRETTY_FUNCTION__ << endl;
        std::copy(that.data_, that.data_ + that.size_, data_);
    }


    template <typename T>
    bool operator ==(const Vector<T>& arr1, const Vector<T>& arr2)
    {
        if (arr1.size() != arr2.size())
                return false;
        else
        {
            for ( unsigned int i=0; i < arr1.size(); i++ )
            {
                if (arr1[i] != arr2[i])
                    return false;
            }
        }
        return true;
    }

    template <typename T>
    bool Vector<T>::empty() const
    {
        if (size_ == 0)
        {
            return true;
        }

        return false;
    }


    template <typename T>
    const T& Vector<T>::operator [](size_t n) const
    {
        if (!(0 <= n && n < size_))
        {
            throw 0;
        }

        return data_[n];
    }


    template <typename T>
    T& Vector<T>::operator [](size_t n)
    {
       return at(n);
    }

    template <typename T>
    Vector<T> operator +(const Vector<T> &arr1, const Vector<T> &arr2)
    {
        size_t arr_size = arr1.size() + arr2.size();

        Vector <T> new_Vector(arr_size);

        for (unsigned int i = 0; i < arr1.size(); i++ )
        {
            new_Vector[i] = arr1[i];
        }

        for (unsigned int i = arr1.size(); i < arr_size; i++ )
        {
            new_Vector[i] = arr2[i];
        }

        return new_Vector;
    }

    template <typename T>
    T Vector<T>::first() const
    {
        if (empty())
        {
            throw 0;
        }

        return data_[0];
    }

    template <typename T>
    T Vector<T>::last() const
    {
        if (empty())
        {
            throw 0;
        }

        return data_[size_-1];
    }

    template <typename T>
    T& Vector<T>::at(const size_t pos)
    {
        if (pos >= size_)
        {
            throw 0;
        }
        return data_[pos];
    }

    template <typename T>
    void Vector<T>::insert(const size_t pos, const T n)
    {
        if (pos >= reserve_)
        {
            throw 0;
        }
        T *newdata_ = new T [size_ - pos];

        for (unsigned int i = pos; i < size_; i++)
        {
            newdata_[i - pos] = data_[i];
        }

        data_[pos] = n;

        for (unsigned int i = pos + 1 ; i < size_; i++)
        {
              data_[i] = newdata_[i - pos - 1];
        }

        reserve_--;
    }

    template <typename T>
    size_t Vector<T>::erase(const size_t pos)
    {
        if (pos >= size_)
        {
            throw 0;
        }

        T *datanew_ = new T [size_-1];

        for (unsigned int i = 0 ; i < pos; i++)
        {
            datanew_[i] = data_[i];
        }

        for (unsigned int i = pos + 1; i < size_; i++)
        {
            datanew_[i-1] = data_[i];
        }
        delete[] data_;
        data_ = datanew_;
        size_--;
        return size_;
    }

    template <typename T>
    void Vector<T>::dump() const
    {
        cout << "Vector";
        cout << "\t{" << endl;
        cout << "\tsize_\t\t= " << size_ << endl;
        cout << "\tdata_ [" << size_ << "]:" << endl;
        cout << "\t\t{" << endl;
        for (unsigned int i = 0; i < size_; i++)
        {
            cout << "\t\t" << "[" << i << "] = " << data_[i] << endl;
        }
        cout << "\t\t}" << endl;
        cout << "\t}" << endl;
    }

    template <typename T>
    void Vector<T>::resize(const size_t new_size)
    {

        if (new_size <= reserve_)
        {
            size_ = new_size;
        }

        T *newdata_ = new int [new_size + 10];

        for (unsigned int i = 0; i < size_; i++)
        {
            newdata_[i] = data_[i];
        }

        delete [] data_;

        size_ = new_size;
        data_ = newdata_;

    }
