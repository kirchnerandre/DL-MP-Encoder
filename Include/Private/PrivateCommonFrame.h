
#ifndef _PRIVATE_COMMON_FRAME_H_
#define _PRIVATE_COMMON_FRAME_H_

#include <stdint.h>

#include "Base/Buffer.h"

namespace FRAME
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class PrivateCommonFrame
    {
    public:
        virtual
       ~PrivateCommonFrame(){};

    protected:
        PrivateCommonFrame(){};

        bool        _FrameFirst     = true;
        uint8_t     _FrameData       [((Width * Height + BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA - 1u) / BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA) * BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA]{};
        size_t      _FrameSize      = ((Width * Height + BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA - 1u) / BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA) * BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA;
        uint32_t    _FrameNumber    = 0u;
    };
}

#endif // _PRIVATE_COMMON_FRAME_H_
