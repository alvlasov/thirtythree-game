#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <ctime>
#include <string>

#define LOG_MESSAGE(reason, str) {\
    time_t rawtime; \
    time(&rawtime); \
    std::string timestr = ctime(&rawtime); \
    timestr.pop_back(); \
    std::cout << timestr << " | [" << #reason << "] " << str << std::endl; }

#if INFO_MESSAGES == true
    #define LOG_INFO(str) LOG_MESSAGE(INFO, str)
#else
    #define LOG_INFO(str)
#endif

#if DEBUG_MESSAGES == true
    #define LOG_DEBUG(str) LOG_MESSAGE(DEBUG, str)
#else
    #define LOG_DEBUG(str)
#endif

#if DEV_MESSAGES == true
    #define LOG_DEV(str) LOG_MESSAGE(DEV, str)
#else
    #define LOG_DEV(str)
#endif

#define LOG_ERROR(str) LOG_MESSAGE(ERROR, str)

#endif // LOGGER_H_INCLUDED

