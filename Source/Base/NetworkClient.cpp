
#if defined(ENCODER_PLATFORM_LINUX)
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <stdio.h>
    #include <string>
    #include <string.h>
    #include <sys/socket.h>
#elif defined(ENCODER_PLATFORM_WINDOWS)
    #include <stdio.h>
    #include <ws2tcpip.h>
#endif

#include "Base/Network.h"


namespace Network
{
    bool NetworkClient::initialize(MODE Mode, uint16_t Port, std::string Address)
    {
        _mode = Mode;

        if (_mode == MODE::TCP)
        {
            return Client::Tcp::initialize(_socket_remote, _socket_address_remote, Port, Address);
        }
        else if (_mode == MODE::UDP)
        {
            return Client::Udp::initialize(_socket_common, _socket_address_remote, Port, Address);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    bool NetworkClient::konnect()
    {
        if (_mode == MODE::TCP)
        {
            return Client::Tcp::konnect(_socket_remote, _socket_address_remote);
        }
        else if (_mode == MODE::UDP)
        {
            return Client::Udp::konnect(_socket_common, _socket_address_remote);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool NetworkClient::deinitialize()
    {
        if (_mode == MODE::TCP)
        {
            return Client::Tcp::deinitialize(_socket_remote);
        }
        else if (_mode == MODE::UDP)
        {
            return Client::Udp::deinitialize(_socket_common);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }
}

