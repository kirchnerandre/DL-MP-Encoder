
#include <stdio.h>

#include "Base/Endianness.h"


namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool OtpFrame<PacketSize, Width, Height>::set(BUFFER::BUFFER_T<PacketSize>& Buffer)
    {
        uint32_t frame_offset = Endianness::ntoh32(Buffer.Offset);
        uint32_t frame_number = Endianness::ntoh32(Buffer.Frame);

        if (this->_FrameFirst)
        {
            this->_FrameNumber  = frame_number;
            this->_FrameFirst   = false;
        }

        if (this->_FrameNumber != frame_number)
        {
            fprintf(stderr, "%s:%d:%s: Invalid frame number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (frame_offset + Buffer.LENGTH_DATA > this->_FrameSize)
        {
            fprintf(stderr, "%s:%d:%s: Invalid offset\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        memcpy(&this->_FrameData[frame_offset], Buffer.Data, Buffer.LENGTH_DATA);

        return true;
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool OtpFrame<PacketSize, Width, Height>::get(uint8_t* Data, uint32_t Frame)
    {
        if (!this->_FrameData)
        {
            fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (Frame != this->_FrameNumber)
        {
            fprintf(stderr, "%s:%d:%s: Invalid frame number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else
        {
            memcpy(Data, this->_FrameData, Width * Height);

            this->_FrameFirst = true;

            return true;
        }
    }
}
