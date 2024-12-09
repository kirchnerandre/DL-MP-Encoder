
#ifndef _UTILS_CONFIG_H_
#define _UTILS_CONFIG_H_

#include <string>

#include "Base/Aes.h"

namespace UtilsConfig
{
    template<typename T>
    static bool read(T& Key, std::string& Filename);
};

#include "Base/UtilsConfig.inl"

#endif // _UTILS_CONFIG_H_
