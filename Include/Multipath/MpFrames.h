
#ifndef _MP_FRAMES_H_
#define _MP_FRAMES_H_

#include <stdint.h>

#include "Base/Buffer.h"
#include "Base/CommonFrames.h"
#include "Multipath/MpFrame.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class MpFrames : public FRAME::CommonFrames<MpFrame<PacketSize, Width, Height>>
    {
    public:
        MpFrames(){};
       ~MpFrames(){};

        bool set(BUFFER::BUFFER_T<PacketSize>& Buffer, MULTIPATH::TYPE_SINGLE Type);
    };
}

#include "Multipath/MpFrames.inl"

#endif // _MP_FRAMES_H_
