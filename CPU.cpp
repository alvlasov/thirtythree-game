#include <iostream>
#include <fstream>
#include <string>
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
            pos = marks_[code_[pos + 1]]; \
            LOG_INFO("CPU: Jump " << #condition << " to mark " << code_[pos + 1]); \
        } \
        else \
        { \
            pos += 2; \
            LOG_INFO("CPU: Skipping jump " << #condition); \
        }

namespace thirtythree
{

    CPU::CPU()
    {
    }

    CPU::~CPU()
    {
    }

    void CPU::readCode(char *filename)
    {
        int k = 0;
        char buff[50]; // буфер промежуточного хранения считываемого из файла текста
        std::ifstream fin(filename); // открыли файл для чтения

        while (fin)
        {
            fin >> buff; // считали первое слово из файла
            if (!strcmp(buff, "push")) {
                code_.push_back(PUSH_CMD);
                fin >> buff;
                if (buff[0] == 'x')
                {
                    code_.push_back(atoi(buff + 1));
                }
                else
                {
                    code_.back() = PUSH_CONST_CMD;
                    code_.push_back(atoi(buff));
                }

            }
            else if (!strcmp(buff, "add"))
            {
                code_.push_back(ADD_CMD_;
            }
            else if (!strcmp(buff, "div"))
            {
                code_.push_back(DIV_CMD);
            }
            else if (!strcmp(buff, "pop"))
            {
                code_.push_back(POP_CMD);
                fin >> buff;
                if (buff[0] == 'x')
                {
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
            }
            else if (!strcmp(buff, "mark"))
            {
                code_.push_back(MARK_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "je"))
            {
                code_.push_back(JE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "jg"))
            {
                code_.push_back(JG_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "jge"))
            {
                code_.push_back(JGE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "jl"))
            {
                code_.push_back(JL_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "jle"))
            {
                code_.push_back(JLE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "jne"))
            {
                code_.push_back(JNE_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "call"))
            {
                code_.push_back(CALL_CMD);
                fin >> buff;
                code_.push_back(atoi(buff));
            }
            else if (!strcmp(buff, "ret"))
            {
                code_.push_back(RET_CMD);
            }

            else if (!strcmp(buff, "end"))
            {
                code_.push_back(END_CMD);
                break;
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
        size_t pos = 0;
        while (true)
        {
            switch (code_[pos])
            {
                case END_CMD:
                {
                    LOG_INFO("CPU: End of script");
                    return;
                }
                case PUSH_CMD:
                {
                    stack_.push(registers_.at(code_[pos + 1]));
                    LOG_INFO("CPU: Push x" << code_[pos + 1] << " = " << stack_.top());
                    pos += 2;
                    break;
                }
                case PUSH_CONST_CMD:
                {
                    stack_.push(code_[pos + 1]);
                    LOG_INFO("CPU: Push " << stack_.top());
                    pos += 2;
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
                    LOG_INFO("CPU: Sum of items = " << stack_.top());
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
                    LOG_INFO("CPU: Div of items = " << stack_.top());
                    break;
                }
                case POP_CMD:
                {
                    registers_.at(code_[pos + 1])=stack_.top();
                    stack_.pop();
                    LOG_INFO("CPU: Pop " << registers_.at(code_[pos + 1]) << " to " << code_[pos + 1]);
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
                    pos = marks_[code_[pos + 1]];
                    LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
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
                    return_.push(pos + 1);
                    pos = marks_[code_[pos + 1]];
                    LOG_INFO("CPU: Calling mark " << code_[pos + 1]);
                    break;
                }
                case RET_CMD:
                {
                    pos = return_.top();
                    return_.pop();
                    LOG_INFO("CPU: Returning to " << pos);
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


    void CPU::mark()
    {
        size_t pos = 0;
        while (true)
        {
            switch (code_[pos])
            {
                case END_CMD:{}

                case PUSH_CMD:
                {
                 pos += 2;
                }

                case PUSH_CONST_CMD:
                {
                    pos += 2;
                }

                case ADD_CMD:
                {
                    pos += 1;
                }

                case DIV_CMD:
                {
                    pos += 1;
                }

                case POP_CMD:
                {
                    pos += 2;
                }

                case JMP_CMD:
                {
                    pos += 2;
                }

                case MARK_CMD:
                {
                    pos +=1;
                    marks.insert(std::pair<int, int>(code_[pos], pos));
                    pos +=1;
                }

                case JE_CMD:
                {
                    pos += 2;
                }

                case JG_CMD:
                {
                    pos +=2;
                }

                case JGE_CMD:
                {
                    pos +=2;
                }

                case JL_CMD:
                {
                    pos +=2;
                }

                case JLE_CMD:
                {
                    pos +=2;
                }

                case JNE_CMD:
                {
                    pos +=2;
                }

                case CALL_CMD:
                {
                    pos += 2;
                }

                case RET_CMD:
                {
                    pos +=1
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
