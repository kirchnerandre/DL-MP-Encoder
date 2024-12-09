
#ifndef _PRIVATE_FRAMES_H_
#define _PRIVATE_FRAMES_H_

#include <stdint.h>
#include <vector>

#include "Base/Buffer.h"

namespace FRAME
{
    template<typename FRAME_T>
    class PrivateFrames
    {
    public:
        virtual
       ~PrivateFrames(){};

    protected:
        PrivateFrames(){};

        std::vector<FRAME_T> _Frames;
        uint32_t             _frame_number_minimum = 0u;
    };
}

#endif // _PRIVATE_FRAMES_H_
