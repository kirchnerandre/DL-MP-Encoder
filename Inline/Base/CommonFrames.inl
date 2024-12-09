
#include <stdint.h>
#include <stdio.h>


namespace FRAME
{
    template<typename FRAME_T>
    bool CommonFrames<FRAME_T>::initialize(uint32_t Size)
    {
        try
        {
            this->_Frames = std::vector<FRAME_T>(Size);
        }
        catch(const std::exception& e)
        {
            fprintf(stderr, "%s:%d:%s: Invalid to initialize frames\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    template<typename FRAME_T>
    bool CommonFrames<FRAME_T>::get(uint8_t* Data, uint32_t FrameNumber)
    {
        if (FrameNumber < this->_frame_number_minimum)
        {
            fprintf(stderr, "%s:%d:%s: Invalid sequence number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (FrameNumber >= this->_frame_number_minimum + this->_Frames.size())
        {
            fprintf(stderr, "%s:%d:%s: Invalid sequence number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!this->_Frames[FrameNumber % this->_Frames.size()].get(Data, FrameNumber))
        {
            fprintf(stderr, "%s:%d:%s: Failed to get frame data\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        this->_frame_number_minimum = FrameNumber + 1u;

        return true;
    }


    template<typename FRAME_T>
    void CommonFrames<FRAME_T>::deinitialize()
    {
        this->_Frames.clear();
    }
}
