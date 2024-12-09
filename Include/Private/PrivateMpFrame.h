
#ifndef _PRIVATE_MP_FRAME_H_
#define _PRIVATE_MP_FRAME_H_

#include <vector>

#include "Base/CommonFrame.h"
#include "Multipath/MpEncoder.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class PrivateMpFrame : public FRAME::CommonFrame<PacketSize, Width, Height>
    {
    public:
        virtual
       ~PrivateMpFrame(){};

    protected:
        typedef std::vector<TYPE_SINGLE>    TYPES_SINGLE;
        typedef TYPES_SINGLE::iterator      ITYPE_SINGLE;

        PrivateMpFrame(){};

        TYPES_SINGLE _BufferTypes = TYPES_SINGLE((Width * Height + BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA - 1u) / BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA, TYPE_SINGLE::EMPTY);
    };
}

#endif // _PRIVATE_MP_FRAME_H_
