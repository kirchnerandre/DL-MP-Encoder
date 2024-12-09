
#include <stdio.h>

#include "Base/Network.h"


bool server_client_communicate_buffer_tcp()
{
    constexpr uint32_t                          packet_size         = 128u;

    bool                                        ret_val             = true;
    std::string                                 address             = "127.0.0.1";
    uint16_t                                    port                = 10000u;

    BUFFER::BUFFER_T<packet_size>               buffer_server       {};
    BUFFER::BUFFER_T<packet_size>               buffer_client       {};

    BUFFER::BUFFER_T<packet_size>               message_server      = { 'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ' };

    BUFFER::BUFFER_T<packet_size>               message_client      = { 'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ' };

    Network::NetworkClient                      client;
    Network::NetworkServer                      server;

    if (!server.initialize(Network::Network::MODE::TCP, port))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize(Network::Network::MODE::TCP, port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to connect\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.receive(buffer_server))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (client.receive(buffer_client))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.transmit(message_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.transmit(message_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.receive(buffer_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.receive(buffer_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_client, &buffer_server, sizeof(buffer_server)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_server, &buffer_client, sizeof(buffer_client)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    return ret_val;
}


bool server_client_communicate_buffer_udp()
{
    constexpr uint32_t                          packet_size         = 128u;

    bool                                        ret_val             = true;
    std::string                                 address             = "127.0.0.1";
    uint16_t                                    port                = 10001u;

    BUFFER::BUFFER_T<packet_size>               buffer_server       {};
    BUFFER::BUFFER_T<packet_size>               buffer_client       {};

    BUFFER::BUFFER_T<packet_size>               message_server      = { 'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ' };

    BUFFER::BUFFER_T<packet_size>               message_client      = { 'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ' };

    Network::NetworkClient                      client;
    Network::NetworkServer                      server;

    if (!server.initialize(Network::Network::MODE::UDP, port))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize(Network::Network::MODE::UDP, port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to connect\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.transmit(message_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.transmit(message_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.receive(buffer_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.receive(buffer_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_client, &buffer_server, sizeof(buffer_server)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_server, &buffer_client, sizeof(buffer_client)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    return ret_val;
}


bool server_client_communicate_packet_tcp()
{
    constexpr uint32_t                          packet_size         = 128u;

    bool                                        ret_val             = true;
    std::string                                 address             = "127.0.0.1";
    uint16_t                                    port                = 10002u;

    PACKET::PACKET_T<packet_size>               buffer_server       {};
    PACKET::PACKET_T<packet_size>               buffer_client       {};
    PACKET::PACKET_T<packet_size>               message_server      {};
    PACKET::PACKET_T<packet_size>               message_client      {};

    Network::NetworkClient                      client;
    Network::NetworkServer                      server;

    message_server.Buffer                                           = { 0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, };

    message_client.Buffer                                           = { 0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xa9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xa9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xa9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xa9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xa9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xa9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                        0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xa9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, };

    if (!server.initialize(Network::Network::MODE::TCP, port))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize(Network::Network::MODE::TCP, port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to connect\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.receive(buffer_server))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (client.receive(buffer_client))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.transmit(message_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.transmit(message_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.receive(buffer_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.receive(buffer_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_client, &buffer_server, sizeof(buffer_server)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_server, &buffer_client, sizeof(buffer_client)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    return ret_val;
}


bool server_client_communicate_packet_udp()
{
    constexpr uint32_t                          packet_size         = 128u;

    bool                                        ret_val             = true;
    std::string                                 address             = "127.0.0.1";
    uint16_t                                    port                = 10003u;

    PACKET::PACKET_T<packet_size>               buffer_server       {};
    PACKET::PACKET_T<packet_size>               buffer_client       {};

    PACKET::PACKET_T<packet_size>               message_server      = { 'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 's', 'e', 'r', 'v', 'e', 'r', ' ', ' ' };

    PACKET::PACKET_T<packet_size>               message_client      = { 'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ',
                                                                        'H', 'i', ' ', 'f', 'r', 'o', 'm', ' ', 'c', 'l', 'i', 'e', 'n', 't', ' ', ' ' };

    Network::NetworkClient                      client;
    Network::NetworkServer                      server;

    if (!server.initialize(Network::Network::MODE::UDP, port))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize(Network::Network::MODE::UDP, port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to connect\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.konnect())
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.transmit(message_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.transmit(message_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.receive(buffer_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.receive(buffer_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_client, &buffer_server, sizeof(buffer_server)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_server, &buffer_client, sizeof(buffer_client)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    return ret_val;
}


int main(int argc, char** argv)
{
    if (!server_client_communicate_buffer_tcp())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!server_client_communicate_buffer_udp())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!server_client_communicate_packet_tcp())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!server_client_communicate_packet_udp())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
