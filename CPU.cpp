/*!
    @file CPU.cpp
    @brief Реализация простого ассемблера
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Апрель 2017
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

#include "GlobalOptions.h"
#include "CPU.h"

#define JMP_COND(condition) \
        double x1, x2; \
        x1 = stack_.top(); \
        stack_.pop(); \
        x2 = stack_.top(); \
        stack_.pop(); \
        if (x2 condition x1) \
        { \
            LOG_DEBUG("CPU: Jump " << #condition << " to mark " << code_[pos + 1]); \
            pos = marks_[code_[pos + 1]]; \
        } \
        else \
        { \
            pos += 2; \
            LOG_DEBUG("CPU: Skipping jump " << #condition); \
        }

namespace thirtythree
{


    CPU::CPU(size_t registersCount) :
        registers_ (registersCount)
    {
        LOG_INFO("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEBUG("CPU: Registers count = " << registers_.size());
    }


    CPU::CPU(std::vector<double> registers) :
        registers_ (registers)
    {
        LOG_INFO("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEBUG("CPU: Registers count = " << registers_.size());
    }

    CPU::~CPU()
    {
        LOG_INFO("CPU: Destructor " << __PRETTY_FUNCTION__);
    }

    CPU::CPU(char *filename, size_t registersCount) :
        registers_ (registersCount)
    {
        LOG_INFO("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEBUG("CPU: Registers count = " << registers_.size());
        readCode(filename);
    }

    CPU::CPU(char *filename, std::vector<double> registers) :
        registers_ (registers)
    {
        LOG_INFO("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEBUG("CPU: Registers count = " << registers_.size());
        readCode(filename);
    }

    CPU::CPU(std::vector<int> code, size_t registersCount) :
        code_ (code),
        registers_ (registersCount)
    {
        LOG_INFO("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEBUG("CPU: Registers count = " << registers_.size());
    }

    CPU::CPU(std::vector<int> code, std::vector<double> registers) :
        code_ (code),
        registers_ (registers)
    {
        LOG_INFO("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEBUG("CPU: Registers count = " << registers_.size());
    }

    void CPU::readCode(char *filename)
    {
        char buff[50]; // буфер промежуточного хранения считываемого из файла текста
        std::ifstream fin(filename); // открыли файл для чтения
        LOG_INFO("CPU: Reading code from " << filename);
        while (true)
        {
            if (!(fin >> buff))
            {
                break;
            }
            if (!strcmp(buff, "push")) {
                code_.push_back(PUSH_CMD);
                fin >> buff;
                if (buff[0] == 'x')
                {
                    LOG_DEBUG("CPU: Push register " << atoi(buff + 1));
                    code_.push_back(atoi(buff + 1));
                }
                else
                {
                    LOG_DEBUG("CPU: Push const " << atoi(buff));
                    code_.back() = PUSH_CONST_CMD;
                    code_.push_back(atoi(buff));
                }

            }
            else if (!strcmp(buff, "mult"))
            {
                LOG_DEBUG("CPU: Mult");
                code_.push_back(MULT_CMD);
            }
            else if (!strcmp(buff, "add"))
            {
                LOG_DEBUG("CPU: Add");
                code_.push_back(ADD_CMD);
            }
            else if (!strcmp(buff, "div"))
            {
                LOG_DEBUG("CPU: Div");
                code_.push_back(DIV_CMD);
            }
            else if (!strcmp(buff, "pop"))
            {
                code_.push_back(POP_CMD);
                fin >> buff;
                if (buff[0] == 'x')
                {
                    LOG_DEBUG("CPU: Pop register " << atoi(buff + 1));
                    code_.push_back(atoi(buff + 1));
                }
                else
                {
                    LOG_ERROR("CPU: Wrong syntax in file " << filename);
                    throw std::runtime_error("CPU: Wrong syntax in file");
                }
            }
            else if (!strcmp(buff, "jmp"))
            {
                code_.push_back(JMP_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Jump to " << atoi(buff));
            }
            else if (!strcmp(buff, "mark"))
            {
                code_.push_back(MARK_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: :" << atoi(buff));
            }
            else if (!strcmp(buff, "je"))
            {
                code_.push_back(JE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Jump to " << atoi(buff) << " if equal");
            }
            else if (!strcmp(buff, "jg"))
            {
                code_.push_back(JG_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Jump to " << atoi(buff) << " if greater");
            }
            else if (!strcmp(buff, "jge"))
            {
                code_.push_back(JGE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Jump to " << atoi(buff) << " if greater/equal");
            }
            else if (!strcmp(buff, "jl"))
            {
                code_.push_back(JL_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Jump to " << atoi(buff) << " if less");
            }
            else if (!strcmp(buff, "jle"))
            {
                code_.push_back(JLE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Jump to " << atoi(buff) << " if less/equal");
            }
            else if (!strcmp(buff, "jne"))
            {
                code_.push_back(JNE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Jump to " << atoi(buff) << " if not equal");
            }
            else if (!strcmp(buff, "call"))
            {
                code_.push_back(CALL_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
                LOG_DEBUG("CPU: Call :" << atoi(buff));
            }
            else if (!strcmp(buff, "ret"))
            {
                code_.push_back(RET_CMD);
                LOG_DEBUG("CPU: Return");
            }

            else if (!strcmp(buff, "end"))
            {
                code_.push_back(END_CMD);
                LOG_DEBUG("CPU: End");
            }
            else
            {
                LOG_ERROR("CPU: Unknown command in file " << filename);
                throw std::runtime_error("CPU: Unknown command in file");
            }
        }
        fin.close();
    }

    void CPU::execute()
    {
        mark();
        size_t pos = 0;
        LOG_INFO("CPU: Executing script...");
        while (true)
        {
            switch (code_[pos])
            {
                case END_CMD:
                {
                    LOG_DEBUG("CPU: End of script");
                    return;
                }
                case PUSH_CMD:
                {
                    stack_.push(registers_.at(code_[pos + 1]));
                    LOG_DEBUG("CPU: Push x" << code_[pos + 1] << " = " << stack_.top());
                    pos += 2;
                    break;
                }
                case PUSH_CONST_CMD:
                {
                    stack_.push(code_[pos + 1]);
                    LOG_DEBUG("CPU: Push const " << stack_.top());
                    pos += 2;
                    break;
                }
                case MULT_CMD:
                {
                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    stack_.push(x2 * x1);
                    pos += 1;
                    LOG_DEBUG("CPU: Mult of items = " << stack_.top());
                    break;
                }
                case ADD_CMD:
                {
                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    stack_.push(x2 + x1);
                    pos += 1;
                    LOG_DEBUG("CPU: Sum of items = " << stack_.top());
                    break;
                }
                case DIV_CMD:
                {
                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    stack_.push(x2 / x1);
                    pos += 1;
                    LOG_DEBUG("CPU: Div of items = " << stack_.top());
                    break;
                }
                case POP_CMD:
                {
                    registers_.at(code_[pos + 1]) = stack_.top();
                    stack_.pop();
                    LOG_DEBUG("CPU: Pop " << registers_.at(code_[pos + 1]) << " to x" << code_[pos + 1]);
                    pos += 2;
                    break;
                }
                case MARK_CMD:
                {
                    pos += 2;
                    break;
                }
                case JMP_CMD:
                {
                    LOG_DEBUG("CPU: Jump to mark :" << code_[pos + 1]);
                    pos = marks_[code_[pos + 1]];
                    break;
                }
                case JE_CMD:
                {
                    JMP_COND(==);
                    break;
                }
                case JG_CMD:
                {
                    JMP_COND(>);
                    break;
                }
                case JGE_CMD:
                {
                    JMP_COND(>=);
                    break;
                }
                case JL_CMD:
                {
                    JMP_COND(<);
                    break;
                }
                case JLE_CMD:
                {
                    JMP_COND(<=);
                    break;
                }
                case JNE_CMD:
                {
                    JMP_COND(!=);
                    break;
                }
                case CALL_CMD:
                {
                    LOG_DEBUG("CPU: Calling mark :" << code_[pos + 1]);
                    return_.push(pos + 2);
                    pos = marks_[code_[pos + 1]];
                    break;
                }
                case RET_CMD:
                {
                    pos = return_.top();
                    return_.pop();
                    LOG_DEBUG("CPU: Returning to " << pos);
                    break;
                }
            }
        }
    }

    void CPU::mark()
    {
        LOG_INFO("CPU: Collecting marks...");
        size_t pos = 0;
        while (pos < code_.size())
        {
            switch (code_[pos])
            {
                case END_CMD:
                {
                    pos += 1;
                    break;
                }
                case PUSH_CMD:
                {
                    pos += 2;
                    break;
                }
                case PUSH_CONST_CMD:
                {
                    pos += 2;
                    break;
                }
                case MULT_CMD:
                {
                    pos += 1;
                    break;
                }
                case ADD_CMD:
                {
                    pos += 1;
                    break;
                }
                case DIV_CMD:
                {
                    pos += 1;
                    break;
                }
                case POP_CMD:
                {
                    pos += 2;
                    break;
                }
                case JMP_CMD:
                {
                    pos += 2;
                    break;
                }
                case MARK_CMD:
                {
                    pos += 1;
                    marks_.insert(std::pair<int, int>(code_[pos], pos + 1));
                    LOG_DEBUG("CPU: Mark :" << code_[pos] << " -> " << marks_[code_[pos]]);
                    pos += 1;
                    break;
                }
                case JE_CMD:
                {
                    pos += 2;
                    break;
                }
                case JG_CMD:
                {
                    pos += 2;
                    break;
                }
                case JGE_CMD:
                {
                    pos += 2;
                    break;
                }
                case JL_CMD:
                {
                    pos += 2;
                    break;
                }
                case JLE_CMD:
                {
                    pos +=2;
                    break;
                }
                case JNE_CMD:
                {
                    pos +=2;
                    break;
                }
                case CALL_CMD:
                {
                    pos += 2;
                    break;
                }
                case RET_CMD:
                {
                    pos += 1;
                    break;
                }
                default:
                {
                    LOG_ERROR("CPU: Code error on " << pos);
                    throw std::runtime_error("CPU: Code error");
                }
          }
        }
    }

}
