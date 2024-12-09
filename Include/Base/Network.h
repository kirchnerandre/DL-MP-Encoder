
#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdint.h>
#include <string>

#include "Base/Packet.h"
#include "Private/PrivateNetwork.h"

namespace Network
{
    class Network : public PrivateNetwork
    {
    public:
        enum class MODE
        {
            NONE,
            TCP,
            UDP,
        };

        virtual
       ~Network(){};

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

        template<uint32_t PacketSize>
        bool transmit(PACKET::PACKET_T<PacketSize>& Packet);

        template<uint32_t PacketSize>
        bool receive(PACKET::PACKET_T<PacketSize>& Packet);

    protected:
        Network(){};

        MODE _mode = MODE::NONE;
    };


    class NetworkClient : public Network
    {
    public:
        NetworkClient(){};
       ~NetworkClient(){};

        /**
         * Prepare to connect to server at IP address Address, and port Port.
         * @param Mode Supported modes are TCP and UDP.
         * @param Port Port number to connect.
         * @param Address Ip address of the target server.
         * @return True if operation was successful, and false otherwise.
        */
        bool initialize(MODE Mode, uint16_t Port, std::string Address);

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
    };


    class NetworkServer : public Network
    {
    public:
        NetworkServer(){};
       ~NetworkServer(){};

        /**
         * Initializes server to bind and listen a port Port for a connectin request from the client.
         * @param Mode Supported modes are TCP and UDP.
         * @param Port Port number that the server is going to bind and listen.
         * @return True if operation was successful, and false otherwise.
        */
        bool initialize(MODE Mode, uint16_t Port);

        /**
         * Listen non-blocking for a single connecting request.
         * @return True if operation was successful, and false otherwise.
        */
        bool konnect();

        /**
         * Close connect, and resets the internal state of the instance to be ready for a new connection.
         * @return True if operation was successful, and false otherwise.
        */
        bool deinitialize();
    };
}

#include "Base/Network.inl"

#endif // _NETWORK_H_
