
#ifndef _PRIVATE_OTP_FRAME_H_
#define _PRIVATE_OTP_FRAME_H_

#include "Base/CommonFrame.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class PrivateOtpFrame : public FRAME::CommonFrame<PacketSize, Width, Height>
    {
    public:
        virtual
       ~PrivateOtpFrame(){};

    protected:
        PrivateOtpFrame(){};
    };
}

#endif // _PRIVATE_OTP_FRAME_H_
