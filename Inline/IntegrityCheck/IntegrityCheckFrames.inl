
#include <stdint.h>
#include <stdio.h>


namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckFrames<PacketSize, Width, Height, HashColumns, HashRows>::set(BUFFER::BUFFER_T<PacketSize>& Buffer, Statistics::STATISTICS_T& Statistics)
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

        return this->_Frames[frame_number % this->_Frames.size()].set(Buffer, Statistics);
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckFrames<PacketSize, Width, Height, HashColumns, HashRows>::set(SHA512::SHA512_T<PacketSize>& Sha512, Statistics::STATISTICS_T& Statistics)
    {
        uint32_t frame_number = Endianness::ntoh32(Sha512.Frame);

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

        return this->_Frames[frame_number % this->_Frames.size()].set(Sha512, Statistics);
    }
}
