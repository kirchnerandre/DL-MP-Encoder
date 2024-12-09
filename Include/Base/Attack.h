
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "Base/Packet.h"

namespace ATTACK
{
    constexpr uint32_t packet_size = 1024u;

    bool Attack(PACKET::PACKET_T<packet_size>& Packet);
}

#endif // _ATTACK_H_
