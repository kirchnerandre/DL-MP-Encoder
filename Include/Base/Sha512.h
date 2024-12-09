
#ifndef _SHA_512_H_
#define _SHA_512_H_

#include <stdint.h>

#include "Base/Buffer.h"

namespace SHA512
{
    template<uint32_t PacketSize>
    struct SHA512_T
    {
        static constexpr uint32_t   DATA_SIZE       = 128u;

        static_assert(PacketSize % DATA_SIZE == 0u, "Packet size must be a multiple of 128 bytes\n");

        static constexpr uint32_t   LENGTH_HEADER   = 4u;
        static constexpr uint32_t   LENGTH_FRAME    = 4u;
        static constexpr uint32_t   LENGTH_OFFSET   = 4u;
        static constexpr uint32_t   LENGTH_TYPE     = 4u;
        static constexpr uint32_t   LENGTH_RESERVED = 4u;
        static constexpr uint32_t   LENGTH_DATA     = 64u;
        static constexpr uint32_t   LENGTH_GARBAGE  = PacketSize - LENGTH_HEADER - LENGTH_FRAME - LENGTH_OFFSET - LENGTH_TYPE - LENGTH_RESERVED - LENGTH_DATA;

        static constexpr uint32_t   TYPE_COLUMN     = 1u;
        static constexpr uint32_t   TYPE_ROW        = 2u;

        typedef uint8_t             HEADER_T        [LENGTH_HEADER];
        typedef uint8_t             FRAME_T         [LENGTH_FRAME];
        typedef uint8_t             OFFSET_T        [LENGTH_OFFSET];
        typedef uint8_t             TYPE_T          [LENGTH_TYPE];
        typedef uint8_t             RESERVED_T      [LENGTH_RESERVED];
        typedef uint8_t             DATA_T          [LENGTH_DATA];
        typedef uint8_t             GARBAGE_T       [LENGTH_GARBAGE];

        HEADER_T                    Header;
        FRAME_T                     Frame;
        OFFSET_T                    Offset;
        TYPE_T                      Type;
        RESERVED_T                  Reserved;
        DATA_T                      Data;
        GARBAGE_T                   Garbage;
    };

    template<uint32_t PacketSize>
    void calculate(BUFFER::BUFFER_T<PacketSize>& Buffer, SHA512_T<PacketSize>& Sha512, bool Reset);
}

#include "Base/Sha512.inl"

#endif // _SHA_512_H_
