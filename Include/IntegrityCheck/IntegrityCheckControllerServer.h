
#ifndef _INTEGRITY_CHECK_CONTROLLER_SERVER_H_
#define _INTEGRITY_CHECK_CONTROLLER_SERVER_H_

#include "Base/Statistics.h"
#include "Private/PrivateIntegrityCheckControllerServer.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    class IntegrityCheckControllerServer : public PrivateIntegrityCheckControllerServer<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>
    {
    public:
        IntegrityCheckControllerServer(){};
       ~IntegrityCheckControllerServer(){};

        bool initialize_server(uint16_t Port, uint32_t Size);

        bool communicate(Statistics::STATISTICS_T& Statistics);

        IntegrityCheckFrames<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>&   get_frames();
    };
}

#include "IntegrityCheck/IntegrityCheckControllerServer.inl"

#endif // _INTEGRITY_CHECK_CONTROLLER_SERVER_H_
