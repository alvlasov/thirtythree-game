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

        //! Конструктор исключения
        //! @param line -  строка исключения, func - функция, в которой было вызвано исключение, file - файл, msg - сообщение об исключении
        MyException(int line, const char *func, const char *file,  const char *msg, const MyException *other = nullptr):
        Data(line,  std::string(func), std::string(file), std::string(msg))
        {
            if (other != nullptr)
            {
                last_exception = new MyException(other->Data.line, other->Data.func, other->Data.file, other->Data.msg);
            }
        }

        //! Вывод содержания исключения
        //! Возвращает строку, в котором записана информация о вызванном исключении
        const std::string what()
        {
            std::stringstream os;
            os << "On line: "<< line <<" In func: "<< func <<" In file: "<< file <<" Message: "<< msg <<"\n";
            os << "Last exception on line: "<< last_exception->Data.line <<" In func: "<< last_exception->Data.func <<" In file: "<< last_exception->Data.file <<" Message: "<< last_exception->Data.msg <<"\n";
            return os.str();
        }

    private:

        //! Содержание исключения: строка, функция, файл, в котором вызвалось исключение, и сообщение об исключении
        class Data
        {
        public:
            //! Конструкторы
            Data() :
                line(0),
                func(""),
                file(""),
                msg("")
            { }

            Data(int line_, std::string &&func_, std::string &&file_, std::string &&msg_) :
                line(line_),
                func(func_),
                file(file_),
                msg(msg_)
            {
            }

            //! Поля класса
            int line;
            std::string func;
            std::string file;
            std::string msg;

        };

        MyException* last_exception;
    };
}
#endif // MYEXCEPTION_H_INCLUDED
