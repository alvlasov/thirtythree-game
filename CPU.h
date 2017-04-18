#include <vector>
#include <stack>

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

namespace thirtythree
{
    enum { END_CMD, PUSH_CMD, ADD_CMD, PUSH_CONST_CMD, DIV_CMD, POP_CMD, JMP_CMD, MARK_CMD, JE_CMD, JG_CMD, JGE_CMD, JL_CMD, JLE_CMD, JNE_CMD, CALL_CMD, RET_CMD};

    class CPU
    {
    public:

        CPU();
        ~CPU();

        void readCode(char *filename);
        void setCode(std::vector<int> code) { code_ = code; }
        void setRegisters(std::vector<double> registers) { registers_ = registers; }
        std::vector<double> readAllRegisters() { return registers_; }
        double readRegister(size_t pos) { return registers_.at(pos); }
        void execute();

    private:

        std::stack<double> stack_;
        std::stack<int> return_;
        std::vector<int> code_;
        std::vector<double> registers_;
        std::vector<int> marks_;

        void mark();

    };
}

#endif // CPU_H_INCLUDED
