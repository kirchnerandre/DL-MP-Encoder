
#ifndef _PACKET_H_
#define _PACKET_H_

#include "Base/Buffer.h"
#include "Base/Dummy.h"
#include "Base/Sha512.h"

namespace PACKET
{
    constexpr uint32_t PACKET_TYPE_BUFFER   = 1u;
    constexpr uint32_t PACKET_TYPE_HASH     = 2u;

    template<uint32_t PacketSize>
    union PACKET_T
    {
        static constexpr uint32_t   DATA_SIZE   = 128u;

        static_assert(PacketSize % DATA_SIZE == 0u, "Packet size must be a multiple of 128 bytes\n");

        BUFFER::BUFFER_T<PacketSize>    Buffer;
        DUMMY ::DUMMY_T <PacketSize>    Dummy;
        SHA512::SHA512_T<PacketSize>    Sha512;
    };
}

#endif // _PACKET_H_
