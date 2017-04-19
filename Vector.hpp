/*!
    @file Vector.hpp
    @brief Реализация класса Vector
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

namespace thirtythree
{

    template <typename T>
    Vector<T>::Vector() :
        data_(nullptr),
        size_(0),
        reserve_(0)
    {
        LOG_DEV(__PRETTY_FUNCTION__);
    }

    template <typename T>
    Vector<T>::Vector(size_t size) :
        size_(size),
        reserve_(size_ + RESERVED_),
        data_(new T [reserve_])
    {
        for (iterator it = begin(); it != end(); ++it )
        {
            *it = 0;
        }
        LOG_DEV(__PRETTY_FUNCTION__);
    }

    template <typename T>
    Vector<T>::Vector(const std::initializer_list<T>& init):
        size_(init.size()),
        reserve_(size_ + RESERVED_),
        data_(new T [reserve_])

    {
        std::copy(init.begin(), init.end(), data_);
        LOG_DEV(__PRETTY_FUNCTION__);
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        LOG_DEV(__PRETTY_FUNCTION__);

        delete [] data_;

        data_ = NULL;
        size_ = 0;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator =(const Vector &that)
    {
        if (&that == this)
        {
            return *this;
        }
        Vector <T> victim(that);
        std::swap(size_, victim.size_);
        std::swap(reserve_, victim.reserve_);
        std::swap(data_, victim.data_);
        return *this;
    }

    template <typename T>
    Vector<T>::Vector(const Vector &that) :
        size_(that.size_),
        reserve_(that.size_ + RESERVED_),
        data_(new T [reserve_])
    {
        LOG_DEV(__PRETTY_FUNCTION__);
        std::copy(that.data_, that.data_ + that.size_, data_);
    }

    template <typename T>
    bool operator ==(const Vector<T>& arr1, const Vector<T>& arr2)
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
        return at(n);
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
            new_Vector[i] = arr2[i - arr1.size()];
        }
        return new_Vector;
    }

    template <typename T>
    T Vector<T>::first() const
    {
        if (empty())
        {
            throw std::runtime_error("Vector is empty");
        }

        return at(0);
    }

    template <typename T>
    T Vector<T>::last() const
    {
        if (empty())
        {
            throw std::runtime_error("Vector is empty");
        }

        return at(size_ - 1);
    }

    template <typename T>
    T& Vector<T>::at(const size_t pos)
    {
        if (pos >= size_)
        {
            throw std::runtime_error("Index out of bounds");
        }
        return data_[pos];
    }

    template <typename T>
    const T& Vector<T>::at(const size_t pos) const
    {
        if (pos >= size_)
        {
            throw std::runtime_error("Index out of bounds");
        }
        return data_[pos];
    }

    template <typename T>
    size_t Vector<T>::insert(const size_t pos, const T n)
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

    template <typename T>
    size_t Vector<T>::erase(const size_t pos)
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

    template <typename T>
    void Vector<T>::dump() const
    {
        cout << "Vector";
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

    template <typename T>
    size_t Vector<T>::resize(const size_t new_size)
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

        T *newdata_ = new T [new_size + RESERVED_];

        for (size_t i = 0; i < size_; i++)
        {
            newdata_[i] = data_[i];
        }

        for (size_t i = size_; i < new_size; i++)
        {
            newdata_[i] = 0;
        }

        delete [] data_;

        size_ = new_size;
        reserve_ = new_size + RESERVED_;
        data_ = newdata_;
        return size_;
    }

}
