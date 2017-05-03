/*!
    @file MyException.h
    @brief Реализация класса исключений
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Апрель 2017
*/

#ifndef MYEXCEPTION_H_INCLUDED
#define MYEXCEPTION_H_INCLUDED

#include <sstream>
#include <string>

namespace thirtythree
{
    class MyException: public std::exception
    {

    public:

        //! Конструктор с хранением предыдущего исключения
        //! @param line -  строка исключения, func - функция, в которой было вызвано исключение, file - файл, msg - сообщение об исключении
        MyException(int line, const char *func, const char *file, const char *msg, MyException *prev_exception) :
            line_ (line),
            number_ ((*prev_exception).number_ + 1),
            func_ (func),
            file_ (file),
            msg_ (msg),
            prev_exception_ (prev_exception)
        {
        }

        //! Конструктор
        //! @param line -  строка исключения, func - функция, в которой было вызвано исключение, file - файл, msg - сообщение об исключении
        MyException(int line, const char *func, const char *file, const char *msg) :
            line_ (line),
            number_ (1),
            func_ (func),
            file_ (file),
            msg_ (msg),
            prev_exception_ (nullptr)
        {
        }

        ~MyException()
        {
            LOG_INFO("MyException " << number_ << " destroyed");

            if (prev_exception_ != nullptr)
            {
                delete prev_exception_;
            }
        }

        //! Вывод содержания исключения
        //! Возвращает строку, в котором записана информация о вызванном исключении
        const std::string what()
        {
            std::stringstream os;
            os << "Exception " << number_ << " thrown:\n\tLine: " << line_ << "\n\tFunc: " << func_ << "\n\tFile: " << file_ << "\n\tMessage: " << msg_ << "\n";
            if (prev_exception_ != nullptr)
            {
                os << prev_exception_->what();
            }
            return os.str();
        }

    private:

        int line_;
        int number_;
        std::string func_;
        std::string file_;
        std::string msg_;

        MyException *prev_exception_;
    };
}
#endif // MYEXCEPTION_H_INCLUDED
