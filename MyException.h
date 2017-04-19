/*!
    @file MyException.h
    @brief Реализация класса исключений
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Апрель 2017
*/

#ifndef MYEXCEPTION_H_INCLUDED
#define MYEXCEPTION_H_INCLUDED

namespace thirtythree
{
    class MyException: public std::exception
    {

    public:

        //! Конструктор исключения
        //! @param line -  строка исключения, func - функция, в которой было вызвано исключение, file - файл, msg - сообщение об исключении
        MyException(int line, const char *func, const char *file,  const char *msg, const MyException *other = nullptr)
        {
            if (other != nullptr)
            {
                exc_vect = other->exc_vect;
            }
            exc_vect.push_back(Data(line,  std::string(func), std::string(file), std::string(msg)));
        }

        //! Вывод содержания исключения
        //! Возвращает строку, в котором записана информация о вызванном исключении
        const std::string what() const
        {
            std::stringstream os;
            for(auto it : exc_vect)
            {
                os<<"On line: "<< it.line <<" In func: "<< it.func <<" In file: "<< it.file <<" Message: "<< it.msg <<"\n";
            }
            return os.str();
        }

    private:

        std::vector<Data> exc_vect;

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
            {}

            Data(int line_, string &&func_, string &&file_, string &&msg_) :
                line(line_),
                func(func_),
                file(file_),
                msg(msg_)
            {}

            //! Поля класса
            int line;
            string func;
            string file;
            string msg;

        };

    };
}
#endif // MYEXCEPTION_H_INCLUDED
