#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>

#if INFO_MESSAGES == true
    #define LOG_INFO(str) \
        std::cout << __DATE__ << " " << __TIME__ << " | [INFO] " << str << std::endl;
#else
    #define LOG_INFO(str)
#endif

#if DEBUG_MESSAGES == true
    #define LOG_DEBUG(str) \
        std::cout << __DATE__ << " " << __TIME__ << " | [DEBUG] " << str << std::endl;
#else
    #define LOG_DEBUG(str)
#endif

#if DEV_MESSAGES == true
    #define LOG_DEV(str) \
        std::cout << __DATE__ << " " << __TIME__ << " | [DEV] " << str << std::endl;
#else
    #define LOG_DEV(str)
#endif

#define LOG_ERROR(str) \
    std::cout << __DATE__ << " " << __TIME__ << " | [ERROR] " << str << std::endl;

#endif // LOGGER_H_INCLUDED

