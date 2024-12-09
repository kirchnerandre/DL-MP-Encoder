
#ifndef _PRIVATE_INTEGRITY_CHECK_CONTROLLER_H_
#define _PRIVATE_INTEGRITY_CHECK_CONTROLLER_H_

#include "IntegrityCheck/IntegrityCheckManager.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    class PrivateIntegrityCheckController
    {
    public:
        virtual
       ~PrivateIntegrityCheckController(){};

    protected:
        PrivateIntegrityCheckController(){};

        IntegrityCheckManager   _manager;
    };
}

#endif // _PRIVATE_INTEGRITY_CHECK_CONTROLLER_H_
