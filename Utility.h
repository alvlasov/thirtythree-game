#ifndef UTILITYH
#define UTILITYH

#include <iostream>

namespace thirtythree
{

    void print(const char *str)
    {
        while (*str)
        {
            std::cout << *str++;
        }
    }


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

}

#endif
