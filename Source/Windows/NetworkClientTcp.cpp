
#include <stdio.h>
#include <ws2tcpip.h>

#include "Base/Network.h"


namespace Network::Client::Tcp
{
    bool initialize(SOCKET& SocketRemote, SOCKADDRIN& SocketRemoteAddress, uint16_t Port, std::string Address)
    {
        constexpr BYTE major = 2;
        constexpr BYTE minor = 2;

        WSADATA wsa_data;

        if (WSAStartup(MAKEWORD(major, minor), &wsa_data))
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize WSA\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketRemote = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (SocketRemote == INVALID_SOCKET)
        {
            fprintf(stderr, "%s:%d:%s: Failed to remote local socket\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketRemoteAddress.sin_family  = AF_INET;
        SocketRemoteAddress.sin_port    = htons(Port);

        if (inet_pton(AF_INET, Address.c_str(), &SocketRemoteAddress.sin_addr) <= 0)
        {
            fprintf(stderr, "%s:%d:%s: Invalid address\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool konnect(SOCKET& SocketRemote, SOCKADDRIN& SocketRemoteAddress)
    {
        if (connect(SocketRemote, (struct sockaddr*)& SocketRemoteAddress, sizeof(SocketRemoteAddress)) == SOCKET_ERROR)
        {
            fprintf(stderr, "%s:%d:%s: Failed to connect\n", __FILE__, __LINE__, __FUNCTION__);
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


    bool deinitialize(SOCKET& SocketRemote)
    {
        bool ret_val = true;

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

        SocketRemote = INVALID_SOCKET;

        return ret_val;
    }
}
