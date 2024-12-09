
#include <stdio.h>
#include <ws2tcpip.h>

#include "Base/Network.h"


namespace Network::Client::Udp
{
    bool initialize(SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress, uint16_t Port, std::string Address)
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


    bool konnect(SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress)
    {
        u_long mode = 1;

        if (ioctlsocket(SocketCommon, FIONBIO, &mode))
        {
            fprintf(stderr, "%s:%d:%s: Failed to make socket non-blocking\n", __FILE__, __LINE__, __FUNCTION__);
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

        if ((SocketCommon != INVALID_SOCKET) && (shutdown(SocketCommon, SD_BOTH) == SOCKET_ERROR))
        {
            fprintf(stderr, "%s:%d:%s: Failed to shutdown remote socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        if ((SocketCommon != INVALID_SOCKET) && (closesocket(SocketCommon) == SOCKET_ERROR))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close remote socket\n", __FILE__, __LINE__, __FUNCTION__);
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
