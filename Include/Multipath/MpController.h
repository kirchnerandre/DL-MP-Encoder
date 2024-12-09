
#ifndef _MP_CONTROLLER_H_
#define _MP_CONTROLLER_H_

#include "Private/PrivateMpController.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    class MpController : public PrivateMpController<PacketSize, ImageWidth, ImageHeight>
    {
    public:
        virtual
       ~MpController(){};

        bool konnect(uint32_t Timeout);
        bool deinitialize();

    protected:
        MpController(){};
    };
}

#include "Multipath/MpController.inl"

#endif // _MP_CONTROLLER_H_
