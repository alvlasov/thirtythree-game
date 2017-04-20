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

using std::stoi;

namespace thirtythree
{

    CPU::CPU(size_t registersCount) :
        registers_ (registersCount)
    {
        LOG_DEBUG("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEV("CPU: Registers count = " << registers_.size());
    }


    CPU::CPU(std::vector<double> registers) :
        registers_ (registers)
    {
        LOG_DEBUG("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEV("CPU: Registers count = " << registers_.size());
    }

    CPU::~CPU()
    {
        LOG_DEBUG("CPU: Destructor " << __PRETTY_FUNCTION__);
    }

    CPU::CPU(std::string filename, size_t registersCount) :
        registers_ (registersCount)
    {
        LOG_DEBUG("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEV("CPU: Registers count = " << registers_.size());
        readCode(filename);
    }

    CPU::CPU(std::string filename, std::vector<double> registers) :
        registers_ (registers)
    {
        LOG_DEBUG("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEV("CPU: Registers count = " << registers_.size());
        readCode(filename);
    }

    CPU::CPU(std::vector<int> code, size_t registersCount) :
        code_ (code),
        registers_ (registersCount)
    {
        LOG_DEBUG("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEV("CPU: Registers count = " << registers_.size());
    }

    CPU::CPU(std::vector<int> code, std::vector<double> registers) :
        code_ (code),
        registers_ (registers)
    {
        LOG_DEBUG("CPU: Constructor " << __PRETTY_FUNCTION__);
        LOG_DEV("CPU: Registers count = " << registers_.size());
    }

    void CPU::readCode(std::string filename)
    {
        std::string buff;
        std::ifstream fin(filename);
        LOG_DEBUG("CPU: Reading code from " << filename);
        while (true)
        {
            if (!(fin >> buff))
            {
                break;
            }
            if (buff == "push") {
                code_.push_back(PUSH_CMD);
                fin >> buff;
                if (buff[0] == 'x')
                {
                    LOG_DEV("CPU: Push register " << stoi(buff.substr(1)));
                    code_.push_back(stoi(buff.substr(1)));
                }
                else
                {
                    LOG_DEV("CPU: Push const " << stoi(buff));
                    code_.back() = PUSH_CONST_CMD;
                    code_.push_back(stoi(buff));
                }

            }
            else if (buff == "mult")
            {
                LOG_DEV("CPU: Mult");
                code_.push_back(MULT_CMD);
            }
            else if (buff == "add")
            {
                LOG_DEV("CPU: Add");
                code_.push_back(ADD_CMD);
            }
            else if (buff == "div")
            {
                LOG_DEV("CPU: Div");
                code_.push_back(DIV_CMD);
            }
            else if (buff == "pop")
            {
                code_.push_back(POP_CMD);
                fin >> buff;
                if (buff[0] == 'x')
                {
                    LOG_DEV("CPU: Pop register " << stoi(buff.substr(1)));
                    code_.push_back(stoi(buff.substr(1)));
                }
                else
                {
                    LOG_ERROR("CPU: Wrong syntax in file " << filename);
                    throw std::runtime_error("CPU: Wrong syntax in file");
                }
            }
            else if (buff == "jmp")
            {
                code_.push_back(JMP_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Jump to " << stoi(buff));
            }
            else if (buff == "mark")
            {
                code_.push_back(MARK_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: :" << stoi(buff));
            }
            else if (buff == "je")
            {
                code_.push_back(JE_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Jump to " << stoi(buff) << " if equal");
            }
            else if (buff == "jg")
            {
                code_.push_back(JG_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Jump to " << stoi(buff) << " if greater");
            }
            else if (buff == "jge")
            {
                code_.push_back(JGE_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Jump to " << stoi(buff) << " if greater/equal");
            }
            else if (buff == "jl")
            {
                code_.push_back(JL_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Jump to " << stoi(buff) << " if less");
            }
            else if (buff == "jle")
            {
                code_.push_back(JLE_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Jump to " << stoi(buff) << " if less/equal");
            }
            else if (buff == "jne")
            {
                code_.push_back(JNE_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Jump to " << stoi(buff) << " if not equal");
            }
            else if (buff == "call")
            {
                code_.push_back(CALL_CMD);
                fin >> buff;
                code_.push_back(stoi(buff));
                LOG_DEV("CPU: Call :" << stoi(buff));
            }
            else if (buff == "ret")
            {
                code_.push_back(RET_CMD);
                LOG_DEV("CPU: Return");
            }

            else if (buff == "end")
            {
                code_.push_back(END_CMD);
                LOG_DEV("CPU: End");
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
        collectMarks();
        double x1, x2;
        size_t pos = 0;

        auto pop_two = [this](double &x1, double &x2)
        {
                x1 = stack_.top();
                stack_.pop();
                x2 = stack_.top();
                stack_.pop();
        };
        auto jump_cond = [this, &pos](bool condition)
        {
            if (condition)
            {
                LOG_DEV("CPU: Jump to mark " << code_[pos + 1]);
                pos = marks_[code_[pos + 1]];
            }
            else
            {
                pos += 2;
                LOG_DEV("CPU: Skipping jump");
            }
        };

        LOG_DEBUG("CPU: Executing script...");
        while (true)
        {
            switch (code_[pos])
            {
                case END_CMD:
                {
                    LOG_DEV("CPU: End of script");
                    return;
                }
                case PUSH_CMD:
                {
                    stack_.push(registers_.at(code_[pos + 1]));
                    LOG_DEV("CPU: Push x" << code_[pos + 1] << " = " << stack_.top());
                    pos += 2;
                    break;
                }
                case PUSH_CONST_CMD:
                {
                    stack_.push(code_[pos + 1]);
                    LOG_DEV("CPU: Push const " << stack_.top());
                    pos += 2;
                    break;
                }
                case MULT_CMD:
                {
                    pop_two(x1, x2);
                    stack_.push(x2 * x1);
                    pos += 1;
                    LOG_DEV("CPU: Mult of items = " << stack_.top());
                    break;
                }
                case ADD_CMD:
                {
                    pop_two(x1, x2);
                    stack_.push(x2 + x1);
                    pos += 1;
                    LOG_DEV("CPU: Sum of items = " << stack_.top());
                    break;
                }
                case DIV_CMD:
                {
                    pop_two(x1, x2);
                    stack_.push(x2 / x1);
                    pos += 1;
                    LOG_DEV("CPU: Div of items = " << stack_.top());
                    break;
                }
                case POP_CMD:
                {
                    registers_.at(code_[pos + 1]) = stack_.top();
                    stack_.pop();
                    LOG_DEV("CPU: Pop " << registers_.at(code_[pos + 1]) << " to x" << code_[pos + 1]);
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
                    LOG_DEV("CPU: Jump to mark :" << code_[pos + 1]);
                    pos = marks_[code_[pos + 1]];
                    break;
                }
                case JE_CMD:
                {
                    pop_two(x1, x2);
                    jump_cond(x2 == x2);
                    break;
                }
                case JG_CMD:
                {
                    pop_two(x1, x2);
                    jump_cond(x2 > x1);
                    break;
                }
                case JGE_CMD:
                {
                    pop_two(x1, x2);
                    jump_cond(x2 >= x1);
                    break;
                }
                case JL_CMD:
                {
                    pop_two(x1, x2);
                    jump_cond(x2 < x1);
                    break;
                }
                case JLE_CMD:
                {
                    pop_two(x1, x2);
                    jump_cond(x2 <= x1);
                    break;
                }
                case JNE_CMD:
                {
                    pop_two(x1, x2);
                    jump_cond(x2 != x1);
                    break;
                }
                case CALL_CMD:
                {
                    LOG_DEV("CPU: Calling mark :" << code_[pos + 1]);
                    return_.push(pos + 2);
                    pos = marks_[code_[pos + 1]];
                    break;
                }
                case RET_CMD:
                {
                    pos = return_.top();
                    return_.pop();
                    LOG_DEV("CPU: Returning to " << pos);
                    break;
                }
            }
        }
    }

    void CPU::collectMarks()
    {
        LOG_DEBUG("CPU: Collecting marks...");
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
                    LOG_DEV("CPU: Mark :" << code_[pos] << " -> " << marks_[code_[pos]]);
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
