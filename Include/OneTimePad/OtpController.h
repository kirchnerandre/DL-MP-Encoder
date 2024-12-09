
#ifndef _OTP_CONTROLLER_H_
#define _OTP_CONTROLLER_H_

#include "Private/PrivateOtpController.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class OtpController : public PrivateOtpController<PacketSize, Width, Height>
    {
    public:
        virtual
       ~OtpController(){};

        bool konnect(uint32_t Timeout);
        bool deinitialize();

    protected:
        OtpController(){};
    };
}

#include "OneTimePad/OtpController.inl"

#endif // _OTP_CONTROLLER_H_
