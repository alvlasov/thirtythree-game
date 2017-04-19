/*!
    @file CPU.h
    @brief Реализация простого ассемблера
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Апрель 2017
*/

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <vector>
#include <stack>
#include <map>

namespace thirtythree
{
    //! Перечисление поддерживаемых команд
    enum { END_CMD, MULT_CMD, PUSH_CMD, ADD_CMD, PUSH_CONST_CMD, DIV_CMD, POP_CMD, JMP_CMD, MARK_CMD, JE_CMD, JG_CMD, JGE_CMD, JL_CMD, JLE_CMD, JNE_CMD, CALL_CMD, RET_CMD};

    class CPU
    {
    public:

        //! Конструктор, принимающий число регистров
        //! @param registersCount Число регистров, по умолчанию defRegistersCount_
        CPU(size_t registersCount = defRegistersCount_);

        //! Конструктор, принимающий вектор регистров
        //! @param registers Содержимое регистров
        CPU(std::vector<double> registers);

        //! Конструктор, принимающий имя файла и число регистров
        //! @param filename Имя файла с кодом
        //! @param registersCount Число регистров, по умолчанию defRegistersCount_
        CPU(char *filename, size_t registersCount = defRegistersCount_);

        //! Конструктор, принимающий имя файла и вектор регистров
        //! @param filename Имя файла с кодом
        //! @param registers Содержимое регистров
        CPU(char *filename, std::vector<double> registers);

        //! Конструктор, принимающий код и число регистров
        //! @param code Вектор с кодом
        //! @param registersCount Число регистров, по умолчанию defRegistersCount_
        CPU(std::vector<int> code, size_t registersCount = defRegistersCount_);

        //! Конструктор, принимающий код и вектор регистров
        //! @param code Вектор с кодом
        //! @param registers Содержимое регистров
        CPU(std::vector<int> code, std::vector<double> registers);

        //! Деструктор (пустой)
        ~CPU();

        //! Считывает код из файла и транслирует его
        //! @param filename Имя файла с кодом
        void readCode(char *filename);

        //! Считывает код из вектора без трансляции
        //! @param code Вектор с кодом
        void setCode(std::vector<int> code) { code_ = code; }

        //! Считывает содержимое регистров из вектора
        //! @param registers Содержимое регистров
        void setAllRegisters(std::vector<double> registers) { registers_ = registers; }

        //! Изменяет значение конкретного регистра
        //! @param value Новое значение регистра
        //! @param pos Номер регистра
        void setRegister(double value, size_t pos) { registers_[pos] = value; }

        //! Возвращает в виде вектора содержимое регистров
        //! @return Содержимое регистров
        std::vector<double> readAllRegisters() { return registers_; }

        //! Возвращает содержимое одного регистра
        //! @param pos Номер регистра
        //! @return Содержимое регистра
        double readRegister(size_t pos) { return registers_.at(pos); }

        //! Обращение к регистрам через []
        //! @param pos Индекс регистра
        //! @return Ссылку на значение регистра
        double& operator [](size_t pos) { return registers_.at(pos); }

        //! Возвращает количество регистров
        //! @return Количество регистров
        size_t registersCount() { return registers_.size(); }

        //! Исполняет транслированный код
        void execute();

    private:

        //! Число регистров по умолчанию
        static const size_t defRegistersCount_ = 8;

        //! Стек процессора
        std::stack<double> stack_;

        //! Стек возвратов процессора
        std::stack<int> return_;

        //! Исполняемый код
        std::vector<int> code_;

        //! Регистры
        std::vector<double> registers_;

        //! Словарь меток
        std::map<int, int> marks_;

        //! Служебная функция, заполняющяя словарь меток
        void mark();

    };
}

#endif // CPU_H_INCLUDED
