
#include <stdio.h>
#include <string>

#include "Base/Network.h"
#include "Base/Screen.h"
#include "Base/Time.h"
#include "Base/UtilsConfig.h"
#include "IntegrityCheck/IntegrityCheckControllerServer.h"


int32_t main(int32_t argc, char** argv)
{
    constexpr uint32_t                                          packet_size         = 1024u;
    constexpr uint32_t                                          image_width         = 320u;
    constexpr uint32_t                                          image_height        = 240u;
    constexpr uint32_t                                          hash_columns        = 7u;
    constexpr uint32_t                                          hash_rows           = 11u;
    constexpr uint32_t                                          frame_rate          = 5u;
    constexpr uint32_t                                          frame_interval      = 1000u / frame_rate;
    constexpr uint64_t                                          latency             = 5000u;

    bool                                                        initial_buffer      = true;
    bool                                                        time_initial_set    = false;
    uint64_t                                                    time_initial        = 0u;
    uint64_t                                                    time_current        = 0u;
    uint8_t*                                                    received_data       = new uint8_t[image_width * image_height]{};
    int32_t                                                     ret_val             = 0;
    uint32_t                                                    frame_number        = 0u;
    uint32_t                                                    port                = 0u;
    uint32_t                                                    size                = 60u;
    uint32_t                                                    timeout             = 0u;
    std::string                                                 title               = "IntegrityCheckEncoder";
    INTEGRITYCHECK::IntegrityCheckControllerServer<packet_size,
                                                   image_width,
                                                   image_height,
                                                   hash_columns,
                                                   hash_rows>   controller;
    Screen::Screen                                              screen;
    Statistics::STATISTICS_T                                    statistics          {};

    if (!received_data)
    {
        fprintf(stderr, "%s:%d:%s: Failed to allocate memory\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (argc != 3)
    {
        fprintf(stderr, "%s:%d:%s: IC_RX_Video.exe PORT TIMEOUT\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    port                = std::stoul(argv[1]);
    timeout             = std::stoul(argv[2]);

    if (!screen.initialize(image_width, image_height, title))
    {
        fprintf(stderr, "%s:%d:%s: Failed to intialize screen\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!controller.initialize_server(port, size))
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

        if (!controller.communicate(statistics))
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

    Statistics::summarize(statistics);

    return ret_val;
}
