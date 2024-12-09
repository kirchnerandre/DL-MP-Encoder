
#ifndef _PRIVATE_OTP_CONTROLLER_H_
#define _PRIVATE_OTP_CONTROLLER_H_

#include "OneTimePad/OtpManager.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class PrivateOtpController
    {
    public:
        virtual
       ~PrivateOtpController(){};

    protected:
        PrivateOtpController(){};

        OtpManager  _manager;
    };
}

#endif // _PRIVATE_OTP_CONTROLLER_H_
