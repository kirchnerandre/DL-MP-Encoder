
#ifndef _PRIVATE_MP_CONTROLLER_H_
#define _PRIVATE_MP_CONTROLLER_H_

#include "Multipath/MpManager.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    class PrivateMpController
    {
    public:
        virtual
       ~PrivateMpController(){};

    protected:
        PrivateMpController(){};

        bool        _enabled_0  = false;
        bool        _enabled_1  = false;
        bool        _enabled_2  = false;
        MpManager   _manager;
    };
}

#endif // _PRIVATE_MP_CONTROLLER_H_
