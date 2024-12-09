
#include "Base/Attack.h"
#include "Base/Packet.h"

namespace ATTACK
{
    bool Attack(PACKET::PACKET_T<packet_size>& Packet)
    {
        constexpr   uint32_t interval   = 100u;
        static      uint32_t counter    = 0u;

        if (counter++ % interval == 0u)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
