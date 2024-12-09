
#ifndef _MP_ENCODER_H_
#define _MP_ENCODER_H_

#include "Base/Buffer.h"

namespace MULTIPATH
{
    enum class TYPE_SINGLE
    {
        EMPTY,
        TYPE_0,
        TYPE_1,
        TYPE_2,
        COMPLETE,
    };

    enum class TYPE_DOUBLE
    {
        EMPTY,
        TYPE_01,
        TYPE_02,
        TYPE_12,
        COMPLETE,
    };

    template<uint32_t PacketSize>
    bool encode_buffer(BUFFER::BUFFER_T<PacketSize>& BufferOutput0,
                       BUFFER::BUFFER_T<PacketSize>& BufferOutput1,
                       BUFFER::BUFFER_T<PacketSize>& BufferOutput2,
                       BUFFER::BUFFER_T<PacketSize>& BufferInput,
                       BUFFER::BUFFER_T<PacketSize>& Key);

    template<uint32_t PacketSize>
    bool decode_buffer(BUFFER::BUFFER_T<PacketSize>& BufferOutput,
                       BUFFER::BUFFER_T<PacketSize>& BufferInputA,
                       BUFFER::BUFFER_T<PacketSize>& BufferInputB,
                       TYPE_DOUBLE                   Type);
}

#include "Multipath/MpEncoder.inl"

#endif // _MP_ENCODER_H_
