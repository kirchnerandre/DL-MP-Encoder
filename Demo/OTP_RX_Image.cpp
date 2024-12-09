
#include <stdio.h>
#include <thread>

#include "Base/UtilsConfig.h"
#include "OneTimePad/OtpManager.h"


int main(int argc, char** argv)
{
    constexpr uint32_t              packet_size         = 128u;
    constexpr uint32_t              time_sleep          = 1000u;

    int                             ret_val             = 0;
    FILE*                           file                = nullptr;
    uint32_t                        timeout_connect     = 0u;
    uint32_t                        port                = 0u;
    std::string                     filename_key_aes;
    std::string                     filename_key_otp;
    std::string                     filename_dest;
    ONETIMEPAD::OtpManager          server;
    AES::KEY256                     key_aes{};
    AES::WORDS                      key_otp{};
    BUFFER::BUFFER_T<packet_size>   data{};

    if (argc != 6)
    {
        fprintf(stderr, "%s:%d:%s: OTP_RX_Image.exe AES_KEY_FILENAME OTP_KEY_FILENAME DEST_FILENAME PORT TIMEOUT\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    filename_key_aes    = argv[1];
    filename_key_otp    = argv[2];
    filename_dest       = argv[3];
    port                = std::stoul(argv[4]);
    timeout_connect     = std::stoul(argv[5]);

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

    if (!server.initialize(key_aes, key_otp, port))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    while (1)
    {
        if (server.konnect())
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

    file = fopen(filename_dest.c_str(), "wb");

    if (!file)
    {
        fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    while (1)
    {
        BUFFER::BUFFER_T<packet_size> buffer{};

        if (!server.receive(buffer))
        {
            fprintf(stderr, "%s:%d:%s: Failed or finished receiving\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = -1;
            goto terminate;
        }

        if (fwrite(&buffer, 1u, sizeof(BUFFER::BUFFER_T<packet_size>), file) != sizeof(BUFFER::BUFFER_T<packet_size>))
        {
            fprintf(stderr, "%s:%d:%s: Failed to write\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = -1;
            goto terminate;
        }
    }

terminate:
    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
    }

    if (file)
    {
        fclose(file);
    }

    return ret_val;
}
