
#ifndef _PRIVATE_OTP_MANAGER_H_
#define _PRIVATE_OTP_MANAGER_H_

#include "Base/Aes.h"
#include "Base/Network.h"

namespace ONETIMEPAD
{
    enum class TYPE
    {
        Invalid,
        Client,
        Server,
    };

    class PrivateOtpManager
    {
    public:
        virtual
       ~PrivateOtpManager(){};

    protected:
        PrivateOtpManager(){};

        Network::NetworkClient  _network_client;
        Network::NetworkServer  _network_server;

        uint32_t                _crc        = 0u;
        TYPE                    _type       = TYPE::Invalid;
        AES::KEY256             _key_aes{};
        AES::WORDS              _key_otp{};
    };
}

#endif // _PRIVATE_OTP_MANAGER_H_
