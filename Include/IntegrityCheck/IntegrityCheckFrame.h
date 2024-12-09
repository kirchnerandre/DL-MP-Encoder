
#ifndef _INTEGRITY_CHECK_FRAME_H_
#define _INTEGRITY_CHECK_FRAME_H_

#include "Base/Statistics.h"
#include "Private/PrivateIntegrityCheckFrame.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    class IntegrityCheckFrame : public PrivateIntegrityCheckFrame<PacketSize, Width, Height, HashColumns, HashRows>
    {
    public:
        IntegrityCheckFrame(){};
       ~IntegrityCheckFrame(){};

        bool set(BUFFER::BUFFER_T<PacketSize>&  Buffer, Statistics::STATISTICS_T& Statistics);
        bool set(SHA512::SHA512_T<PacketSize>&  Sha512, Statistics::STATISTICS_T& Statistics);

        bool get(uint8_t* Data, uint32_t FrameNumber);

    protected:
        void process_column(uint32_t Position, Statistics::STATISTICS_T& Statistics);
        void process_row   (uint32_t Position, Statistics::STATISTICS_T& Statistics);
    };
}

#include "IntegrityCheck/IntegrityCheckFrame.inl"

#endif // _INTEGRITY_CHECK_FRAME_H_
