#include "Utility.h"

void print(const char *str)
{
    while (*str)
    {
        std::cout << *str++;
    }
}
