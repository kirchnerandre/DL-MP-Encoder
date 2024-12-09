
#include <stdio.h>

#include "Base/Aes.h"
#include "Base/Network.h"
#include "OneTimePad/OtpEncoder.h"


namespace ONETIMEPAD
{
    template<uint32_t PacketSize>
    bool OtpManager::transmit(BUFFER::BUFFER_T<PacketSize>& Buffer)
    {
        BUFFER::BUFFER_T<PacketSize> key_otp{};

        for (uint32_t i = 0u; i < sizeof(BUFFER::BUFFER_T<PacketSize>) / sizeof(AES::WORDS); i++)
        {
            this->_key_aes.Round = 0u;

            if (!AES::encode(this->_key_aes, this->_key_otp))
            {
                fprintf(stderr, "%s:%d:%s: Failed to encode OTP key\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            memcpy(&key_otp[i * sizeof(AES::WORDS)], &this->_key_otp, sizeof(AES::WORDS));
        }

        if (!encode(Buffer, key_otp))
        {
            fprintf(stderr, "%s:%d:%s: Failed to encode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (this->_type == TYPE::Client)
        {
            bool ret_val = this->_network_client.transmit(Buffer);

            return ret_val;
        }
        else if (this->_type == TYPE::Server)
        {
            return this->_network_server.transmit(Buffer);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    template<uint32_t PacketSize>
    bool OtpManager::receive(BUFFER::BUFFER_T<PacketSize>& Buffer)
    {
        BUFFER::BUFFER_T<PacketSize> key_otp{};

        if (this->_type == TYPE::Client)
        {
            if (!this->_network_client.receive(Buffer))
            {
                return false;
            }
        }
        else if (this->_type == TYPE::Server)
        {
            if (!this->_network_server.receive(Buffer))
            {
                return false;
            }
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        for (uint32_t i = 0u; i < sizeof(BUFFER::BUFFER_T<PacketSize>) / sizeof(AES::WORDS); i++)
        {
            this->_key_aes.Round = 0u;

            if (!AES::encode(this->_key_aes, this->_key_otp))
            {
                fprintf(stderr, "%s:%d:%s: Failed to encode OTP key\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            memcpy(&key_otp[i * sizeof(AES::WORDS)], &this->_key_otp, sizeof(AES::WORDS));
        }

        if (!decode(Buffer, key_otp))
        {
            fprintf(stderr, "%s:%d:%s: Failed to decode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }
}
