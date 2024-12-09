
#include <stdio.h>
#include <string.h>
#include <thread>

#include "Base/Network.h"


namespace Network::Server::Tcp
{
    bool initialize(SOCKET& SocketLocal, uint16_t Port)
    {
        constexpr BYTE major = 2;
        constexpr BYTE minor = 2;

        WSADATA wsa_data;

        if (WSAStartup(MAKEWORD(major, minor), &wsa_data))
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize WSA\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketLocal = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (SocketLocal == INVALID_SOCKET)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create local socket\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        u_long mode = 1;

        if (ioctlsocket(SocketLocal, FIONBIO, &mode))
        {
            fprintf(stderr, "%s:%d:%s: Failed to make socket non-blocking\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SOCKADDRIN socket_address_local{};

        socket_address_local.sin_family         = AF_INET;
        socket_address_local.sin_addr.s_addr    = INADDR_ANY;
        socket_address_local.sin_port           = htons(Port);

        if (bind(SocketLocal, (struct sockaddr*)& socket_address_local, sizeof(socket_address_local)) == SOCKET_ERROR)
        {
            fprintf(stderr, "%s:%d:%s: Failed to bind\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (listen(SocketLocal, 1) == SOCKET_ERROR )
        {
            fprintf(stderr, "%s:%d:%s: Failed to listen\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool konnect(SOCKET& SocketLocal, SOCKET& SocketRemote)
    {
        SocketRemote = accept(SocketLocal, NULL, NULL);

        if (SocketRemote == INVALID_SOCKET)
        {
            fprintf(stderr, "%s:%d:%s: Failed to accept\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        u_long mode = 1;

        if (ioctlsocket(SocketRemote, FIONBIO, &mode))
        {
            fprintf(stderr, "%s:%d:%s: Failed to make socket non-blocking\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool deinitialize(SOCKET& SocketLocal, SOCKET& SocketRemote)
    {
        bool ret_val = true;

        if ((SocketLocal != INVALID_SOCKET) && (closesocket(SocketLocal) == SOCKET_ERROR))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close local socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        if ((SocketRemote != INVALID_SOCKET) && (shutdown(SocketRemote, SD_BOTH) == SOCKET_ERROR))
        {
            fprintf(stderr, "%s:%d:%s: Failed to shutdown remote socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        if ((SocketRemote != INVALID_SOCKET) && (closesocket(SocketRemote) == SOCKET_ERROR))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close remote socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        if (WSACleanup())
        {
            fprintf(stderr, "%s:%d:%s: Failed to unload WSA\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        SocketLocal  = INVALID_SOCKET;
        SocketRemote = INVALID_SOCKET;

        return ret_val;
    }
}
