
#if defined(ENCODER_PLATFORM_LINUX)
    #include <stdio.h>
    #include <string.h>
#elif defined(ENCODER_PLATFORM_WINDOWS)
    #include <stdio.h>
    #include <string.h>
    #include <thread>
#endif

#include "Base/Network.h"


namespace Network
{
    bool NetworkServer::initialize(MODE Mode, uint16_t Port)
    {
        _mode = Mode;

        if (_mode == MODE::TCP)
        {
            return Server::Tcp::initialize(_socket_local, Port);
        }
        else if (_mode == MODE::UDP)
        {
            return Server::Udp::initialize(_socket_common, Port);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    bool NetworkServer::konnect()
    {
        if (_mode == MODE::TCP)
        {
            return Server::Tcp::konnect(_socket_local, _socket_remote);
        }
        else if (_mode == MODE::UDP)
        {
            return Server::Udp::konnect(_socket_common, _socket_address_remote);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    bool NetworkServer::deinitialize()
    {
        if (_mode == MODE::TCP)
        {
            return Server::Tcp::deinitialize(_socket_local, _socket_remote);
        }
        else if (_mode == MODE::UDP)
        {
            return Server::Udp::deinitialize(_socket_common);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
}
