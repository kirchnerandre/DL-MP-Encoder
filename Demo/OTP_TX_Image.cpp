
#include <stdio.h>
#include <thread>

#include "Base/UtilsConfig.h"
#include "OneTimePad/OtpManager.h"


int main(int argc, char** argv)
{
    constexpr uint32_t      packet_size         = 128u;
    constexpr uint32_t      time_sleep          = 1000u;

    int                     ret_val             = 0;
    FILE*                   file                = nullptr;
    uint32_t                timeout_connect     = 0u;
    uint32_t                port                = 0u;
    uint32_t                size                = 0u;
    std::string             address;
    std::string             filename_key_aes;
    std::string             filename_key_otp;
    std::string             filename_source;
    ONETIMEPAD::OtpManager  client;
    AES::KEY256             key_aes{};
    AES::WORDS              key_otp{};

    if (argc != 7)
    {
        fprintf(stderr, "%s:%d:%s: OTP_TX_Image.exe AES_KEY_FILENAME OTP_KEY_FILENAME SOURCE_FILENAME PORT ADDRESS TIMEOUT\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    filename_key_aes    = argv[1];
    filename_key_otp    = argv[2];
    filename_source     = argv[3];
    port                = std::stoul(argv[4]);
    address             = argv[5];
    timeout_connect     = std::stoul(argv[6]);

    if (!UtilsConfig::read(key_aes, filename_key_aes))
    {
        fprintf(stderr, "%s:%d:%s: Failed to read AES key\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!UtilsConfig::read(key_otp, filename_key_otp))
    {
        fprintf(stderr, "%s:%d:%s: Failed to read OTP key\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!client.initialize(key_aes, key_otp, port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    while (1)
    {
        if (client.konnect())
        {
            fprintf(stderr, "%s:%d:%s: Succeeded connecting\n", __FILE__, __LINE__, __FUNCTION__);
            break;
        }

        if (--timeout_connect == 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to connect\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = -1;
            goto terminate;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(time_sleep));
    }

    file = fopen(filename_source.c_str(), "rb");

    if (!file)
    {
        fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    while (1)
    {
        BUFFER::BUFFER_T<packet_size>   buffer{};
        uint32_t                        size = 0u;

        size = fread(&buffer, 1u, sizeof(buffer), file);

        if (size == 0u)
        {
            break;
        }
        else
        {
            if (!client.transmit(buffer))
            {
                fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = -1;
                goto terminate;
            }
        }
    }

terminate:
    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
    }

    if (file)
    {
        fclose(file);
    }

    return ret_val;
}
