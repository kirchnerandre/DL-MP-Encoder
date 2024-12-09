
#ifndef _COMMON_FRAMES_H_
#define _COMMON_FRAMES_H_

#include <stdint.h>

#include "Private/PrivateFrames.h"

namespace FRAME
{
    template<typename FRAME_T>
    class CommonFrames : public FRAME::PrivateFrames<FRAME_T>
    {
    public:
        CommonFrames(){};
       ~CommonFrames(){};

        bool initialize(uint32_t Size);

        bool get(uint8_t* Data, uint32_t FrameNumber);

        void deinitialize();
    };
}

#include "Base/CommonFrames.inl"

#endif // _COMMON_FRAMES_H_
