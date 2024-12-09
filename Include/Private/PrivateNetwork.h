
#ifndef _PRIVATE_NETWORK_H_
#define _PRIVATE_NETWORK_H_

#if defined(ENCODER_PLATFORM_LINUX)
    #include <netinet/in.h>
    #include <stdint.h>

    typedef uint32_t            SOCKET;
    typedef struct sockaddr_in  SOCKADDRIN;
#elif defined(ENCODER_PLATFORM_WINDOWS)
    #define WIN32_LEAN_AND_MEAN

    #include <stdint.h>
    #include <windows.h>
    #include <winsock2.h>

    typedef struct sockaddr_in  SOCKADDRIN;
#endif

namespace Network
{
    namespace Client::Tcp
    {
        bool initialize  (SOCKET& SocketRemote, SOCKADDRIN& SocketRemoteAddress, uint16_t Port, std::string Address);
        bool konnect     (SOCKET& SocketRemote, SOCKADDRIN& SocketRemoteAddress);
        bool deinitialize(SOCKET& SocketRemote);
    }

    namespace Client::Udp
    {
        bool initialize  (SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress, uint16_t Port, std::string Address);
        bool konnect     (SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress);
        bool deinitialize(SOCKET& SocketCommon);
    }

    namespace Server::Tcp
    {
        bool initialize  (SOCKET& SocketLocal, uint16_t Port);
        bool konnect     (SOCKET& SocketLocal, SOCKET&  SocketRemote);
        bool deinitialize(SOCKET& SocketLocal, SOCKET&  SocketRemote);
    }

    namespace Server::Udp
    {
        bool initialize  (SOCKET& SocketCommon, uint16_t    Port);
        bool konnect     (SOCKET& SocketCommon, SOCKADDRIN& SocketRemoteAddress);
        bool deinitialize(SOCKET& SocketCommon);
    }

    class PrivateNetwork
    {
    public:
        virtual
       ~PrivateNetwork(){};

    protected:
        PrivateNetwork(){};

#if defined(ENCODER_PLATFORM_LINUX)
        SOCKADDRIN  _socket_address_local   {};
        SOCKADDRIN  _socket_address_remote  {};
        uint32_t    _socket_local           = 0;
        uint32_t    _socket_remote          = 0;
        uint32_t    _socket_common          = 0;
#elif defined(ENCODER_PLATFORM_WINDOWS)
        SOCKADDRIN  _socket_address_local   {};
        SOCKADDRIN  _socket_address_remote  {};
        SOCKET      _socket_local           = INVALID_SOCKET;
        SOCKET      _socket_remote          = INVALID_SOCKET;
        SOCKET      _socket_common          = INVALID_SOCKET;
#endif
    };
}

#endif // _PRIVATE_NETWORK_H_
