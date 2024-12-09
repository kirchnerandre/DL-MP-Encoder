
#include <algorithm>
#include <filesystem>
#include <stdio.h>
#include <string>

#include "Base/Network.h"
#include "Base/Time.h"
#include "Base/UtilsConfig.h"
#include "IntegrityCheck/IntegrityCheckControllerClient.h"


typedef std::vector<std::string>    FILES;
typedef FILES::iterator             IFILE;


bool get_files(FILES& Files, std::string& Folder)
{
    for (const auto& file: std::filesystem::directory_iterator(Folder))
    {
        Files.push_back(file.path().string());
    }

    std::sort(Files.begin(), Files.end());

    return true;
}


int32_t main(int32_t argc, char** argv)
{
    constexpr uint32_t                                          packet_size         = 1024u;
    constexpr uint32_t                                          image_width         = 320u;
    constexpr uint32_t                                          image_height        = 240u;
    constexpr uint32_t                                          hash_columns        = 7u;
    constexpr uint32_t                                          hash_rows           = 11u;
    constexpr uint32_t                                          frame_rate          = 5u;
    constexpr uint32_t                                          frame_interval      = 1000u / frame_rate;
    constexpr uint32_t                                          time_sleep          = frame_interval / 3u;

    int32_t                                                     ret_val             = 0;
    uint64_t                                                    time_initial        = 0u;
    uint64_t                                                    time_current        = 0u;
    uint32_t                                                    port                = 0u;
    uint32_t                                                    timeout             = 0u;
    std::string                                                 folder;
    std::string                                                 address;
    INTEGRITYCHECK::IntegrityCheckControllerClient<packet_size,
                                                   image_width,
                                                   image_height,
                                                   hash_columns,
                                                   hash_rows>   controller;
    FILES                                                       files;
    IFILE                                                       i_file              = files.end();
    Statistics::STATISTICS_T                                    statistics          {};

    if (argc != 5)
    {
        fprintf(stderr, "%s:%d:%s: IC_TX_Video.exe FOLDER ADDRESS PORT TIMEOUT\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    folder              = argv[1];
    port                = std::stoul(argv[2]);
    address             = argv[3];
    timeout             = std::stoul(argv[4]);

    if (!get_files(files, folder))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get files\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    if (!controller.initialize_client(port, address))
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

    i_file = files.begin();

    if (!Time::get_time(time_initial))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get initial time\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
        goto terminate;
    }

    while (i_file != files.end())
    {
        bool status = false;

        if (!Time::get_time(time_current))
        {
            fprintf(stderr, "%s:%d:%s: Failed to get initial time\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = -1;
            goto terminate;
        }

        if (time_current - time_initial >= frame_interval)
        {
            if (!controller.communicate(*i_file, statistics))
            {
                fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = -1;
                goto terminate;
            }

            time_initial += frame_interval;

            i_file++;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(time_sleep));
        }
    }

terminate:
    if (!controller.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize controller\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = -1;
    }

    Statistics::summarize(statistics);

    return ret_val;
}
