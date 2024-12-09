
#include <stdint.h>
#include <stdio.h>


namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool OtpFrames<PacketSize, Width, Height>::set(BUFFER::BUFFER_T<PacketSize>& Buffer)
    {
        uint32_t frame_number = Endianness::ntoh32(Buffer.Frame);

        if (frame_number < this->_frame_number_minimum)
        {
            fprintf(stderr, "%s:%d:%s: Invalid sequence number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (frame_number >= this->_frame_number_minimum + this->_Frames.size())
        {
            fprintf(stderr, "%s:%d:%s: Invalid sequence number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return this->_Frames[frame_number % this->_Frames.size()].set(Buffer);
    }
}
