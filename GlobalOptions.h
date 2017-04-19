#include <iostream>

#ifndef GLOBALOPTIONS_H_INCLUDED
#define GLOBALOPTIONS_H_INCLUDED

#define DEV_MESSAGES false
#define INFO_MESSAGES true

#if INFO_MESSAGES == true
    #define LOG_INFO(str) \
        std::cout << __DATE__ << " " << __TIME__ << " | [INFO] " << str << std::endl;
#else
    #define LOG_INFO(str)
#endif

#if DEV_MESSAGES == true
    #define LOG_DEBUG(str) \
        std::cout << __DATE__ << " " << __TIME__ << " | [DEBUG] " << str << std::endl;
#else
    #define LOG_DEBUG(str)
#endif


#define LOG_ERROR(str) \
    std::cout << __DATE__ << " " << __TIME__ << " | [ERROR] " << str << std::endl;

#endif // GLOBALOPTIONS_H_INCLUDED
