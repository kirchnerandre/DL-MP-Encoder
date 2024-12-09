
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/socket.h>

#include "Base/Network.h"


namespace Network::Client::Udp
{
    bool initialize(SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress, uint16_t Port, std::string Address)
    {
        int32_t socket_common = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (socket_common < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to remote local socket\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketCommon = static_cast<uint32_t>(socket_common);

        SocketRemoteAddress.sin_family  = AF_INET;
        SocketRemoteAddress.sin_port    = htons(Port);

        if (inet_pton(AF_INET, Address.c_str(), &SocketRemoteAddress.sin_addr) <= 0)
        {
            fprintf(stderr, "%s:%d:%s: Invalid address\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool konnect(SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress)
    {
        int32_t flags = fcntl(static_cast<int32_t>(SocketCommon), F_GETFL, 0);

        if (flags < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to get flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        flags = flags | O_NONBLOCK;

        if (fcntl(static_cast<int32_t>(SocketCommon), F_SETFL, flags))
        {
            fprintf(stderr, "%s:%d:%s: Failed to set flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        uint8_t buffer_data_expected            = 0x33;
        int32_t buffer_length                   = static_cast<int32_t>(sizeof(buffer_data_expected));
        int32_t socket_remote_address_length    = static_cast<int32_t>(sizeof(SocketRemoteAddress));

        int32_t communicated = sendto(SocketCommon,
                                      reinterpret_cast<char*>(&buffer_data_expected),
                                      buffer_length,
                                      0,
                                      reinterpret_cast<struct sockaddr*>(&SocketRemoteAddress),
                                      socket_remote_address_length);

        if (communicated == SOCKET_ERROR)
        {
            fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else
        {
            return true;
        }
    }


    bool deinitialize(SOCKET& SocketCommon)
    {
        bool ret_val = true;

        if ((SocketCommon > 0) && (close(SocketCommon) == SOCKET_ERROR))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        SocketCommon = 0;

        return ret_val;
    }
}
