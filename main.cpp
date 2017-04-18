#include <iostream>

#include "Smart_ptr.h"
#include "Stack.h"
#include "Vector.h"
#include "Utility.h"
#include "UnitTests.h"
#include "CPU.h"

#include "GlobalOptions.h"

using namespace thirtythree;

int main()
{
    CPU cpu;
    cpu.setCode({PUSH_CMD, 2, PUSH_CONST_CMD, 324, ADD_CMD, PUSH_CMD, 0, PUSH_CMD, 1, DIV_CMD, 3323232, END_CMD});
    cpu.setRegisters({11, 22, 33});
    cpu.execute();
    //return UnitTest::RunAllTests();
}
