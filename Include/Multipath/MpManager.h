

#ifndef _MP_MANAGER_H_
#define _MP_MANAGER_H_

#include <stdint.h>
#include <string>

#include "Base/Aes.h"
#include "Base/Buffer.h"
#include "Private/PrivateMpManager.h"

namespace MULTIPATH
{
    class MpManager : public PrivateMpManager
    {
    public:
        MpManager(){};
       ~MpManager(){};

        /**
         * Initialize AES encoder internally, and prepare to connect to server at IP address Address, and port Port.
         * This instance will be a server if Address is empty. Otherwise, it will be a client.
         * @param InitialKeyAes 128-bit initial AES key.
         * @param InitialKeyOtp 128-bit partial OTP key. AES is used to generate the full OTP key.
         * @param Port0 Port number to connect for channel 0.
         * @param Port1 Port number to connect for channel 1.
         * @param Port2 Port number to connect for channel 2.
         * @param Address1 Ip address of the target server for channel 0.
         * @param Address2 Ip address of the target server for channel 1.
         * @param Address3 Ip address of the target server for channel 1.
         * @return True if operation was successful, and false otherwise.
        */
        bool initialize(AES::KEY256&    InitialKeyAes,
                        AES::WORDS&     InitialKeyOtp,
                        uint16_t        Port0,
                        uint16_t        Port1,
                        uint16_t        Port2,
                        std::string     Address0 = "",
                        std::string     Address1 = "",
                        std::string     Address2 = "");

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
         * Blocks until an entire BUFFER_T structure is received through channel 2.
         * @param Buffer Buffer space for the receiving data.
         * @param Channel Output paramter that speficies which channel does the data belong to.
         * @return True if operation was successful, and false if it timeout or there was an internal error.
        */
        template<uint32_t PacketSize>
        bool receive(BUFFER::BUFFER_T<PacketSize>& Buffer, TYPE_SINGLE& Channel);
    };
}

#include "Multipath/MpManager.inl"

#endif // _MP_MANAGER_H_
