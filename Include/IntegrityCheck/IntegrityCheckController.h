
#ifndef _INTEGRITY_CHECK_CONTROLLER_H_
#define _INTEGRITY_CHECK_CONTROLLER_H_

#include "Private/PrivateIntegrityCheckController.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    class IntegrityCheckController : public PrivateIntegrityCheckController<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>
    {
    public:
        virtual
       ~IntegrityCheckController(){};

        bool konnect(uint32_t Timeout);
        bool deinitialize();

    protected:
        IntegrityCheckController(){};
    };
}

#include "IntegrityCheck/IntegrityCheckController.inl"

#endif // _INTEGRITY_CHECK_CONTROLLER_H_
