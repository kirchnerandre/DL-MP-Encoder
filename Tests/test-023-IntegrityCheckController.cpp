
#include <stdio.h>
#include <string>

#include "IntegrityCheck/IntegrityCheckControllerClient.h"
#include "IntegrityCheck/IntegrityCheckControllerServer.h"
#include "IntegrityCheck/IntegrityCheckFrame.h"


bool verify_frame(std::string& FrameFilename, uint8_t* FrameData)
{
    bool        ret_val         = true;
    uint8_t*    frame_data      = nullptr;
    uint32_t    frame_width     = 0u;
    uint32_t    frame_height    = 0u;
    uint32_t    frame_maximum   = 0u;

    if (!UtilsPgm::read(&frame_data, frame_width, frame_height, frame_maximum, nullptr, FrameFilename))
    {
        fprintf(stderr, "%s:%d:%s: Failed to read file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(frame_data, FrameData, frame_width * frame_height))
    {
        fprintf(stderr, "%s:%d:%s: Invalid frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (frame_data)
    {
        delete[] frame_data;
    }

    return ret_val;
}


bool test_connection()
{
    constexpr uint32_t                          packet_size         = 128u;
    constexpr uint32_t                          image_width         = 320u;
    constexpr uint32_t                          image_height        = 240u;
    constexpr uint32_t                          hash_columns        = 3;
    constexpr uint32_t                          hash_rows           = 2;
    constexpr uint32_t                          size                = 1u;

    bool                                        ret_val             = true;
    uint32_t                                    port                = 30000u;
    uint32_t                                    timeout             = 10u;
    std::string                                 address             = "127.0.0.1";

    INTEGRITYCHECK::IntegrityCheckControllerClient<packet_size, image_width, image_height, hash_columns, hash_rows>  client; 
    INTEGRITYCHECK::IntegrityCheckControllerServer<packet_size, image_width, image_height, hash_columns, hash_rows>  server;

    if (!server.initialize_server(port, size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize_client(port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (server.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly succeed to connect\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:

    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    return ret_val;
}


bool test_single_communication()
{
    constexpr uint32_t                          packet_size         = 1024u;
    constexpr uint32_t                          image_width         = 320u;
    constexpr uint32_t                          image_height        = 240u;
    constexpr uint32_t                          hash_columns        = 7;
    constexpr uint32_t                          hash_rows           = 11;

    bool                                        ret_val             = true;
    uint8_t                                     received_data       [image_width * image_height]{};;
    uint32_t                                    transmitted_width   = 0u;
    uint32_t                                    transmitted_height  = 0u;
    uint32_t                                    transmitted_maximum = 0u;
    uint32_t                                    port                = 30100u;
    uint32_t                                    timeout             = 10u;
    uint32_t                                    frames_size         = 1u;
    uint32_t                                    frame_number        = 0u;
    std::string                                 frame_filename      = "./Data/Input/Frames-0320x0240/frame-0320x0240-0005.pgm";
    std::string                                 address             = "127.0.0.1";
    Statistics::STATISTICS_T                    statistics_client   {};
    Statistics::STATISTICS_T                    statistics_server   {};

    INTEGRITYCHECK::IntegrityCheckControllerClient<packet_size, image_width, image_height, hash_columns, hash_rows>  client; 
    INTEGRITYCHECK::IntegrityCheckControllerServer<packet_size, image_width, image_height, hash_columns, hash_rows>  server;

    if (!server.initialize_server(port, frames_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize_client(port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename, statistics_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    while (server.communicate(statistics_server));

    if (!server.get_frames().get(received_data, frame_number))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!verify_frame(frame_filename, received_data))
    {
        fprintf(stderr, "%s:%d:%s: Invalid frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    return ret_val;
}


bool test_many_communication()
{
    constexpr uint32_t                          packet_size         = 1024u;
    constexpr uint32_t                          image_width         = 320u;
    constexpr uint32_t                          image_height        = 240u;
    constexpr uint32_t                          hash_columns        = 7u;
    constexpr uint32_t                          hash_rows           = 11u;

    bool                                        ret_val             = true;
    uint8_t                                     received_data       [image_width * image_height]{};
    uint32_t                                    transmitted_width   = 0u;
    uint32_t                                    transmitted_height  = 0u;
    uint32_t                                    transmitted_maximum = 0u;
    uint32_t                                    port                = 30200u;
    uint32_t                                    timeout             = 10u;
    uint32_t                                    frames_size         = 5u;
    uint32_t                                    frame_number        = 0u;
    std::string                                 frame_filename_0    = "./Data/Input/Frames-0320x0240/frame-0320x0240-0000.pgm";
    std::string                                 frame_filename_1    = "./Data/Input/Frames-0320x0240/frame-0320x0240-0001.pgm";
    std::string                                 frame_filename_2    = "./Data/Input/Frames-0320x0240/frame-0320x0240-0002.pgm";
    std::string                                 frame_filename_3    = "./Data/Input/Frames-0320x0240/frame-0320x0240-0003.pgm";
    std::string                                 frame_filename_4    = "./Data/Input/Frames-0320x0240/frame-0320x0240-0004.pgm";
    std::string                                 address             = "127.0.0.1";
    Statistics::STATISTICS_T                    statistics_client   {};
    Statistics::STATISTICS_T                    statistics_server   {};

    INTEGRITYCHECK::IntegrityCheckControllerClient<packet_size, image_width, image_height, hash_columns, hash_rows>  client; 
    INTEGRITYCHECK::IntegrityCheckControllerServer<packet_size, image_width, image_height, hash_columns, hash_rows>  server;

    if (!server.initialize_server(port, frames_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize_client(port, address))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect client\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.konnect(timeout))
    {
        fprintf(stderr, "%s:%d:%s: Failed to connect server\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_0, statistics_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_1, statistics_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_2, statistics_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_3, statistics_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_4, statistics_client))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    while (server.communicate(statistics_server));

    if (!server.get_frames().get(received_data, frame_number++))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!verify_frame(frame_filename_0, received_data))
    {
        fprintf(stderr, "%s:%d:%s: Invalid frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.get_frames().get(received_data, frame_number++))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!verify_frame(frame_filename_1, received_data))
    {
        fprintf(stderr, "%s:%d:%s: Invalid frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.get_frames().get(received_data, frame_number++))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!verify_frame(frame_filename_2, received_data))
    {
        fprintf(stderr, "%s:%d:%s: Invalid frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.get_frames().get(received_data, frame_number++))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!verify_frame(frame_filename_3, received_data))
    {
        fprintf(stderr, "%s:%d:%s: Invalid frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!server.get_frames().get(received_data, frame_number++))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!verify_frame(frame_filename_4, received_data))
    {
        fprintf(stderr, "%s:%d:%s: Invalid frame\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (!client.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    if (!server.deinitialize())
    {
        fprintf(stderr, "%s:%d:%s: Failed to deinitialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
    }

    return ret_val;
}


int main(int argc, char** argv)
{
    if (!test_connection())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_single_communication())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_many_communication())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
