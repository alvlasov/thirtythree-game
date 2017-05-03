/*!
    @file Smart_ptr.h
    @brief Реализация классов умных указателей
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Март 2017
*/

#ifndef SMART_PTR_H_INCLUDED
#define SMART_PTR_H_INCLUDED

#include <stdexcept>

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
            T* operator->()
            {
                return obj_;
            }

            //! Перегруженный оператор *
            //! @return объект, который он хранит
            T& operator* ()
            {
                if (obj_ == nullptr)
                {
                    throw std::runtime_error("Nullptr access");
                }
                return *obj_;
            }

            //! Функция "перемещения" указателя
            T* release()
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
                    obj_ = that.release();
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
            T& operator* ()
            {
                if (obj_ == nullptr)
                {
                    throw std::runtime_error("Nullptr access");
                }
                return *obj_;
            }

            //! Функция "перемещения" указателя
            T* release()
            {
                T *result = obj_;
                obj_ = nullptr;
                return result;
            }

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

        //! Блок управления
        struct control_block
        {
            //! Указатель на объект
            T* obj_;

            //! Счетчик ссылок на объект
            int *cnt_;

            //! Конструкторы
            control_block() :
                obj_(nullptr),
                cnt_(new int(0))
                { }

            control_block(T* p) :
                obj_(p),
                cnt_(new int(1))
                { }

            //! Функция удаления
            void del_control_block()
            {
                if (cnt_ != nullptr && *cnt_ == 1)
                    {
                            delete obj_;
                            delete cnt_;
                            obj_ = nullptr;
                            cnt_ = nullptr;
                    }
                    else
                    {
                        (*cnt_)--;
                    }
            }

        };

            //! Конструкторы
            my_shared_ptr() :
                object_(nullptr),
                block_(new control_block)
            { }

            explicit my_shared_ptr(T* p) :
                object_(p),
                block_(new control_block(p))
            { }

            //! Деструктор с уменьшением счетчика
            ~my_shared_ptr()
            {
                block_->del_control_block();
                if (block_->cnt_ == nullptr )
                {
                    delete object_;
                    object_ = nullptr;
                }
            }

            //! Оператор присваивания с увеличением счетчика
            //! @param const my_shared_ptr &that
            //! @return ссылка на объект
            my_shared_ptr& operator = (const my_shared_ptr &that)
            {
                    if (this != &that)
                    {
                            reset();
                            object_= that.object_;
                            block_ = that.block_;
                            ++*(block_->cnt_);
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
            //!@param my_shared_ptr &that
            void swap(my_shared_ptr &that)
            {
                    std::swap(object_, that.object_);
                    std::swap(block_, that.block_);
            }


            //! Перегруженный оператор ->
            //! @return Возвращает указатель на объект
            T* operator -> () const
            {
                if (object_ == nullptr)
                {
                    throw std::runtime_error("Nullptr access");
                }
                return object_;
            }

            //! Перегруженный оператор *
            //! @return объект, который он хранит
            T& operator * () const
            {
                return *object_;
            }

            //! Функция обнуление указателей
            void reset()
            {
                    this->~my_shared_ptr();
                    object_ = nullptr;
                    block_ = nullptr;
            }

            bool unique()
            {
                return (*(block_->cnt_) == 1);
            }


    private:

        //! Указатель на объект
        T* object_;

        //! Блок управления
        control_block* block_;
    };
}
#endif // SMART_PTR_H_INCLUDED
