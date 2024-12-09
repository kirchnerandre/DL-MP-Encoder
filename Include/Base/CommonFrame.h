
#ifndef _COMMON_FRAME_H_
#define _COMMON_FRAME_H_

#include "Private/PrivateCommonFrame.h"

namespace FRAME
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class CommonFrame : public PrivateCommonFrame<PacketSize, Width, Height>
    {
    public:
        virtual
       ~CommonFrame(){};

        /**
         * Copies the data of the frame specified by the frame number into the data output parameter.
         * @param Data Output parameter containing the address where the frame data is copied to.
         * @param FrameNumber Frame number used to select the desired frame.
         * @return True if valid frame number was used. False otherwise.
        */
        virtual bool get(uint8_t* Data, uint32_t FrameNumber) = 0;

        /**
         * Testing function used to compare frames to verify they are exactly the same.
         * @param Frame Frame to be compared to.
         * @return True if frames are exactly the same, and false otherwise.
        */
        bool test(CommonFrame& Frame);

        /**
         * Print frame to screen.
        */
        void print();

    protected:
        CommonFrame(){};
    };
}

#include "Base/CommonFrame.inl"

#endif // _COMMON_FRAME_H_
