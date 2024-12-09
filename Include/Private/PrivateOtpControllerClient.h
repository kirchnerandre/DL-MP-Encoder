
#ifndef _PRIVATE_OTP_CONTROLLER_CLIENT_H_
#define _PRIVATE_OTP_CONTROLLER_CLIENT_H_

#include "OneTimePad/OtpController.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class PrivateOtpControllerClient : public OtpController<PacketSize, Width, Height>
    {
    public:
        virtual
       ~PrivateOtpControllerClient(){};

    protected:
        PrivateOtpControllerClient(){};

        uint32_t _frame_number = 0u;
    };
}

#endif // _PRIVATE_OTP_CONTROLLER_CLIENT_H_
