
#ifndef _INTEGRITY_CHECK_CONTROLLER_CLIENT_H_
#define _INTEGRITY_CHECK_CONTROLLER_CLIENT_H_

#include "Base/Statistics.h"
#include "Private/PrivateIntegrityCheckControllerClient.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    class IntegrityCheckControllerClient : public PrivateIntegrityCheckControllerClient<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>
    {
    public:
        IntegrityCheckControllerClient(){};
       ~IntegrityCheckControllerClient(){};

        bool initialize_client(uint16_t Port, std::string Address);

        bool communicate(std::string& Filename, Statistics::STATISTICS_T& Statistics);
    };
}

#include "IntegrityCheck/IntegrityCheckControllerClient.inl"

#endif // _INTEGRITY_CHECK_CONTROLLER_CLIENT_H_
