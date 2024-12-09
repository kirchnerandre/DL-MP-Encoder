

#ifndef _INTEGRITY_CHECK_MANAGER_H_
#define _INTEGRITY_CHECK_MANAGER_H_

#include <stdint.h>
#include <string>

#include "Base/Buffer.h"
#include "Base/Sha512.h"
#include "Private/PrivateIntegrityCheckManager.h"

namespace INTEGRITYCHECK
{
    class IntegrityCheckManager : public PrivateIntegrityCheckManager
    {
    public:
        IntegrityCheckManager(){};
       ~IntegrityCheckManager(){};

        bool initialize(uint16_t Port, std::string Address = "");

        bool konnect();

        bool deinitialize();

        template<uint32_t PacketSize>
        bool transmit(PACKET::PACKET_T<PacketSize>& Packet);

        template<uint32_t PacketSize>
        bool receive(PACKET::PACKET_T<PacketSize>& Packet);
    };
}

#include "IntegrityCheck/IntegrityCheckManager.inl"

#endif // _INTEGRITY_CHECK_MANAGER_H_
