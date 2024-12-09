
#ifndef _PRIVATE_MP_CONTROLLER_SERVER_H_
#define _PRIVATE_MP_CONTROLLER_SERVER_H_

#include "Multipath/MpFrames.h"
#include "Multipath/MpController.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    class PrivateMpControllerServer : public MpController<PacketSize, ImageWidth, ImageHeight>
    {
    public:
        virtual
       ~PrivateMpControllerServer(){};

    protected:
        PrivateMpControllerServer(){};

        MpFrames<PacketSize, ImageWidth, ImageHeight> _frames;
    };
}

#endif // _PRIVATE_MP_CONTROLLER_SERVER_H_
