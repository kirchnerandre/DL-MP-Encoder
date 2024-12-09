
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/socket.h>

#include "Base/Network.h"


namespace Network::Client::Tcp
{
    bool initialize(SOCKET& SocketRemote, SOCKADDRIN& SocketRemoteAddress, uint16_t Port, std::string Address)
    {
        int32_t socket_remote = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_remote < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to remote local socket\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketRemote = static_cast<uint32_t>(socket_remote);

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
        if (connect(static_cast<int32_t>(SocketRemote), reinterpret_cast<struct sockaddr*>(& SocketRemoteAddress), sizeof(SocketRemoteAddress)) < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to connect\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        int32_t flags = fcntl(static_cast<int32_t>(SocketRemote), F_GETFL, 0);

        if (flags < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to get flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        flags = flags | O_NONBLOCK;

        if (fcntl(static_cast<int32_t>(SocketRemote), F_SETFL, flags))
        {
            fprintf(stderr, "%s:%d:%s: Failed to set flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }


        return true;
    }


    bool deinitialize(SOCKET& SocketRemote)
    {
        bool ret_val = true;

        if ((SocketRemote> 0) && (shutdown(static_cast<int32_t>(SocketRemote), SHUT_RDWR) < 0))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close remote socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        SocketRemote = 0u;

        return ret_val;
    }
}
