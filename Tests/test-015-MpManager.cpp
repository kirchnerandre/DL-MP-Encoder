
#include <chrono>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <thread>

#include "Multipath/MpEncoder.h"
#include "Multipath/MpManager.h"


bool client_transmits(uint16_t Port0, uint16_t Port1, uint16_t Port2)
{
    constexpr uint32_t                  packet_size             = 128u;

    bool                                ret_val                 = true;
    std::string                         address_0               = "127.0.0.1";
    std::string                         address_1               = "127.0.0.1";
    std::string                         address_2               = "127.0.0.1";
    AES::KEY256                         key_aes                 = { 0u, 0x5fd92f6f, 0x53853c01, 0x0bb2124a, 0x21af89e0 };
    AES::WORDS                          key_mp                  = {     0x8fc46159, 0xdd05af88, 0xda98f727, 0x60004b30 };

    MULTIPATH::TYPE_SINGLE              type_a                  = MULTIPATH::TYPE_SINGLE::EMPTY;
    MULTIPATH::TYPE_SINGLE              type_b                  = MULTIPATH::TYPE_SINGLE::EMPTY;
    MULTIPATH::TYPE_SINGLE              type_c                  = MULTIPATH::TYPE_SINGLE::EMPTY;
    BUFFER::BUFFER_T<packet_size>       message_received_a      {};
    BUFFER::BUFFER_T<packet_size>       message_received_b      {};
    BUFFER::BUFFER_T<packet_size>       message_received_c      {};
    BUFFER::BUFFER_T<packet_size>       message_received_01     {};
    BUFFER::BUFFER_T<packet_size>       message_received_02     {};
    BUFFER::BUFFER_T<packet_size>       message_received_12     {};

    BUFFER::BUFFER_T<packet_size>       message_transmitted     = { 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00,
                                                                    0x04, 0x9e, 0x1a, 0xe4, 0x1c, 0xda, 0x24, 0x6e, 0xce, 0x2d, 0xcf, 0xb5, 0x63, 0x6c, 0x4f, 0x79,
                                                                    0x14, 0x2f, 0x62, 0x2f, 0x0c, 0xcc, 0x37, 0x79, 0xbc, 0x67, 0x12, 0x7d, 0x95, 0x75, 0x7d, 0x99,
                                                                    0x13, 0x97, 0x7d, 0x2f, 0x71, 0xa1, 0x9d, 0x3f, 0xce, 0x6d, 0xf4, 0x31, 0xd9, 0x43, 0xab, 0xed,
                                                                    0x72, 0x0d, 0x1c, 0x7f, 0xd9, 0x54, 0xf8, 0x95, 0xbb, 0x0a, 0x12, 0x50, 0x7f, 0x8f, 0xe9, 0x92,
                                                                    0x26, 0x66, 0xc1, 0x97, 0x07, 0x5f, 0xd6, 0xd6, 0xcc, 0xca, 0x07, 0xa5, 0x0e, 0xb2, 0x92, 0x80,
                                                                    0xbf, 0xae, 0xff, 0x98, 0x02, 0xf7, 0x2d, 0xbe, 0x02, 0x3f, 0x0e, 0x81, 0xce, 0xf8, 0x14, 0xf4,
                                                                    0x5e, 0xd5, 0x8b, 0x66, 0x34, 0x61, 0x3c, 0x00, 0x2c, 0x43, 0xa5, 0x3a, 0xf6, 0x37, 0xba, 0xb5, };

    MULTIPATH::MpManager                client;
    MULTIPATH::MpManager                server;

    if (!server.initialize(key_aes, key_mp, Port0, Port1, Port2))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!client.initialize(key_aes, key_mp, Port0, Port1, Port2, address_0, address_1, address_2))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize client\n", __FILE__, __LINE__, __FUNCTION__);
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

    if (server.receive(message_received_a, type_a))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.receive(message_received_b, type_b))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.receive(message_received_b, type_c))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.transmit(message_transmitted))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if ((Port0) && (!server.receive(message_received_a, type_a)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if ((Port1) && (!server.receive(message_received_b, type_b)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if ((Port2) && (!server.receive(message_received_c, type_c)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (Port0 && Port1)
    {
        if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_a, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_b, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_a, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_c, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_b, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_c, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }

        if (memcmp(&message_received_01, &message_transmitted, sizeof(BUFFER::BUFFER_T<packet_size>)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }
    }

    if (Port0 && Port2)
    {
        if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_a, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_b, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_a, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_c, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_b, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_c, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }

        if (memcmp(&message_received_02, &message_transmitted, sizeof(BUFFER::BUFFER_T<packet_size>)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }
    }

    if (Port1 && Port2)
    {
        if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_a, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_b, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_a, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_c, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_b, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_c, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }

        if (memcmp(&message_received_12, &message_transmitted, sizeof(BUFFER::BUFFER_T<packet_size>)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
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


bool server_transmits(uint16_t Port0, uint16_t Port1, uint16_t Port2)
{
    constexpr uint32_t                  packet_size             = 128u;

    bool                                ret_val                 = true;
    std::string                         address_0               = "127.0.0.1";
    std::string                         address_1               = "127.0.0.1";
    std::string                         address_2               = "127.0.0.1";
    AES::KEY256                         key_aes                 = { 0u, 0x5fd92f6f, 0x53853c01, 0x0bb2124a, 0x21af89e0 };
    AES::WORDS                          key_mp                  = {     0x8fc46159, 0xdd05af88, 0xda98f727, 0x60004b30 };
    MULTIPATH::TYPE_SINGLE              type_a                  = MULTIPATH::TYPE_SINGLE::EMPTY;
    MULTIPATH::TYPE_SINGLE              type_b                  = MULTIPATH::TYPE_SINGLE::EMPTY;
    MULTIPATH::TYPE_SINGLE              type_c                  = MULTIPATH::TYPE_SINGLE::EMPTY;
    BUFFER::BUFFER_T<packet_size>       message_received_a      {};
    BUFFER::BUFFER_T<packet_size>       message_received_b      {};
    BUFFER::BUFFER_T<packet_size>       message_received_c      {};
    BUFFER::BUFFER_T<packet_size>       message_received_01     {};
    BUFFER::BUFFER_T<packet_size>       message_received_02     {};
    BUFFER::BUFFER_T<packet_size>       message_received_12     {};

    BUFFER::BUFFER_T<packet_size>       message_transmitted     = { 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00,
                                                                    0x04, 0x9e, 0x1a, 0xe4, 0x1c, 0xda, 0x24, 0x6e, 0xce, 0x2d, 0xcf, 0xb5, 0x63, 0x6c, 0x4f, 0x79,
                                                                    0x14, 0x2f, 0x62, 0x2f, 0x0c, 0xcc, 0x37, 0x79, 0xbc, 0x67, 0x12, 0x7d, 0x95, 0x75, 0x7d, 0x99,
                                                                    0x13, 0x97, 0x7d, 0x2f, 0x71, 0xa1, 0x9d, 0x3f, 0xce, 0x6d, 0xf4, 0x31, 0xd9, 0x43, 0xab, 0xed,
                                                                    0x72, 0x0d, 0x1c, 0x7f, 0xd9, 0x54, 0xf8, 0x95, 0xbb, 0x0a, 0x12, 0x50, 0x7f, 0x8f, 0xe9, 0x92,
                                                                    0x26, 0x66, 0xc1, 0x97, 0x07, 0x5f, 0xd6, 0xd6, 0xcc, 0xca, 0x07, 0xa5, 0x0e, 0xb2, 0x92, 0x80,
                                                                    0xbf, 0xae, 0xff, 0x98, 0x02, 0xf7, 0x2d, 0xbe, 0x02, 0x3f, 0x0e, 0x81, 0xce, 0xf8, 0x14, 0xf4,
                                                                    0x5e, 0xd5, 0x8b, 0x66, 0x34, 0x61, 0x3c, 0x00, 0x2c, 0x43, 0xa5, 0x3a, 0xf6, 0x37, 0xba, 0xb5, };

    MULTIPATH::MpManager                client;
    MULTIPATH::MpManager                server;

    if (!server.initialize(key_aes, key_mp, Port0, Port1, Port2))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!client.initialize(key_aes, key_mp, Port0, Port1, Port2, address_0, address_1, address_2))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize client\n", __FILE__, __LINE__, __FUNCTION__);
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

    if (client.receive(message_received_a, type_a))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (client.receive(message_received_b, type_b))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (client.receive(message_received_c, type_c))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.transmit(message_transmitted))
    {
        fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if ((Port0) && (!client.receive(message_received_a, type_a)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if ((Port1) && (!client.receive(message_received_b, type_b)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if ((Port2) && (!client.receive(message_received_c, type_c)))
    {
        fprintf(stderr, "%s:%d:%s: Failed to receive\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (Port0 && Port1)
    {
        if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_a, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_b, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_a, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_c, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_b, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_1))
        {
            if (!MULTIPATH::decode_buffer(message_received_01, message_received_b, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_01))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }

        if (memcmp(&message_received_01, &message_transmitted, sizeof(BUFFER::BUFFER_T<packet_size>)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }
    }

    if (Port0 && Port2)
    {
        if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_a, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_b, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_a, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_c, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_b, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_0) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_02, message_received_c, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_02))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }

        if (memcmp(&message_received_02, &message_transmitted, sizeof(BUFFER::BUFFER_T<packet_size>)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }
    }

    if (Port1 && Port2)
    {
        if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_a, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_b, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_a == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_a, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_a == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_c, message_received_a, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_b == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_c == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_b, message_received_c, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else if ((type_c == MULTIPATH::TYPE_SINGLE::TYPE_1) && (type_b == MULTIPATH::TYPE_SINGLE::TYPE_2))
        {
            if (!MULTIPATH::decode_buffer(message_received_12, message_received_c, message_received_b, MULTIPATH::TYPE_DOUBLE::TYPE_12))
            {
                fprintf(stderr, "%s:%d:%s: Failed to decode message\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }

        if (memcmp(&message_received_12, &message_transmitted, sizeof(BUFFER::BUFFER_T<packet_size>)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to receive message\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
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


bool client_transmits_012()
{
    constexpr uint16_t port_0 = 20010u;
    constexpr uint16_t port_1 = 20011u;
    constexpr uint16_t port_2 = 20012u;

    return client_transmits(port_0, port_1, port_2);
}


bool client_transmits_01()
{
    constexpr uint16_t port_0 = 20020u;
    constexpr uint16_t port_1 = 20021u;
    constexpr uint16_t port_2 = 0u;

    return client_transmits(port_0, port_1, port_2);
}


bool client_transmits_02()
{
    constexpr uint16_t port_0 = 20030u;
    constexpr uint16_t port_1 = 0u;
    constexpr uint16_t port_2 = 20032u;

    return client_transmits(port_0, port_1, port_2);
}


bool client_transmits_12()
{
    constexpr uint16_t port_0 = 0u;
    constexpr uint16_t port_1 = 20041u;
    constexpr uint16_t port_2 = 20042u;

    return client_transmits(port_0, port_1, port_2);
}


bool server_transmits_012()
{
    constexpr uint16_t port_0 = 20050u;
    constexpr uint16_t port_1 = 20051u;
    constexpr uint16_t port_2 = 20052u;

    return server_transmits(port_0, port_1, port_2);
}


bool server_transmits_01()
{
    constexpr uint16_t port_0 = 20060u;
    constexpr uint16_t port_1 = 20061u;
    constexpr uint16_t port_2 = 0u;

    return server_transmits(port_0, port_1, port_2);
}


bool server_transmits_02()
{
    constexpr uint16_t port_0 = 20070u;
    constexpr uint16_t port_1 = 0u;
    constexpr uint16_t port_2 = 20072u;

    return server_transmits(port_0, port_1, port_2);
}


bool server_transmits_12()
{
    constexpr uint16_t port_0 = 0u;
    constexpr uint16_t port_1 = 20081u;
    constexpr uint16_t port_2 = 20082u;

    return server_transmits(port_0, port_1, port_2);
}


int main(int argc, char** argv)
{
    if (!client_transmits_012())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!client_transmits_01())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!client_transmits_02())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!client_transmits_12())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!server_transmits_012())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!server_transmits_01())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!server_transmits_02())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!server_transmits_12())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
