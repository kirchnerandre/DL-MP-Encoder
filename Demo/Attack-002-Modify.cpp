
#include "Base/Attack.h"
#include "Base/Packet.h"

namespace ATTACK
{
    bool Attack(PACKET::PACKET_T<packet_size>& Packet)
    {
        constexpr   uint32_t interval   = 100u;
        constexpr   uint32_t byte       = 500u;
        static      uint32_t counter    = 0u;

        if (counter++ % interval == 0u)
        {
            uint8_t value = Packet.Dummy.Garbage[byte];

            Packet.Dummy.Garbage[byte] = value ^ 0xff;
        }

        return true;
    }
}
