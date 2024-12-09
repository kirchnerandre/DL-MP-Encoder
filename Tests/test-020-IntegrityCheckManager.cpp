
#include <chrono>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <thread>

#include "IntegrityCheck/IntegrityCheckManager.h"


bool server_client_communicate()
{
    constexpr uint32_t                          packet_size         = 128u;

    bool                                        ret_val             = true;
    std::string                                 address             = "127.0.0.1";
    uint16_t                                    port                = 40000u;

    INTEGRITYCHECK::IntegrityCheckManager       client;
    INTEGRITYCHECK::IntegrityCheckManager       server;

    PACKET::PACKET_T<packet_size>               packet_tmp          {};
    PACKET::PACKET_T<packet_size>               packet_server       {};
    PACKET::PACKET_T<packet_size>               packet_client       {};

    PACKET::PACKET_T<packet_size>               buffer_server       = { 0x00, 0x00, 0x00, 0x01,
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

    PACKET::PACKET_T<packet_size>               buffer_client       = { 0x00, 0x00, 0x00, 0x01,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, };

    PACKET::PACKET_T<packet_size>               sha512_server       = { 0x00, 0x00, 0x00, 0x02,
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

    PACKET::PACKET_T<packet_size>               sha512_client       = { 0x00, 0x00, 0x00, 0x02,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
                                                                        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, };

    PACKET::PACKET_T<packet_size>               invalid_packet      = { 0x00, 0x00, 0x00, 0x03,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0x00, 0x00, 0x00, 0x00,
                                                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, };

    if (!server.initialize(port))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize(port, address))
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

    if (server.receive(packet_server))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (client.receive(packet_client))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    memcpy(&packet_tmp, &buffer_server, packet_size);

    if (!server.transmit(packet_tmp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.receive(packet_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&buffer_server, &packet_client, packet_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    memcpy(&packet_tmp, &buffer_client, packet_size);

    if (!client.transmit(packet_tmp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.receive(packet_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&buffer_client, &packet_server, packet_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    memcpy(&packet_tmp, &sha512_server, packet_size);

    if (!server.transmit(packet_tmp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.receive(packet_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&sha512_server, &packet_client, packet_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    memcpy(&packet_tmp, &sha512_client, packet_size);

    if (!client.transmit(packet_tmp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.receive(packet_server))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&sha512_client, &packet_server, packet_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    memcpy(&packet_tmp, &invalid_packet, packet_size);

    if (!server.transmit(packet_tmp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (client.receive(packet_client))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    memcpy(&packet_tmp, &invalid_packet, packet_size);

    if (!client.transmit(packet_tmp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.receive(packet_client))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
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
    if (!server_client_communicate())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
