
#include <stdio.h>
#include <string.h>
#include <thread>

#include "Base/Network.h"


namespace Network::Server::Udp
{
    bool initialize(SOCKET& SocketCommon, uint16_t Port)
    {
        constexpr BYTE major = 2;
        constexpr BYTE minor = 2;

        WSADATA wsa_data;

        if (WSAStartup(MAKEWORD(major, minor), &wsa_data))
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize WSA\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketCommon = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (SocketCommon == INVALID_SOCKET)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create local socket\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        u_long mode = 1;

        if (ioctlsocket(SocketCommon, FIONBIO, &mode))
        {
            fprintf(stderr, "%s:%d:%s: Failed to make socket non-blocking\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SOCKADDRIN socket_address_local{};

        socket_address_local.sin_family         = AF_INET;
        socket_address_local.sin_addr.s_addr    = INADDR_ANY;
        socket_address_local.sin_port           = htons(Port);

        if (bind(SocketCommon, (struct sockaddr*)& socket_address_local, sizeof(socket_address_local)) == SOCKET_ERROR)
        {
            fprintf(stderr, "%s:%d:%s: Failed to bind\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool konnect(SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress)
    {
        constexpr uint8_t   buffer_data_expected            = 0x33;

        uint8_t             buffer_data                     = 0;
        int32_t             buffer_length                   = static_cast<int32_t>(sizeof(buffer_data));
        int32_t             socket_remote_address_length    = static_cast<int32_t>(sizeof(SocketRemoteAddress));

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

        if ((SocketCommon != INVALID_SOCKET) && (closesocket(SocketCommon) == SOCKET_ERROR))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close local socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        if (WSACleanup())
        {
            fprintf(stderr, "%s:%d:%s: Failed to unload WSA\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        SocketCommon = INVALID_SOCKET;

        return ret_val;
    }
}
