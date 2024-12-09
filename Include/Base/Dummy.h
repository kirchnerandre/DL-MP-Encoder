
#ifndef _DUMMY_H_
#define _DUMMY_H_

#include <stdint.h>

namespace DUMMY
{
    template<uint32_t PacketSize>
    struct DUMMY_T
    {
        static constexpr uint32_t   DATA_SIZE   = 128u;

        static_assert(PacketSize % DATA_SIZE == 0u, "Packet size must be a multiple of 128 bytes\n");

        static constexpr uint32_t   LENGTH_HEADER   = 4u;
        static constexpr uint32_t   LENGTH_GARBAGE  = PacketSize - LENGTH_HEADER;

        typedef uint8_t             HEADER_T        [LENGTH_HEADER];
        typedef uint8_t             GARBAGE_T       [LENGTH_GARBAGE];

        HEADER_T                    Header;
        GARBAGE_T                   Garbage;
    };
}

#endif // _DUMMY_H_
