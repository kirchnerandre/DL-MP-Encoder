
#include <stdio.h>

#include "Base/Aes.h"
#include "Base/Network.h"
#include "OneTimePad/OtpEncoder.h"
#include "OneTimePad/OtpManager.h"


namespace ONETIMEPAD
{
    bool OtpManager::initialize(AES::KEY256& InitialKeyAes, AES::WORDS& InitialKeyOtp, uint16_t Port, std::string Address)
    {
        this->_key_aes = InitialKeyAes;
        this->_key_otp = InitialKeyOtp;

        if (Address.length() > 0u)
        {
            this->_type = TYPE::Client;
            return this->_network_client.initialize(Network::Network::MODE::TCP, Port, Address);
        }
        else
        {
            this->_type = TYPE::Server;
            return this->_network_server.initialize(Network::Network::MODE::TCP, Port);
        }
    }


    bool OtpManager::konnect()
    {
        if (this->_type == TYPE::Client)
        {
            return this->_network_client.konnect();
        }
        else if (this->_type == TYPE::Server)
        {
            return this->_network_server.konnect();
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    bool OtpManager::deinitialize()
    {
        if (this->_type == TYPE::Client)
        {
            return this->_network_client.deinitialize();
        }
        else if (this->_type == TYPE::Server)
        {
            return this->_network_server.deinitialize();
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
}
