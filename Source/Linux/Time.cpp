
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "Base/Time.h"


namespace Time
{
    bool get_time(uint64_t& TimeMilliseconds)
    {
        struct timespec time_spec{};

        if (clock_gettime(CLOCK_REALTIME, &time_spec) < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to get time\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        TimeMilliseconds = 1000u * time_spec.tv_sec + time_spec.tv_nsec / 1000000u;

        return true;
    }
}
