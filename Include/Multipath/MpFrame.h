
#ifndef _MP_FRAME_H_
#define _MP_FRAME_H_

#include "Private/PrivateMpFrame.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class MpFrame : public PrivateMpFrame<PacketSize, Width, Height>
    {
    public:
        MpFrame(){};
       ~MpFrame(){};

        /**
         * Copies the buffer payload into the frame array. Complete is set to true when the frame array is complete.
         * @param Buffer Input buffer containing partial frame data, its offset in the frame array, and the frame
         * number the data belongs to.
         * @param Type Specify the type of data in the buffer.
         * @return True if valid data was received, and false otherwise.
        */
        bool set(BUFFER::BUFFER_T<PacketSize>& Buffer, TYPE_SINGLE Type);

        /**
         * Copies the data of the frame specified by the frame number into the data output parameter.
         * @param Data Output parameter containing the address where the frame data is copied to.
         * @param FrameNumber Frame number used to select the desired frame.
         * @return True if valid frame number was used. False otherwise.
        */
        bool get(uint8_t* Data, uint32_t FrameNumber);
    };
}

#include "Multipath/MpFrame.inl"

#endif // _MP_FRAME_H_
