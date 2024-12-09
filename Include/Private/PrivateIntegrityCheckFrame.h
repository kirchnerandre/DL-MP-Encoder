
#ifndef _PRIVATE_INTEGRITY_CHECK_FRAME_H_
#define _PRIVATE_INTEGRITY_CHECK_FRAME_H_

#include <vector>

#include "Base/CommonFrame.h"
#include "Base/Sha512.h"

namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    class PrivateIntegrityCheckFrame : public FRAME::CommonFrame<PacketSize, Width, Height>
    {
    public:
        virtual
       ~PrivateIntegrityCheckFrame(){};

    protected:
        enum class STATE
        {
            EMPTY,
            AVAILABLE,
            PROCESSED,
        };

        PrivateIntegrityCheckFrame(){};

        BUFFER::BUFFER_T<PacketSize>    _buffers            [HashColumns * HashRows]{};
        SHA512::SHA512_T<PacketSize>    _sha512_columns     [HashColumns           ]{};
        SHA512::SHA512_T<PacketSize>    _sha512_rows        [              HashRows]{};

        STATE                           _grid_buffers       [HashColumns * HashRows]{ STATE::EMPTY };

        bool                            _grid_hashes_columns[HashColumns           ]{ false };
        bool                            _grid_hashes_rows   [              HashRows]{ false };
    };
}

#endif // _PRIVATE_INTEGRITY_CHECK_FRAME_H_
