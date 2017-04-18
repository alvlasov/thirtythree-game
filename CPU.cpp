#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "GlobalOptions.h"
#include "CPU.h"

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
                    LOG_INFO("CPU: Pop " << registers_.at(code_[pos + 1]));
                    pos += 2;
                    break;
                }
                case JMP_CMD:
                {
                    pos = marks_[code_[pos + 1]];
                    LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
                    break;
                }
                case MARK_CMD:
                {
                    pos +=1;
                    break;
                }
                case JE_CMD:
                {

                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    if (x1==x2)
                    {
                        pos = marks_[code_[pos + 1]];
                        LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
                    }
                    else
                    {
                        pos +=2;
                        LOG_INFO("CPU:  no Jump ");
                    }
                    break;
                }
                case JG_CMD:
                {

                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    if (x2>x1)
                    {
                        pos = marks_[code_[pos + 1]];
                        LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
                    }
                    else
                    {
                        pos +=2;
                        LOG_INFO("CPU:  no Jump ");
                    }
                    break;
                }
                case JGE_CMD:
                {

                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    if (x2>=x1)
                    {
                        pos = marks_[code_[pos + 1]];
                        LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
                    }
                    else
                    {
                        pos +=2;
                        LOG_INFO("CPU:  no Jump ");
                    }
                    break;
                }
                case JL_CMD:
                {

                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    if (x2<x1)
                    {
                        pos = marks_[code_[pos + 1]];
                        LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
                    }
                    else
                    {
                        pos +=2;
                        LOG_INFO("CPU:  no Jump ");
                    }
                    break;
                }
                case JLE_CMD:
                {

                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    if (x2<=x1)
                    {
                        pos = marks_[code_[pos + 1]];
                        LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
                    }
                    else
                    {
                        pos +=2;
                        LOG_INFO("CPU:  no Jump ");
                    }
                    break;
                }
                case JNE_CMD:
                {

                    double x1, x2;
                    x1 = stack_.top();
                    stack_.pop();
                    x2 = stack_.top();
                    stack_.pop();
                    if (x2!=x1)
                    {
                        pos = marks_[code_[pos + 1]];
                        LOG_INFO("CPU: Jump to mark " << code_[pos + 1]);
                    }
                    else
                    {
                        pos +=2;
                        LOG_INFO("CPU:  no Jump ");
                    }
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
