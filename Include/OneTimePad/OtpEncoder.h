
#ifndef _OTP_ENCODER_H_
#define _OTP_ENCODER_H_

#include <stdint.h>

#include "Base/Buffer.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize>
    bool encode(BUFFER::BUFFER_T<PacketSize>& Buffer, BUFFER::BUFFER_T<PacketSize>& Key);

    template<uint32_t PacketSize>
    bool encode(BUFFER::BUFFER_T<PacketSize>& Buffer, BUFFER::BUFFER_T<PacketSize>& Key, uint32_t Seed);

    template<uint32_t PacketSize>
    bool decode(BUFFER::BUFFER_T<PacketSize>& Buffer, BUFFER::BUFFER_T<PacketSize>& Key);
}

#include "OneTimePad/OtpEncoder.inl"

#endif // _OTP_ENCODER_H_
