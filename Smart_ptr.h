/*!
    @file Smart_ptr.h
    @brief ���������� ������� ����� ����������
    @author ������ ���������, ������� ���������, ����� ����������
    @date ���� 2017
*/

#ifndef SMART_PTR_H_INCLUDED
#define SMART_PTR_H_INCLUDED

namespace thirtythree
{
    template <typename T>
    class my_auto_ptr
    {
        public:

            //! ������������
            my_auto_ptr() :
                obj_(nullptr)
            { }

            explicit my_auto_ptr(T *obj) :
                obj_(obj)
            { }

            //! ����������
            ~my_auto_ptr()
            {
                delete obj_;
                obj_ = nullptr;
            }

            //! ������������� �������� ->
            //! @return ���������� ��������� �� ������
            T* operator->() { return obj_; }

            //! ������������� �������� *
            //! @return ������, ������� �� ������
            T& operator* () { return *obj_; }

            //! ������� "�����������" ���������
            T *Release()
            {
                T *result = obj_;
                obj_ = nullptr;
                return result;
            }

            //! �������� ������������ � ���������� �����������
            //! @param ����� ��������� that
            //! @return ��������� �� ����
            my_auto_ptr &operator=(my_auto_ptr &that)
            {
                if (&that != this)
                {
                    this->~my_auto_ptr();
                    obj_ = that.Release();
                }

                return *this;
            }

        private:

            //! ��������� �� ������
            T* obj_;
    };

    template <typename T>
    class my_unique_ptr
    {
        public:

            //! ������������
            my_unique_ptr ()
                : obj_(nullptr)
            { }

            explicit my_unique_ptr (T *obj)
                : obj_(obj)
            { }

            //! ����������
            ~my_unique_ptr() {
                delete obj_;
                obj_ = nullptr;
            }

            //! ������������� �������� ->
            //! @return ���������� ��������� �� ������
            T* operator->() { return obj_; }

            //! ������������� �������� *
            //! @return ������, ������� �� ������
            T& operator* () { return *obj_; }

            //! �������� ������������ ��� �����������, ��������� ������ ��������� �������
            //! @param ����� ��������� that
            //! @return ��������� �� ����
            my_unique_ptr& operator=(my_unique_ptr  &&that)
            {
                std::swap(obj_, that.obj_);
                return *this;
            }


        private:

            //! ��������� �� ������
            T* obj_;
    };


    template <class T>
    class my_shared_ptr
    {

    public:
            //! ������������
            my_shared_ptr() :
                obj_(nullptr),
                cnt_(nullptr)
            { }

            explicit my_shared_ptr(T* p) :
                obj_(p),
                cnt_(new int(1))
            { }

            //! ����������
            ~my_shared_ptr()
            {
                    if (cnt_ != nullptr && --*cnt_ == 0)
                    {
                            delete obj_;
                            delete cnt_;
                    }
            }

            //! �������� ������������ � ����������� ��������
            //! @param const my_shared_ptr &that
            //! @return ������ �� ������
            my_shared_ptr& operator = (const my_shared_ptr &that)
            {
                    if (this != &that) {
                            reset();
                            obj_= that.obj_;
                            cnt_ = that.cnt_;
                            ++*cnt_;
                    }
                    return *this;
            }

            //! �������� ������������ � ��������� ��������
            //! @param my_shared_ptr Rvalue
            //! @return ������ �� ������
            my_shared_ptr& operator = (my_shared_ptr &&x)
            {
                    swap(x);
                    return *this;
            }

            //!��������������� ������� swap()
            //!@param my_shared_ptr &x
            void swap(my_shared_ptr &x)
            {
                    std::swap(obj_, x.obj_);
                    std::swap(cnt_, x.cnt_);
            }


            //! ������������� �������� ->
            //! @return ���������� ��������� �� ������
            T* operator -> () const
            {
                    return obj_;
            }

            //! ������������� �������� *
            //! @return ������, ������� �� ������
            T& operator * () const
            {
                    return *obj_;
            }

            //! ������� ��������� ����������
            void reset()
            {
                    this->~shared_ptr();
                    obj_ = nullptr;
                    cnt_ = nullptr;
            }

    private:

        //! ��������� �� ������
        T* obj_;

        //! �������
        int *cnt_;
    };

}
#endif // SMART_PTR_H_INCLUDED
