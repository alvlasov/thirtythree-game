/*!
    @file Smart_ptr.h
    @brief Реализация классов умных указателей
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#ifndef SMART_PTR_H_INCLUDED
#define SMART_PTR_H_INCLUDED

namespace thirtythree
{
    template <typename T>
    class my_auto_ptr
    {
        public:

            //! Конструкторы
            my_auto_ptr() :
                obj_(nullptr)
            { }

            explicit my_auto_ptr(T *obj) :
                obj_(obj)
            { }

            //! Деструктор
            ~my_auto_ptr()
            {
                delete obj_;
                obj_ = nullptr;
            }

            //! Перегруженный оператор ->
            //! @return Возвращает указатель на объект
            T* operator->() { return obj_; }

            //! Перегруженный оператор *
            //! @return объект, который он хранит
            T& operator* () { return *obj_; }

            //! Функция "перемещения" указателя
            T *Release()
            {
                T *result = obj_;
                obj_ = nullptr;
                return result;
            }

            //! Оператор присваивания с семантикой перемещения
            //! @param умный указатель that
            //! @return указатель на себя
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

            //! указатель на объект
            T* obj_;
    };

    template <typename T>
    class my_unique_ptr
    {
        public:

            //! Конструкторы
            my_unique_ptr ()
                : obj_(nullptr)
            { }

            explicit my_unique_ptr (T *obj)
                : obj_(obj)
            { }

            //! Деструктор
            ~my_unique_ptr() {
                delete obj_;
                obj_ = nullptr;
            }

            //! Перегруженный оператор ->
            //! @return Возвращает указатель на объект
            T* operator->() { return obj_; }

            //! Перегруженный оператор *
            //! @return объект, который он хранит
            T& operator* () { return *obj_; }

            //! Оператор присваивания без перемещения, принимает только временные объекты
            //! @param умный указатель that
            //! @return указатель на себя
            my_unique_ptr& operator=(my_unique_ptr  &&that)
            {
                std::swap(obj_, that.obj_);
                return *this;
            }


        private:

            //! указатель на объект
            T* obj_;
    };


    template <class T>
    class my_shared_ptr
    {

    public:
            //! Конструкторы
            my_shared_ptr() :
                obj_(nullptr),
                cnt_(nullptr)
            { }

            explicit my_shared_ptr(T* p) :
                obj_(p),
                cnt_(new int(1))
            { }

            //! Деструктор
            ~my_shared_ptr()
            {
                    if (cnt_ != nullptr && --*cnt_ == 0)
                    {
                            delete obj_;
                            delete cnt_;
                    }
            }

            //! Оператор присваивания с увеличением счетчика
            //! @param const my_shared_ptr &that
            //! @return ссылка на объект
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

            //! Оператор присваивания с удаляемым объектом
            //! @param my_shared_ptr Rvalue
            //! @return ссылка на объект
            my_shared_ptr& operator = (my_shared_ptr &&x)
            {
                    swap(x);
                    return *this;
            }

            //!Переопределение функции swap()
            //!@param my_shared_ptr &x
            void swap(my_shared_ptr &x)
            {
                    std::swap(obj_, x.obj_);
                    std::swap(cnt_, x.cnt_);
            }


            //! Перегруженный оператор ->
            //! @return Возвращает указатель на объект
            T* operator -> () const
            {
                    return obj_;
            }

            //! Перегруженный оператор *
            //! @return объект, который он хранит
            T& operator * () const
            {
                    return *obj_;
            }

            //! Функция обнуление указателей
            void reset()
            {
                    this->~shared_ptr();
                    obj_ = nullptr;
                    cnt_ = nullptr;
            }

    private:

        //! Указатель на объект
        T* obj_;

        //! Счетчик
        int *cnt_;
    };

}
#endif // SMART_PTR_H_INCLUDED
