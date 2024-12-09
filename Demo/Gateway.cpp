
#include <stdio.h>
#include <string>

#include "Base/Network.h"


int main(int argc, char** argv)
{
    constexpr uint32_t      packet_size             = 1024u;
    constexpr uint32_t      timeout_communication   = 10u;

    int32_t                 ret_val                 = 0;
    uint32_t                parameter               = 0u;
    uint32_t                port_input              = 0u;
    uint32_t                port_output             = 0u;
    std::string             address_output;
    uint32_t                timeout_connection      = 0u;
    uint32_t                timeout                 = 0u;
    Network::NetworkClient  client;
    Network::NetworkServer  server;

    if (argc != 5)
    {
        fprintf(stderr, "%s:%d:%s: MP_GATEWAY.exe PORT_INPUT PORT_OUTPUT ADDRESS_OUTPUT TIMEOUT\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    port_input          = std::stoul(argv[++parameter]);
    port_output         = std::stoul(argv[++parameter]);
    address_output      = argv[++parameter];
    timeout_connection  = std::stoul(argv[++parameter]);

    if (!server.initialize(Network::Network::MODE::TCP, port_input))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!client.initialize(Network::Network::MODE::TCP, port_output, address_output))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    while (1)
    {
        if (server.konnect())
        {
            fprintf(stderr, "%s:%d:%s: Succeed connecting server\n", __FILE__, __LINE__, __FUNCTION__);
            break;
        }
        else if (!--timeout_connection)
        {
            fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
            goto terminate;
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Trying to connect\n", __FILE__, __LINE__, __FUNCTION__);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
        }
    }

    while (1)
    {
        if (client.konnect())
        {
            fprintf(stderr, "%s:%d:%s: Succeed connecting client\n", __FILE__, __LINE__, __FUNCTION__);
            break;
        }
        else if (!--timeout_connection)
        {
            fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
            goto terminate;
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Trying to connect\n", __FILE__, __LINE__, __FUNCTION__);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
        }
    }

    timeout = timeout_communication;

    while (1)
    {
        PACKET::PACKET_T<packet_size>   packet{};

        while (1)
        {
            if (server.receive(packet))
            {
                timeout = timeout_communication;
                break;
            }

            if (!--timeout)
            {
                fprintf(stderr, "%s:%d:%s: Timeout receiving\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }

        while (1)
        {
            if (client.transmit(packet))
            {
                timeout = timeout_communication;
                break;
            }

            if (!--timeout)
            {
                fprintf(stderr, "%s:%d:%s: Timeout transmitting\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
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
