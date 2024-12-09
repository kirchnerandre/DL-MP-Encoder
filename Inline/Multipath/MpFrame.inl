
#include <stdio.h>

#include "Base/Buffer.h"
#include "Base/Endianness.h"


namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool MpFrame<PacketSize, Width, Height>::set(BUFFER::BUFFER_T<PacketSize>& Buffer, TYPE_SINGLE Type)
    {
        uint32_t frame_number = Endianness::ntoh32(Buffer.Frame);
        uint32_t frame_offset = Endianness::ntoh32(Buffer.Offset);

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

        uint32_t offset = frame_offset / Buffer.LENGTH_DATA;

        TYPE_SINGLE buffer_type = this->_BufferTypes.at(offset);

        if (buffer_type == Type)
        {
            fprintf(stderr, "%s:%d:%s: Invalid buffer_type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (buffer_type == TYPE_SINGLE::EMPTY)
        {
            memcpy(&this->_FrameData[frame_offset], Buffer.Data, Buffer.LENGTH_DATA);

            this->_BufferTypes.at(offset) = Type;
        }
        else if (buffer_type == TYPE_SINGLE::COMPLETE)
        {

        }
        else
        {
            BUFFER::BUFFER_T<PacketSize> buffer{};
            BUFFER::BUFFER_T<PacketSize> output{};

            memcpy(&buffer.Data, &this->_FrameData[frame_offset], buffer.LENGTH_DATA);

            if ((buffer_type == TYPE_SINGLE::TYPE_0) && (Type == TYPE_SINGLE::TYPE_1))
            {
                if (!decode_buffer(output, buffer, Buffer, TYPE_DOUBLE::TYPE_01))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to decode\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else if ((buffer_type == TYPE_SINGLE::TYPE_1) && (Type == TYPE_SINGLE::TYPE_0))
            {
                if (!decode_buffer(output, Buffer, buffer, TYPE_DOUBLE::TYPE_01))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to decode\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else if ((buffer_type == TYPE_SINGLE::TYPE_0) && (Type == TYPE_SINGLE::TYPE_2))
            {
                if (!decode_buffer(output, buffer, Buffer, TYPE_DOUBLE::TYPE_02))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to decode\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else if ((buffer_type == TYPE_SINGLE::TYPE_2) && (Type == TYPE_SINGLE::TYPE_0))
            {
                if (!decode_buffer(output, Buffer, buffer, TYPE_DOUBLE::TYPE_02))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to decode\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else if ((buffer_type == TYPE_SINGLE::TYPE_1) && (Type == TYPE_SINGLE::TYPE_2))
            {
                if (!decode_buffer(output, buffer, Buffer, TYPE_DOUBLE::TYPE_12))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to decode\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else if ((buffer_type == TYPE_SINGLE::TYPE_2) && (Type == TYPE_SINGLE::TYPE_1))
            {
                if (!decode_buffer(output, Buffer, buffer, TYPE_DOUBLE::TYPE_12))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to decode\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }

            memcpy(&this->_FrameData[frame_offset], &output.Data, output.LENGTH_DATA);

            this->_BufferTypes.at(offset) = TYPE_SINGLE::COMPLETE;
        }

        return true;
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool MpFrame<PacketSize, Width, Height>::get(uint8_t* Data, uint32_t Frame)
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
            for (std::vector<TYPE_SINGLE>::iterator i = this->_BufferTypes.begin(); i != this->_BufferTypes.end(); i++)
            {
                *i = TYPE_SINGLE::EMPTY;
            }

            memcpy(Data, this->_FrameData, Width * Height);

            this->_FrameFirst = true;

            return true;
        }
    }
}
