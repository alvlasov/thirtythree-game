#include <iostream>

#ifndef UTILITYH
#define UTILITYH

void print(const char *str);

template <typename T, typename... Args>
void print(const char *str, T val, Args... args)
{
    while (*str)
    {
        if (*str != '%')
        {
            std::cout << *str++;
        }
        else
        {
            std::cout << val;
            print(str + 1, args...);
            break;
        }
    }
}

#endif
