
#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include <stdint.h>

namespace Statistics
{
    struct STATISTICS_T
    {
        uint32_t    PacketDataTotal;
        uint32_t    PacketDataGood;
        uint32_t    PacketHashTypeColumnTotal;
        uint32_t    PacketHashTypeColumnGood;
        uint32_t    PacketHashTypeColumnBad;
        uint32_t    PacketHashTypeRowTotal;
        uint32_t    PacketHashTypeRowGood;
        uint32_t    PacketHashTypeRowBad;
    };

    void summarize(STATISTICS_T& Statistics);
}

#endif // _STATISTICS_H_
