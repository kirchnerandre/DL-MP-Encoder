
#include <stdio.h>

#include "Base/Aes.h"
#include "Base/Endianness.h"
#include "Base/Network.h"
#include "Multipath/MpManager.h"


namespace MULTIPATH
{
    namespace
    {
        bool internal_initialize(Network::NetworkClient&    NetworkClient,
                                 Network::NetworkServer&    NetworkServer,
                                 uint16_t                   Port,
                                 std::string                Address)
        {
            if (Address.length())
            {
                if (!NetworkClient.initialize(Network::Network::MODE::TCP, Port, Address))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to initialize Port\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else
            {
                if (!NetworkServer.initialize(Network::Network::MODE::TCP, Port))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to initialize Port\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }

            return true;
        }


        bool internal_konnect(Network::NetworkClient&   NetworkClient,
                              Network::NetworkServer&   NetworkServer,
                              TYPE                      Type)
        {
            if (Type == TYPE::Client)
            {
                return NetworkClient.konnect();
            }
            else if (Type == TYPE::Server)
            {
                return NetworkServer.konnect();
            }
            else
            {
                fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }


        bool internal_deinitialize(Network::NetworkClient&  NetworkClient,
                                   Network::NetworkServer&  NetworkServer,
                                   TYPE                     Type)
        {
            if (Type == TYPE::Client)
            {
                return NetworkClient.deinitialize();
            }
            else if (Type == TYPE::Server)
            {
                return NetworkServer.deinitialize();
            }
            else
            {
                fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }
    }


    bool MpManager::initialize( AES::KEY256&    InitialKeyAes,
                                AES::WORDS&     InitialKeyOtp,
                                uint16_t        Port0,
                                uint16_t        Port1,
                                uint16_t        Port2,
                                std::string     Address0,
                                std::string     Address1,
                                std::string     Address2)
    {
        this->_key_aes  = InitialKeyAes;
        this->_key_mp   = InitialKeyOtp;

        if ((Address0.length()) && (Address1.length()) && (Address2.length()))
        {
            this->_type = TYPE::Client;
        }
        else
        {
            this->_type = TYPE::Server;
        }

        if (Port0)
        {
            if (!internal_initialize(this->_network_client_0, this->_network_server_0, Port0, Address0))
            {
                fprintf(stderr, "%s:%d:%s: Failed to initialize Port0\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            this->_channel    = TYPE_SINGLE::TYPE_0;
            this->_use_port_0 = true;
        }

        if (Port1)
        {
            if (!internal_initialize(this->_network_client_1, this->_network_server_1, Port1, Address1))
            {
                fprintf(stderr, "%s:%d:%s: Failed to initialize Port1\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            this->_channel    = TYPE_SINGLE::TYPE_1;
            this->_use_port_1 = true;
        }

        if (Port2)
        {
            if (!internal_initialize(this->_network_client_2, this->_network_server_2, Port2, Address2))
            {
                fprintf(stderr, "%s:%d:%s: Failed to initialize Port2\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            this->_channel    = TYPE_SINGLE::TYPE_2;
            this->_use_port_2 = true;
        }

        return true;
    }


    bool MpManager::konnect()
    {
        if (this->_use_port_0)
        {
            if (!internal_konnect(this->_network_client_0, this->_network_server_0, this->_type))
            {
                fprintf(stderr, "%s:%d:%s: Failed to connect Port0\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        if (this->_use_port_1)
        {
            if (!internal_konnect(this->_network_client_1, this->_network_server_1, this->_type))
            {
                fprintf(stderr, "%s:%d:%s: Failed to connect Port1\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        if (this->_use_port_2)
        {
            if (!internal_konnect(this->_network_client_2, this->_network_server_2, this->_type))
            {
                fprintf(stderr, "%s:%d:%s: Failed to connect Port2\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        return true;
    }


    bool MpManager::deinitialize()
    {
        if (this->_use_port_0)
        {
            if (!internal_deinitialize(this->_network_client_0, this->_network_server_0, this->_type))
            {
                fprintf(stderr, "%s:%d:%s: Failed to deinitialize Port0\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            this->_use_port_0 = false;
        }

        if (this->_use_port_1)
        {
            if (!internal_deinitialize(this->_network_client_1, this->_network_server_1, this->_type))
            {
                fprintf(stderr, "%s:%d:%s: Failed to deinitialize Port1\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            this->_use_port_1 = false;
        }

        if (this->_use_port_2)
        {
            if (!internal_deinitialize(this->_network_client_2, this->_network_server_2, this->_type))
            {
                fprintf(stderr, "%s:%d:%s: Failed to deinitialize Port2\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            this->_use_port_2 = false;
        }

        return true;
    }
}
