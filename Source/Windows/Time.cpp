
#include <windows.h>

#include "Base/Time.h"


namespace Time
{
    bool get_time(uint64_t& TimeMilliseconds)
    {
        SYSTEMTIME system_time{};

        GetSystemTime(&system_time);

        TimeMilliseconds = static_cast<uint64_t>(system_time.wMilliseconds)
                         + static_cast<uint64_t>(system_time.wSecond        * 1000u)
                         + static_cast<uint64_t>(system_time.wMinute        * 1000u * 60u)
                         + static_cast<uint64_t>(system_time.wHour          * 1000u * 60u * 60u);

        return true;
    }
}
