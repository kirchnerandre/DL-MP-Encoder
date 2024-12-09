
#include <stdio.h>

#include "Base/Aes.h"
#include "Base/Endianness.h"
#include "Base/Network.h"


namespace MULTIPATH
{
    namespace
    {
        template<uint32_t PacketSize>
        bool internal_transmit(Network::NetworkClient&          NetworkClient,
                               Network::NetworkServer&          NetworkServer,
                               TYPE                             Type,
                               BUFFER::BUFFER_T<PacketSize>&    Buffer)
        {
            if (Type == TYPE::Client)
            {
                return NetworkClient.transmit(Buffer);
            }
            else if (Type == TYPE::Server)
            {
                return NetworkServer.transmit(Buffer);
            }
            else
            {
                fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }


        template<uint32_t PacketSize>
        bool internal_receive(Network::NetworkClient&       NetworkClient,
                              Network::NetworkServer&       NetworkServer,
                              TYPE                          Type,
                              BUFFER::BUFFER_T<PacketSize>& Buffer)
        {
            if (Type == TYPE::Client)
            {
                if (!NetworkClient.receive(Buffer))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else if (Type == TYPE::Server)
            {
                if (!NetworkServer.receive(Buffer))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
            }
            else
            {
                fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            return true;
        }
    }


    template<uint32_t PacketSize>
    bool MpManager::transmit(BUFFER::BUFFER_T<PacketSize>& Buffer)
    {
        BUFFER::BUFFER_T<PacketSize> key_mp  {};
        BUFFER::BUFFER_T<PacketSize> buffer_0{};
        BUFFER::BUFFER_T<PacketSize> buffer_1{};
        BUFFER::BUFFER_T<PacketSize> buffer_2{};

        for (uint32_t i = 0u; i < sizeof(BUFFER::BUFFER_T<PacketSize>) / sizeof(AES::WORDS); i++)
        {
            this->_key_aes.Round = 0u;

            if (!AES::encode(this->_key_aes, this->_key_mp))
            {
                fprintf(stderr, "%s:%d:%s: Failed to encode OTP key\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            memcpy(&key_mp[i * sizeof(AES::WORDS)], &this->_key_mp, sizeof(AES::WORDS));
        }

        Endianness::hton32(key_mp.Frame,  0u);
        Endianness::hton32(key_mp.Offset, 0u);

        if (!encode_buffer(buffer_0, buffer_1, buffer_2, Buffer, key_mp))
        {
            fprintf(stderr, "%s:%d:%s: Failed to encode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (this->_use_port_0)
        {
            if (!internal_transmit(this->_network_client_0, this->_network_server_0, this->_type, buffer_0))
            {
                fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        if (this->_use_port_1)
        {
            if (!internal_transmit(this->_network_client_1, this->_network_server_1, this->_type, buffer_1))
            {
                fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        if (this->_use_port_2)
        {
            if (!internal_transmit(this->_network_client_2, this->_network_server_2, this->_type, buffer_2))
            {
                fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        return true;
    }


    template<uint32_t PacketSize>
    bool MpManager::receive(BUFFER::BUFFER_T<PacketSize>& Buffer, TYPE_SINGLE& Channel)
    {
        Channel = TYPE_SINGLE::EMPTY;

        if (this->_channel == TYPE_SINGLE::TYPE_0)
        {
            if (this->_use_port_1)
            {
                this->_channel = TYPE_SINGLE::TYPE_1;
            }
            else if (this->_use_port_2)
            {
                this->_channel = TYPE_SINGLE::TYPE_2;
            }
        }
        else if (this->_channel == TYPE_SINGLE::TYPE_1)
        {
            if (this->_use_port_2)
            {
                this->_channel = TYPE_SINGLE::TYPE_2;
            }
            else if (this->_use_port_0)
            {
                this->_channel = TYPE_SINGLE::TYPE_0;
            }
        }
        else if (this->_channel == TYPE_SINGLE::TYPE_2)
        {
            if (this->_use_port_0)
            {
                this->_channel = TYPE_SINGLE::TYPE_0;
            }
            else if (this->_use_port_1)
            {
                this->_channel = TYPE_SINGLE::TYPE_1;
            }
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid channel\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (this->_channel == TYPE_SINGLE::TYPE_0)
        {
            if (!internal_receive(this->_network_client_0, this->_network_server_0, this->_type, Buffer))
            {
                fprintf(stderr, "%s:%d:%s: Failed to receive through channel 0\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            Channel = TYPE_SINGLE::TYPE_0;
        }
        else if (this->_channel == TYPE_SINGLE::TYPE_1)
        {
            if (!internal_receive(this->_network_client_1, this->_network_server_1, this->_type, Buffer))
            {
                fprintf(stderr, "%s:%d:%s: Failed to receive through channel 1\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            Channel = TYPE_SINGLE::TYPE_1;
        }
        else if (this->_channel == TYPE_SINGLE::TYPE_2)
        {
            if (!internal_receive(this->_network_client_2, this->_network_server_2, this->_type, Buffer))
            {
                fprintf(stderr, "%s:%d:%s: Failed to receive through channel 2\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            Channel = TYPE_SINGLE::TYPE_2;
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid channel\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }
}
