
#include <cstdlib>
#include <ctime>

#include "Base/Attack.h"
#include "Base/Packet.h"


namespace ATTACK
{
    bool Attack(PACKET::PACKET_T<packet_size>& Packet)
    {
        constexpr   uint32_t    byte        = 500u;
        static      bool        initialized = false;

        if (!initialized)
        {
            initialized = true;
            srand(time(0));
        }

        if (static_cast<float>(rand()) / RAND_MAX <= 0.005f)
        {
            Packet.Dummy.Garbage[byte] ^= 0xff;

            return true;
        }
        else if (static_cast<float>(rand()) / RAND_MAX <= 0.010f)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
