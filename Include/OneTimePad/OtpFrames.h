
#ifndef _OTP_FRAMES_H_
#define _OTP_FRAMES_H_

#include <stdint.h>

#include "Base/Buffer.h"
#include "Base/CommonFrames.h"
#include "OneTimePad/OtpFrame.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class OtpFrames : public FRAME::CommonFrames<OtpFrame<PacketSize, Width, Height>>
    {
    public:
        OtpFrames(){};
       ~OtpFrames(){};

        bool set(BUFFER::BUFFER_T<PacketSize>& Buffer);
    };
}

#include "OneTimePad/OtpFrames.inl"

#endif // _OTP_FRAMES_H_
