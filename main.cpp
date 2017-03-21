#include <iostream>

#include "Stack.h"
#include "Array.h"
#include "UnitTests.h"
#include "Utility.h"

int main()
{
    print("This is a % functi%n test % % %", "print()", 'O', 42, 4.2, "\n");
    return UnitTest::RunAllTests();
}
