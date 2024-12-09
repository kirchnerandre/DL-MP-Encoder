
#ifndef _INTEGRITY_CHECK_FRAMES_H_
#define _INTEGRITY_CHECK_FRAMES_H_

#include <stdint.h>

#include "Base/Buffer.h"
#include "Base/CommonFrames.h"
#include "Base/Statistics.h"
#include "IntegrityCheck/IntegrityCheckFrame.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    class IntegrityCheckFrames : public FRAME::CommonFrames<IntegrityCheckFrame<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>>
    {
    public:
        IntegrityCheckFrames(){};
       ~IntegrityCheckFrames(){};

        bool set(BUFFER::BUFFER_T<PacketSize>&  Buffer, Statistics::STATISTICS_T& Statistics);
        bool set(SHA512::SHA512_T<PacketSize>&  Sha512, Statistics::STATISTICS_T& Statistics);
    };
}

#include "IntegrityCheck/IntegrityCheckFrames.inl"

#endif // _INTEGRITY_CHECK_FRAMES_H_
