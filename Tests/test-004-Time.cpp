
#include <chrono>
#include <stdio.h>
#include <thread>

#include "Base/Time.h"


bool test_get_time(uint64_t Time)
{
    constexpr uint64_t error = 20u;

    uint64_t time_initial = 0u;
    uint64_t time_final   = 0u;

    if (!Time::get_time(time_initial))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get initial time\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(Time));

    if (!Time::get_time(time_final))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get final time\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    uint64_t interval = time_final - time_initial;

    uint64_t time_min = Time - error;
    uint64_t time_max = Time + error;

    if ((interval < time_min) || (interval > time_max))
    {
        fprintf(stderr, "%s:%d:%s: Invalid time\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


int main(int argc, char** argv)
{
    if (!test_get_time(1000u))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (!test_get_time(2000u))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (!test_get_time(5000u))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return 0;
}
