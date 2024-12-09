
#ifndef _MP_CONTROLLER_SERVER_H_
#define _MP_CONTROLLER_SERVER_H_

#include "Private/PrivateMpControllerServer.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    class MpControllerServer : public PrivateMpControllerServer<PacketSize, ImageWidth, ImageHeight>
    {
    public:
        MpControllerServer(){};
       ~MpControllerServer(){};

        bool initialize_server(uint16_t Port0, uint16_t Port1, uint16_t Port2, uint32_t Size);

        bool communicate();

        MpFrames<PacketSize, ImageWidth, ImageHeight>& get_frames();
    };
}

#include "Multipath/MpControllerServer.inl"

#endif // _MP_CONTROLLER_SERVER_H_
