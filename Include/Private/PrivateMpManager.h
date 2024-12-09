
#ifndef _PRIVATE_MP_MANAGER_H_
#define _PRIVATE_MP_MANAGER_H_

#include "Base/Network.h"
#include "Multipath/MpEncoder.h"

namespace MULTIPATH
{
    enum class TYPE
    {
        Invalid,
        Client,
        Server,
    };

    class PrivateMpManager
    {
    public:
        virtual
       ~PrivateMpManager(){};

    protected:
        PrivateMpManager(){};

        Network::NetworkClient  _network_client_0;
        Network::NetworkClient  _network_client_1;
        Network::NetworkClient  _network_client_2;

        Network::NetworkServer  _network_server_0;
        Network::NetworkServer  _network_server_1;
        Network::NetworkServer  _network_server_2;

        uint32_t                _crc        = 0u;
        TYPE                    _type       = TYPE::Invalid;
        AES::KEY256             _key_aes{};
        AES::WORDS              _key_mp {};

        bool                    _use_port_0 = false;
        bool                    _use_port_1 = false;
        bool                    _use_port_2 = false;
        TYPE_SINGLE             _channel    = TYPE_SINGLE::EMPTY;
    };
}

#endif // _PRIVATE_MP_MANAGER_H_
