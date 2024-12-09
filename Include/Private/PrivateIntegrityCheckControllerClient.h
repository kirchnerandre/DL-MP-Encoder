
#ifndef _PRIVATE_INTEGRITY_CHECK_CONTROLLER_CLIENT_H_
#define _PRIVATE_INTEGRITY_CHECK_CONTROLLER_CLIENT_H_

#include "IntegrityCheck/IntegrityCheckController.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    class PrivateIntegrityCheckControllerClient : public IntegrityCheckController<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>
    {
    public:
        virtual
       ~PrivateIntegrityCheckControllerClient(){};

    protected:
        PrivateIntegrityCheckControllerClient(){};

        uint32_t _frame_number = 0u;
    };
}

#endif // _PRIVATE_INTEGRITY_CHECK_CONTROLLER_CLIENT_H_
