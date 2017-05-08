/*!
    @file ScriptingUnit.h
    @brief Реализация простого ассемблера и CPU
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#ifndef ScriptingUnit_H_INCLUDED
#define ScriptingUnit_H_INCLUDED

#include "GlobalOptions.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <stack>
#include <map>
#include <functional>

namespace thirtythree {
//! Перечисление поддерживаемых команд


class ScriptingUnit {
public:

    struct Command {
        Command(std::string name, bool has_argument,
                std::function<void(std::vector<Command>::iterator &it)> F = nullptr,
                int argument = 0)
            : name_ (name), has_argument_ (has_argument),
              argument_ (argument), Execute (F) {}
        std::string name_;
        bool has_argument_;
        int argument_;
        std::function<void(std::vector<Command>::iterator &it)> Execute;
    };

    //! Конструктор, принимающий число регистров
    //! @param registersCount Число регистров, по умолчанию defRegistersCount_
    ScriptingUnit(size_t registersCount = defRegistersCount_);

    //! Конструктор, принимающий вектор регистров
    //! @param registers Содержимое регистров
    ScriptingUnit(std::vector<double> registers);

    //! Конструктор, принимающий имя файла и число регистров
    //! @param filename Имя файла с кодом
    //! @param registersCount Число регистров, по умолчанию defRegistersCount_
    ScriptingUnit(std::string filename, size_t registersCount = defRegistersCount_);

    //! Конструктор, принимающий имя файла и вектор регистров
    //! @param filename Имя файла с кодом
    //! @param registers Содержимое регистров
    ScriptingUnit(std::string filename, std::vector<double> registers);

    //! Конструктор, принимающий код и число регистров
    //! @param code Вектор с кодом
    //! @param registersCount Число регистров, по умолчанию defRegistersCount_
    ScriptingUnit(std::vector<Command> code, size_t registersCount = defRegistersCount_);

    //! Конструктор, принимающий код и вектор регистров
    //! @param code Вектор с кодом
    //! @param registers Содержимое регистров
    ScriptingUnit(std::vector<Command> code, std::vector<double> registers);

    //! Деструктор (пустой)
    ~ScriptingUnit();

    //! Считывает код из файла и транслирует его
    //! @param filename Имя файла с кодом
    void Assemble(std::string filename);

    //! Считывает код из вектора без трансляции
    //! @param code Вектор с кодом
    void SetScript(std::vector<Command> code) { code_ = code; }

    //! Считывает содержимое регистров из вектора
    //! @param registers Содержимое регистров
    void SetAllRegisters(std::vector<double> registers) { registers_ = registers; }

    //! Изменяет значение конкретного регистра
    //! @param value Новое значение регистра
    //! @param pos Номер регистра
    void SetRegister(double value, size_t pos) { registers_[pos] = value; }

    //! Возвращает в виде вектора содержимое регистров
    //! @return Содержимое регистров
    std::vector<double> ReadAllRegisters() { return registers_; }

    //! Возвращает содержимое одного регистра
    //! @param pos Номер регистра
    //! @return Содержимое регистра
    double ReadRegister(size_t pos) { return registers_.at(pos); }

    //! Обращение к регистрам через []
    //! @param pos Индекс регистра
    //! @return Ссылку на значение регистра
    double& operator [](size_t pos) { return registers_.at(pos); }

    //! Возвращает количество регистров
    //! @return Количество регистров
    size_t RegistersCount() { return registers_.size(); }

    //! Исполняет транслированный код
    void Execute();

private:

    //! Сервисная функция: вытащить два элемента из стека процессора
    std::function<void(double&, double&)> CommandPopTwo =
        [this](double &x1, double &x2) {
            x1 = stack_.top();
            stack_.pop();
            x2 = stack_.top();
            stack_.pop();
        };

    //! Сервисная функция: условный переход
    std::function<void(std::vector<Command>::iterator&, bool)> CommandCondJump =
        [this](std::vector<Command>::iterator &it, bool condition) {
            if (condition) {
                LOG_DEV("ScriptingUnit: Cond jump to mark " << it->argument_);
                it = marks_[it->argument_];
            } else {
                it++;
                LOG_DEV("ScriptingUnit: Skipping jump");
            }
        };

    //! Вектор, содержащий все доступные команды
    std::vector<Command> available_commands_ = {
        Command("end", false, {
                [this] (std::vector<Command>::iterator &it) {
                    LOG_DEV("ScriptingUnit: End of script");
                    it = code_.end();
                }}),
        Command("push", true, {
                [this] (std::vector<Command>::iterator &it) {
                    stack_.push(registers_.at(it->argument_));
                    LOG_DEV("ScriptingUnit: Push x" << it->argument_ << " = " << stack_.top());
                    it++;
                }}),
        Command("pushc", true, {
                [this] (std::vector<Command>::iterator &it) {
                    stack_.push(it->argument_);
                    LOG_DEV("ScriptingUnit: Push const " << stack_.top());
                    it++;
                }}),
        Command("mult", false, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    stack_.push(x2 * x1);
                    LOG_DEV("ScriptingUnit: Mult of items = " << stack_.top());
                    it++;
                }}),
        Command("add", false, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    stack_.push(x2 + x1);
                    LOG_DEV("ScriptingUnit: Sum of items = " << stack_.top());
                    it++;
                }}),
        Command("div", false, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    stack_.push(x2 / x1);
                    LOG_DEV("ScriptingUnit: Div of items = " << stack_.top());
                    it++;
                }}),
        Command("pop", true, {
                [this] (std::vector<Command>::iterator &it) {
                    registers_.at(it->argument_) = stack_.top();
                    stack_.pop();
                    LOG_DEV("ScriptingUnit: Pop " << registers_.at(it->argument_) << " to x" << it->argument_);
                    it++;
                }}),
        Command("mark", true, {
                [this] (std::vector<Command>::iterator &it) {
                    it++;
                }}),
        Command("jmp", true, {
                [this] (std::vector<Command>::iterator &it) {
                    LOG_DEV("ScriptingUnit: Jump to mark :" << it->argument_);
                    it = marks_[it->argument_];
                }}),
        Command("je", true, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    CommandCondJump(it, x2 == x1);
                }}),
        Command("jg", true, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    CommandCondJump(it, x2 > x1);
                }}),
        Command("jge", true, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    CommandCondJump(it, x2 >= x1);
                }}),
        Command("jl", true, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    CommandCondJump(it, x2 < x1);
                }}),
        Command("jle", true, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    CommandCondJump(it, x2 <= x1);
                }}),
        Command("jne", true, {
                [this] (std::vector<Command>::iterator &it) {
                    double x1, x2;
                    CommandPopTwo(x1, x2);
                    CommandCondJump(it, x2 != x1);
                }}),
        Command("call", true, {
                [this] (std::vector<Command>::iterator &it) {
                    int mark = it->argument_;
                    LOG_DEV("ScriptingUnit: Calling mark :" << mark);
                    return_.push(++it);
                    it = marks_[mark];
                }}),
        Command("ret", false, {
                [this] (std::vector<Command>::iterator &it) {
                    it = return_.top();
                    return_.pop();
                    LOG_DEV("ScriptingUnit: Returning");
                }}),
    };

    //! Число регистров по умолчанию
    static const size_t defRegistersCount_ = 8;

    //! Стек процессора
    std::stack<double> stack_;

    //! Стек возвратов процессора
    std::stack<std::vector<Command>::iterator> return_;

    //! Исполняемый код
    std::vector<Command> code_;

    //! Регистры
    std::vector<double> registers_;

    //! Словарь меток
    std::map<int, std::vector<Command>::iterator> marks_;

    //! Служебная функция, заполняющяя словарь меток
    void collectMarks();

};

}

#endif // ScriptingUnit_H_INCLUDED
