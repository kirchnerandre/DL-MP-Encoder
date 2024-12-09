
#ifndef _MP_CONTROLLER_CLIENT_H_
#define _MP_CONTROLLER_CLIENT_H_

#include "Base/Aes.h"
#include "Private/PrivateMpControllerClient.h"

namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    class MpControllerClient : public PrivateMpControllerClient<PacketSize, ImageWidth, ImageHeight>
    {
    public:
        MpControllerClient(){};
       ~MpControllerClient(){};

        bool initialize_client(uint16_t     Port0,
                               uint16_t     Port1,
                               uint16_t     Port2,
                               std::string  Address0,
                               std::string  Address1,
                               std::string  Address2,
                               AES::KEY256& InitialKeyAes,
                               AES::WORDS&  InitialKeyOtp);

        bool communicate(std::string& Filename);
    };
}

#include "Multipath/MpControllerClient.inl"

#endif // _MP_CONTROLLER_CLIENT_H_
