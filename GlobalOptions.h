#include <iostream>
#include <ctime>

#ifndef GLOBALOPTIONS_H_INCLUDED
#define GLOBALOPTIONS_H_INCLUDED

#define DEV_MESSAGES true
#define INFO_MESSAGES true

#define LOG_INFO(str) \
    if (INFO_MESSAGES) \
    std::cout << __DATE__ << " " << __TIME__ << " | [INFO] " << str << std::endl; \


#endif // GLOBALOPTIONS_H_INCLUDED
