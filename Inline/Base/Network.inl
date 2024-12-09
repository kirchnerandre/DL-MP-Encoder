
#if defined(ENCODER_PLATFORM_LINUX)
    #include <chrono>
    #include <fcntl.h>
    #include <stdio.h>
    #include <sys/socket.h>
    #include <thread>
    #include <unistd.h>

    inline uint32_t get_last_error_code()
    {
        return errno;
    }

    #define  SOCKET_ERROR               (-1)
    #define  SOCKET_ERROR_TRY_AGAIN     (EAGAIN)
    #define  SOCKET_ERROR_WOULD_BLOCK   (EWOULDBLOCK)
#elif defined(ENCODER_PLATFORM_WINDOWS)
    #include <chrono>
    #include <fcntl.h>
    #include <stdio.h>
    #include <thread>
    #include <winsock2.h>

    inline uint32_t get_last_error_code()
    {
        return WSAGetLastError();
    }

    #define  SOCKET_ERROR_TRY_AGAIN     (WSAEWOULDBLOCK)
    #define  SOCKET_ERROR_WOULD_BLOCK   (WSAEWOULDBLOCK)
#endif


namespace Network
{
    namespace
    {
        bool communicate_tcp(SOCKET Socket, uint8_t* Buffer, uint32_t Length, bool Direction)
        {
            constexpr uint32_t  timeout_max     = 1000u;
            constexpr uint32_t  time_sleep_max  = 100u;
            constexpr uint32_t  time_sleep_min  = 0u;
            uint32_t            time_sleep      = time_sleep_min;
            uint32_t            timeout_current = 0u;
            uint32_t            offset          = 0u;

            while (timeout_current < timeout_max)
            {
                int32_t communicated = 0;

                if (Direction)
                {
                    communicated = send(Socket, reinterpret_cast<char*>(&Buffer[offset]), static_cast<int32_t>(Length - offset), 0);
                }
                else
                {
                    communicated = recv(Socket, reinterpret_cast<char*>(&Buffer[offset]), static_cast<int32_t>(Length - offset), 0);
                }

                if (communicated == SOCKET_ERROR)
                {
                    if ((get_last_error_code() == SOCKET_ERROR_TRY_AGAIN) || (get_last_error_code() == SOCKET_ERROR_WOULD_BLOCK))
                    {
                        communicated = 0u;
                    }
                    else
                    {
                        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
                        return false;
                    }
                }

                offset += static_cast<size_t>(communicated);

                if (offset == Length)
                {
                    return true;
                }
                else if ((communicated == 0) && (time_sleep < time_sleep_max))
                {
                    time_sleep++;
                }
                else if ((communicated != 0) && (time_sleep > time_sleep_min))
                {
                    time_sleep--;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(time_sleep));

                timeout_current += time_sleep;
            }

            fprintf(stderr, "%s:%d:%s: Timeout\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }


        bool communicate_udp(SOCKET Socket, uint8_t* Buffer, uint32_t Length, bool Direction, SOCKADDRIN& SocketRemoteAddress)
        {
            constexpr uint32_t  timeout_max     = 1000u;
            constexpr uint32_t  time_sleep_max  = 100u;
            constexpr uint32_t  time_sleep_min  = 0u;
            uint32_t            time_sleep      = time_sleep_min;
            uint32_t            timeout_current = 0u;

            while (timeout_current < timeout_max)
            {
                int32_t communicated    = 0;
                int32_t length          = static_cast<uint32_t>(sizeof(SocketRemoteAddress));

                if (Direction)
                {
                    communicated = sendto(Socket, reinterpret_cast<char*>(Buffer), static_cast<int32_t>(Length), 0, reinterpret_cast<struct sockaddr*>(&SocketRemoteAddress), length);
                }
                else
                {
                    communicated = recvfrom(Socket, reinterpret_cast<char*>(Buffer), static_cast<int32_t>(Length), 0, nullptr, 0);
                }

                if (communicated == SOCKET_ERROR)
                {
                    if ((get_last_error_code() == SOCKET_ERROR_TRY_AGAIN) || (get_last_error_code() == SOCKET_ERROR_WOULD_BLOCK))
                    {
                        communicated = 0u;
                    }
                    else
                    {
                        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
                        return false;
                    }
                }
                else if (static_cast<size_t>(communicated) != Length)
                {
                    fprintf(stderr, "%s:%d:%s: Failed to transmit/receive message\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }
                else
                {
                    return true;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(++time_sleep));

                timeout_current += time_sleep;
            }

            fprintf(stderr, "%s:%d:%s: Timeout\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    template<uint32_t PacketSize>
    bool Network::transmit(BUFFER::BUFFER_T<PacketSize>& Buffer)
    {
        uint8_t* buffer = reinterpret_cast<uint8_t*>(&Buffer);

        uint32_t length = sizeof(Buffer);

        if (_mode == MODE::TCP)
        {
            return communicate_tcp(_socket_remote, buffer, length, true);
        }
        else if (_mode == MODE::UDP)
        {
            return communicate_udp(_socket_common, buffer, length, true, _socket_address_remote);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    template<uint32_t PacketSize>
    bool Network::receive(BUFFER::BUFFER_T<PacketSize>& Buffer)
    {
        uint8_t* buffer = reinterpret_cast<uint8_t*>(&Buffer);

        uint32_t length = sizeof(Buffer);

        if (_mode == MODE::TCP)
        {
            return communicate_tcp(_socket_remote, buffer, length, false);
        }
        else if (_mode == MODE::UDP)
        {
            return communicate_udp(_socket_common, buffer, length, false, _socket_address_remote);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    template<uint32_t PacketSize>
    bool Network::transmit(PACKET::PACKET_T<PacketSize>& Packet)
    {
        uint8_t* packet = reinterpret_cast<uint8_t*>(&Packet);

        if (_mode == MODE::TCP)
        {
            return communicate_tcp(_socket_remote, packet, PacketSize, true);
        }
        else if (_mode == MODE::UDP)
        {
            return communicate_udp(_socket_common, packet, PacketSize, true, _socket_address_remote);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    template<uint32_t PacketSize>
    bool Network::receive(PACKET::PACKET_T<PacketSize>& Packet)
    {
        bool        ret_val = true;
        uint8_t*    packet  = reinterpret_cast<uint8_t*>(&Packet);

        if (_mode == MODE::TCP)
        {
            ret_val = communicate_tcp(_socket_remote, packet, PacketSize, false);
        }
        else if (_mode == MODE::UDP)
        {
            ret_val = communicate_udp(_socket_common, packet, PacketSize, false, _socket_address_remote);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid mode\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
        }

        return ret_val;
    }
}
