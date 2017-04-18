#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

namespace thirtythree
{
    class CPU
    {
    public:

        CPU();
        ~CPU();

        void setCode(char *filename);
        void setCode(Vector<int> code);
        void setRegisters(Vector<int> registers);
        int* readRegisters();
        void execute();

    private:

        Stack<int> stack_;
        Stack<int> return_;
        Vector<int> code_;
        Vector<int> registers_;
        Vector<int> marks_;

        void mark();
        void assembly(char *filename);

    };
}

#endif // CPU_H_INCLUDED
