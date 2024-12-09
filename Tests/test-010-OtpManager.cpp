
#include <chrono>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <thread>

#include "OneTimePad/OtpManager.h"


bool server_client_communicate()
{
    constexpr uint32_t                          packet_size         = 128u;

    bool                                        ret_val             = true;
    std::string                                 address             = "127.0.0.1";
    uint16_t                                    port                = 20000u;
    AES::KEY256                                 key_aes             = { 0u, 0x5fd92f6f, 0x53853c01, 0x0bb2124a, 0x21af89e0 };
    AES::WORDS                                  key_otp             = {     0x8fc46159, 0xdd05af88, 0xda98f727, 0x60004b30 };

    ONETIMEPAD::OtpManager                      client;
    ONETIMEPAD::OtpManager                      server;

    BUFFER::BUFFER_T<packet_size>               buffer_tmp          {};
    BUFFER::BUFFER_T<packet_size>               buffer_server       {};
    BUFFER::BUFFER_T<packet_size>               buffer_client       {};

    BUFFER::BUFFER_T<packet_size>               message_server      = { 'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  's',  'e',  'r',  'v',  'e',  'r',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  's',  'e',  'r',  'v',  'e',  'r',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  's',  'e',  'r',  'v',  'e',  'r',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  's',  'e',  'r',  'v',  'e',  'r',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  's',  'e',  'r',  'v',  'e',  'r',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  's',  'e',  'r',  'v',  'e',  'r',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  's',  'e',  'r',  'v',  'e',  'r',  ' ',  ' ',
                                                                        ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  0u,   0u,   0u,   0u };

    BUFFER::BUFFER_T<packet_size>               message_client      = { 'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  'c',  'l',  'i',  'e',  'n',  't',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  'c',  'l',  'i',  'e',  'n',  't',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  'c',  'l',  'i',  'e',  'n',  't',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  'c',  'l',  'i',  'e',  'n',  't',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  'c',  'l',  'i',  'e',  'n',  't',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  'c',  'l',  'i',  'e',  'n',  't',  ' ',  ' ',
                                                                        'H',  'i',  ' ',  'f',  'r',  'o',  'm',  ' ',  'c',  'l',  'i',  'e',  'n',  't',  ' ',  ' ',
                                                                        ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  0u,   0u,   0u,   0u };

    if (!server.initialize(key_aes, key_otp, port))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize(key_aes, key_otp, port, address))
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

    memcpy(&buffer_tmp, &message_server, sizeof(BUFFER::BUFFER_T<packet_size>));

    if (!server.transmit(buffer_tmp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.receive(buffer_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(&message_server, &buffer_client, sizeof(BUFFER::BUFFER_T<packet_size>)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    memcpy(&buffer_tmp, &message_client, sizeof(BUFFER::BUFFER_T<packet_size>));

    if (!client.transmit(buffer_tmp))
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

    if (memcmp(&message_client, &buffer_server, sizeof(BUFFER::BUFFER_T<packet_size>)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
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
