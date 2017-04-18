#include <iostream>
#include <fstream>
#include <string>

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
        // enum { END_CMD, PUSH_CMD, ADD_CMD, PUSH_CONST_CMD, DIV_CMD, POP_CMD, JMP_CMD, MARK_CMD, JE_CMD, JG_CMD, JGE_CMD, JL_CMD, JLE_CMD, JNE_CMD, CALL_CMD, RET_CMD};
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
                case ADD_CMD:
                {
                    int sum;
                    sum = stack_.top();
                    stack_.pop();
                    sum += stack_.top();
                    stack_.pop();
                    stack_.push(sum);
                    pos += 1;
                    LOG_INFO("CPU: Sum items = " << stack_.top());
                    break;
                }
            }
        }
    }

    void CPU::mark()
    {
    }

}
