

#ifndef _OTP_MANAGER_H_
#define _OTP_MANAGER_H_

#include <stdint.h>
#include <string>

#include "Base/Aes.h"
#include "Base/Buffer.h"
#include "Private/PrivateOtpManager.h"

namespace ONETIMEPAD
{
    class OtpManager : public PrivateOtpManager
    {
    public:
        OtpManager(){};
       ~OtpManager(){};

        /**
         * Initialize AES encoder internally, and prepare to connect to server at IP address Address, and port Port.
         * This instance will be a server if Address is empty. Otherwise, it will be a client.
         * @param InitialKeyAes 128-bit initial AES key.
         * @param InitialKeyOtp 128-bit partial OTP key. AES is used to generate the full OTP key.
         * @param Port Port number to connect.
         * @param Address Ip address of the target server.
         * @return True if operation was successful, and false otherwise.
        */
        bool initialize(AES::KEY256& InitialKeyAes, AES::WORDS& InitialKeyOtp, uint16_t Port, std::string Address = "");

        /**
         * Creates a connection request for the server.
         * @return True if operation was successful, and false otherwise.
        */
        bool konnect();

        /**
         * Close connect, and resets the internal state of the instance to be ready for a new connection.
         * @return True if operation was successful, and false otherwise.
        */
        bool deinitialize();

        /**
         * Transmits the entire data of the BUFFER_T structure to the receiving endpoint.
         * @param Buffer BUFFER_T structure containing data to be transmitted.
         * @return True if operation was successful, and false otherwise.
        */
        template<uint32_t PacketSize>
        bool transmit(BUFFER::BUFFER_T<PacketSize>& Buffer);

        /**
         * Blocks until an entire BUFFER_T structure is received.
         * @param Buffer Buffer space for the receiving data.
         * @return True if operation was successful, and false if it timeout or there was an internal error.
        */
        template<uint32_t PacketSize>
        bool receive(BUFFER::BUFFER_T<PacketSize>& Buffer);
    };
}

#include "OneTimePad/OtpManager.inl"

#endif // _OTP_MANAGER_H_
