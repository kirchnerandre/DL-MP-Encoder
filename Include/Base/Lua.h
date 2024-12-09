
#ifndef _LUA_H_
#define _LUA_H_

#include "Packet.h"

namespace LUA
{



    template<uint32_t PacketSize>
    bool execute_attack(PACKET::PACKET_T<PacketSize>* Packet);
}

#endif

#include "Base/Lua.inl"
