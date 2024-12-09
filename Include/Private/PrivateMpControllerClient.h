
#ifndef _PRIVATE_MP_CONTROLLER_CLIENT_H_
#define _PRIVATE_MP_CONTROLLER_CLIENT_H_

#include "Multipath/MpController.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    class PrivateMpControllerClient : public MpController<PacketSize, ImageWidth, ImageHeight>
    {
    public:
        virtual
       ~PrivateMpControllerClient(){};

    protected:
        PrivateMpControllerClient(){};

        uint32_t _frame_number = 0u;
    };
}

#endif // _PRIVATE_MP_CONTROLLER_CLIENT_H_
