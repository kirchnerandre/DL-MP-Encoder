
#include <stdio.h>
#include <string>

#include "Base/Network.h"
#include "Base/Screen.h"
#include "Base/Time.h"
#include "Base/UtilsConfig.h"
#include "Multipath/MpControllerServer.h"
#include "Multipath/MpFrame.h"


int32_t main(int32_t argc, char** argv)
{
    constexpr uint32_t                                          packet_size         = 1024u;
    constexpr uint32_t                                          width               = 320u;
    constexpr uint32_t                                          height              = 240u;
    constexpr uint32_t                                          frame_rate          = 5u;
    constexpr uint32_t                                          frame_interval      = 1000u / frame_rate;
    constexpr uint64_t                                          latency             = 2000u;

    bool                                                        initial_buffer      = true;
    bool                                                        time_initial_set    = false;
    uint64_t                                                    time_initial        = 0u;
    uint64_t                                                    time_current        = 0u;
    uint8_t*                                                    received_data       = new uint8_t[width * height]{};
    int32_t                                                     ret_val             = 0;
    uint32_t                                                    frame_number        = 0u;
    uint32_t                                                    port_0              = 0u;
    uint32_t                                                    port_1              = 0u;
    uint32_t                                                    port_2              = 0u;
    uint32_t                                                    timeout             = 0u;
    uint32_t                                                    size                = 60u;
    std::string                                                 title               = "MPEncoder";
    MULTIPATH::MpControllerServer<packet_size, width, height>   controller;
    Screen::Screen                                              screen;

    if (!received_data)
    {
        fprintf(stderr, "%s:%d:%s: Failed to allocate memory\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (argc != 5)
    {
        fprintf(stderr, "%s:%d:%s: MP_RX_Video.exe PORT_0 PORT_1 PORT_2 TIMEOUT\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    port_0              = std::stoul(argv[1]);
    port_1              = std::stoul(argv[2]);
    port_2              = std::stoul(argv[3]);
    timeout             = std::stoul(argv[4]);

    if (!screen.initialize(width,  height, title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to intialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!controller.initialize_server(port_0, port_1, port_2, size))
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
