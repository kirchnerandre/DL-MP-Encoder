
#ifndef _OTP_FRAME_H_
#define _OTP_FRAME_H_

#include "Private/PrivateOtpFrame.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class OtpFrame : public PrivateOtpFrame<PacketSize, Width, Height>
    {
    public:
        OtpFrame(){};
       ~OtpFrame(){};

        /**
         * Copies the buffer payload into the frame array. Complete is set to true when the frame array is complete.
         * @param Buffer Input buffer containing partial frame data, its offset in the frame array, and the frame
         * number the data belongs to.
         * @return True if valid data was received, and false otherwise.
        */
        bool set(BUFFER::BUFFER_T<PacketSize>& Buffer);

        /**
         * Copies the data of the frame specified by the frame number into the data output parameter.
         * @param Data Output parameter containing the address where the frame data is copied to.
         * @param FrameNumber Frame number used to select the desired frame.
         * @return True if valid frame number was used. False otherwise.
        */
        bool get(uint8_t* Data, uint32_t FrameNumber);
    };
}

#include "OneTimePad/OtpFrame.inl"

#endif // _OTP_FRAME_H_
