
#include <stdio.h>


namespace FRAME
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool CommonFrame<PacketSize, Width, Height>::test(CommonFrame& Frame)
    {
        if (Frame._FrameNumber != this->_FrameNumber)
        {
            fprintf(stderr, "%s:%d:%s: Invalid frame number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (Frame._Width != this->_Width)
        {
            fprintf(stderr, "%s:%d:%s: Invalid width\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (Frame._Height != this->_Height)
        {
            fprintf(stderr, "%s:%d:%s: Invalid height\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (memcmp(Frame._FrameData, this->_FrameData, sizeof(this->_FrameData)))
        {
            fprintf(stderr, "%s:%d:%s: Invalid data\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    void CommonFrame<PacketSize, Width, Height>::print()
    {
        uint32_t height = Height;
        uint32_t width  = Width;

        for (uint32_t j = 0u; j < height; j++)
        {
            for (uint32_t i = 0u; i < width; i++)
            {
                printf("0x%02x ", this->_FrameData[j * width + i]);
            }

            printf("\n");
        }
    }
}
