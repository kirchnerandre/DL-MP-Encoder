
#ifndef _PRIVATE_INTEGRITY_CHECK_CONTROLLER_SERVER_H_
#define _PRIVATE_INTEGRITY_CHECK_CONTROLLER_SERVER_H_

#include "IntegrityCheck/IntegrityCheckController.h"
#include "IntegrityCheck/IntegrityCheckFrames.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    class PrivateIntegrityCheckControllerServer : public IntegrityCheckController<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>
    {
    public:
        virtual
       ~PrivateIntegrityCheckControllerServer(){};

    protected:
        PrivateIntegrityCheckControllerServer(){};

        IntegrityCheckFrames<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>    _frames;
    };
}

#endif // _PRIVATE_INTEGRITY_CHECK_CONTROLLER_SERVER_H_
