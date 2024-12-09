
#ifndef _PRIVATE_OTP_CONTROLLER_SERVER_H_
#define _PRIVATE_OTP_CONTROLLER_SERVER_H_

#include "OneTimePad/OtpController.h"
#include "OneTimePad/OtpFrames.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class PrivateOtpControllerServer : public OtpController<PacketSize, Width, Height>
    {
    public:
        virtual
       ~PrivateOtpControllerServer(){};

    protected:
        PrivateOtpControllerServer(){};

        OtpFrames<PacketSize, Width, Height> _frames;
    };
}

#endif // _PRIVATE_OTP_CONTROLLER_SERVER_H_
