
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Base/Network.h"


namespace Network::Server::Udp
{
    bool initialize(SOCKET& SocketCommon, uint16_t Port)
    {
        int32_t socket_commmon = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (socket_commmon < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create local socket\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        int32_t flags = fcntl(static_cast<int32_t>(socket_commmon), F_GETFL, 0);

        if (flags < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to get flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        flags = flags | O_NONBLOCK;

        if (fcntl(static_cast<int32_t>(socket_commmon), F_SETFL, flags))
        {
            fprintf(stderr, "%s:%d:%s: Failed to set flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SOCKADDRIN socket_address_local{};

        socket_address_local.sin_family         = AF_INET;
        socket_address_local.sin_addr.s_addr    = INADDR_ANY;
        socket_address_local.sin_port           = htons(Port);

        if (bind(socket_commmon, reinterpret_cast<sockaddr*>(&socket_address_local), sizeof(socket_address_local)) < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to bind\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketCommon = static_cast<uint32_t>(socket_commmon);

        return true;
    }


    bool konnect(SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress)
    {
        constexpr uint8_t   buffer_data_expected            = 0x33;

        uint8_t             buffer_data                     = 0;
        int32_t             buffer_length                   = static_cast<int32_t  >(sizeof(buffer_data));
        socklen_t           socket_remote_address_length    = static_cast<socklen_t>(sizeof(SocketRemoteAddress));

        int32_t             communicated                    = recvfrom(SocketCommon,
                                                                       reinterpret_cast<char*>(&buffer_data),
                                                                       buffer_length,
                                                                       0,
                                                                       reinterpret_cast<struct sockaddr*>(&SocketRemoteAddress),
                                                                       &socket_remote_address_length);

        if (communicated == SOCKET_ERROR)
        {
            fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if ((communicated != buffer_length) || (buffer_data != buffer_data_expected))
        {
            fprintf(stderr, "%s:%d:%s: Failed to konnect\n", __FILE__, __LINE__, __FUNCTION__);
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
            fprintf(stderr, "%s:%d:%s: Failed to close local socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        SocketCommon = 0;

        return ret_val;
    }
}
