
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Base/Network.h"


namespace Network::Server::Tcp
{
    bool initialize(SOCKET& SocketLocal, uint16_t Port)
    {
        int32_t socket_local = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_local < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create local socket\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketLocal = static_cast<uint32_t>(socket_local);

        int32_t flags = fcntl(static_cast<int32_t>(SocketLocal), F_GETFL, 0);

        if (flags < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to get flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        flags = flags | O_NONBLOCK;

        if (fcntl(static_cast<int32_t>(SocketLocal), F_SETFL, flags))
        {
            fprintf(stderr, "%s:%d:%s: Failed to set flags\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SOCKADDRIN socket_address_local{};

        socket_address_local.sin_family         = AF_INET;
        socket_address_local.sin_addr.s_addr    = INADDR_ANY;
        socket_address_local.sin_port           = htons(Port);

        if (bind(SocketLocal, reinterpret_cast<sockaddr*>(&socket_address_local), sizeof(socket_address_local)) < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to bind\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (listen(SocketLocal, 1) < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to listen\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool konnect(SOCKET& SocketLocal, SOCKET& SocketRemote)
    {
        SocketRemote = accept(static_cast<int32_t>(SocketLocal), nullptr, nullptr);

        if (SocketRemote < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to accept\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        SocketRemote = static_cast<uint32_t>(SocketRemote);

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


    bool deinitialize(SOCKET& SocketLocal, SOCKET& SocketRemote)
    {
        bool ret_val = true;

        if ((SocketRemote > 0) && (close(static_cast<int32_t>(SocketRemote)) < 0))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close remote socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        SocketRemote = 0u;

        if ((SocketLocal > 0) && (shutdown(static_cast<int32_t>(SocketLocal), SHUT_RDWR) < 0))
        {
            fprintf(stderr, "%s:%d:%s: Failed to close local socket\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        SocketLocal = 0u;

        return ret_val;
    }
}
