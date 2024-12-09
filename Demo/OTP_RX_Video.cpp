
#include <stdio.h>
#include <string>

#include "Base/Network.h"
#include "Base/Screen.h"
#include "Base/Time.h"
#include "Base/UtilsConfig.h"
#include "OneTimePad/OtpControllerServer.h"
#include "OneTimePad/OtpFrame.h"


int32_t main(int32_t argc, char** argv)
{
    constexpr uint32_t                                          packet_size         = 1024u;
    constexpr uint32_t                                          width               = 320u;
    constexpr uint32_t                                          height              = 240u;
    constexpr uint32_t                                          frame_rate          = 10u;
    constexpr uint32_t                                          frame_interval      = 1000u / frame_rate;
    constexpr uint64_t                                          latency             = 2000u;

    bool                                                        initial_buffer      = true;
    bool                                                        time_initial_set    = false;
    uint64_t                                                    time_initial        = 0u;
    uint64_t                                                    time_current        = 0u;
    uint8_t*                                                    received_data       = new uint8_t[width * height]{};
    int32_t                                                     ret_val             = 0;
    uint32_t                                                    frame_number        = 0u;
    uint32_t                                                    port                = 0u;
    uint32_t                                                    size                = 60u;
    uint32_t                                                    timeout             = 0u;
    std::string                                                 title               = "DLEncoder";
    std::string                                                 filename_key_aes;
    std::string                                                 filename_key_otp;
    AES::KEY256                                                 key_aes{};
    AES::WORDS                                                  key_otp{};
    ONETIMEPAD::OtpControllerServer<packet_size, width, height> controller;
    Screen::Screen                                              screen;

    if (!received_data)
    {
        fprintf(stderr, "%s:%d:%s: Failed to allocate memory\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (argc != 5)
    {
        fprintf(stderr, "%s:%d:%s: OTP_RX_Video.exe AES OTP PORT TIMEOUT\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    filename_key_aes    = argv[1];
    filename_key_otp    = argv[2];
    port                = std::stoul(argv[3]);
    timeout             = std::stoul(argv[4]);

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

    if (!screen.initialize( width,  height, title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to intialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!controller.initialize_server(key_aes, key_otp, port, size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize controller\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!controller.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    while (1)
    {
        bool status = false;

        if (!controller.communicate())
        {
            fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
            goto terminate;
        }

        if (!time_initial_set)
        {
            if (!Time::get_time(time_initial))
            {
                fprintf(stderr, "%s:%d:%s: Failed to get initial time\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = -1;
                goto terminate;
            }

            time_initial_set = true;
        }

        if (!Time::get_time(time_current))
        {
            fprintf(stderr, "%s:%d:%s: Failed to get initial time\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = -1;
            goto terminate;
        }

        if (time_current - time_initial >= latency)
        {
            if (!controller.get_frames().get(received_data, frame_number++))
            {
                fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }

            screen.display_image(received_data);

            time_initial += frame_interval;
        }
    }

terminate:
    screen.deinitialize();

    if (!controller.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize controller\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
    }

    if (received_data)
    {
        delete[] received_data;
    }

    return ret_val;
}
