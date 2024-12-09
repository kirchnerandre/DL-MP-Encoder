
#ifndef _PRIVATE_INTEGRITY_CHECK_MANAGER_H_
#define _PRIVATE_INTEGRITY_CHECK_MANAGER_H_

#include "Base/Network.h"

namespace INTEGRITYCHECK
{
    enum class TYPE
    {
        Invalid,
        Client,
        Server,
    };

    class PrivateIntegrityCheckManager
    {
    public:
        virtual
       ~PrivateIntegrityCheckManager(){};

    protected:
        PrivateIntegrityCheckManager(){};

        Network::NetworkClient  _network_client;
        Network::NetworkServer  _network_server;

        TYPE                    _type       = TYPE::Invalid;
    };
}

#endif // _PRIVATE_INTEGRITY_CHECK_MANAGER_H_
