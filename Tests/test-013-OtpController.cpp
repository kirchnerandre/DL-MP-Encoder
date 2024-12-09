
#include <stdio.h>
#include <string>

#include "OneTimePad/OtpControllerClient.h"
#include "OneTimePad/OtpControllerServer.h"
#include "OneTimePad/OtpFrame.h"


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
    constexpr uint32_t                          width               = 320u;
    constexpr uint32_t                          height              = 240u;
    constexpr uint32_t                          size                = 1u;

    bool                                        ret_val             = true;
    uint32_t                                    port                = 30000u;
    uint32_t                                    timeout             = 10u;
    std::string                                 address             = "127.0.0.1";
    AES::KEY256                                 initial_key_aes   { 0u,
                                                                    0x0012d464, 0x000123c7, 0x6c75d464, 0x65203c73,
                                                                    0x00001200, 0x23696e63, 0x65aa0012, 0x88803c73 };
    AES::WORDS                                  initial_key_otp   { 0x75d00124, 0x64520300, 0x12c73093, 0x6c750012 };


    ONETIMEPAD::OtpControllerClient<packet_size,
                                    width,
                                    height>     client;
                                    
    ONETIMEPAD::OtpControllerServer<packet_size,
                                    width,
                                    height>     server;

    if (!server.initialize_server(initial_key_aes, initial_key_otp, port, size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize_client(initial_key_aes, initial_key_otp, port, address))
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
    constexpr uint32_t                          packet_size         = 128u;
    constexpr uint32_t                          width               = 320u;
    constexpr uint32_t                          height              = 240u;

    bool                                        ret_val             = true;
    uint8_t                                     received_data       [width * height]{};;
    uint32_t                                    transmitted_width   = 0u;
    uint32_t                                    transmitted_height  = 0u;
    uint32_t                                    transmitted_maximum = 0u;
    uint32_t                                    port                = 30100u;
    uint32_t                                    timeout             = 10u;
    uint32_t                                    frames_size         = 1u;
    uint32_t                                    frame_number        = 0u;
    std::string                                 frame_filename      = "./Data/Input/Frames-0320x0240/frame-0320x0240-0005.pgm";
    std::string                                 address             = "127.0.0.1";
    AES::KEY256                                 initial_key_aes     { 0u,
                                                                       0x0012d464, 0x000123c7, 0x6c75d464, 0x65203c73,
                                                                       0x00001200, 0x23696e63, 0x65aa0012, 0x88803c73 };
    AES::WORDS                                  initial_key_otp     { 0x75d00124, 0x64520300, 0x12c73093, 0x6c750012 };

    ONETIMEPAD::OtpControllerClient<packet_size,
                                    width,
                                    height>     client;
                                    
    ONETIMEPAD::OtpControllerServer<packet_size,
                                    width,
                                    height>     server;

    if (!server.initialize_server(initial_key_aes, initial_key_otp, port, frames_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize_client(initial_key_aes, initial_key_otp, port, address))
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

    if (!client.communicate(frame_filename))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    while (server.communicate());

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
    constexpr uint32_t                          packet_size         = 128u;
    constexpr uint32_t                          width               = 360u;
    constexpr uint32_t                          height              = 320u;

    bool                                        ret_val             = true;
    uint8_t                                     received_data       [width * height]{};
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
    AES::KEY256                                 initial_key_aes     { 0u,
                                                                      0x0012d464, 0x000123c7, 0x6c75d464, 0x65203c73,
                                                                      0x00001200, 0x23696e63, 0x65aa0012, 0x88803c73 };
    AES::WORDS                                  initial_key_otp     { 0x75d00124, 0x64520300, 0x12c73093, 0x6c750012 };

    ONETIMEPAD::OtpControllerClient<packet_size,
                                    width,
                                    height>     client;
                                    
    ONETIMEPAD::OtpControllerServer<packet_size,
                                    width,
                                    height>     server;

    if (!server.initialize_server(initial_key_aes, initial_key_otp, port, frames_size))
    {
        fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.initialize_client(initial_key_aes, initial_key_otp, port, address))
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

    if (!client.communicate(frame_filename_0))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_1))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_2))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_3))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!client.communicate(frame_filename_4))
    {
        fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    while (server.communicate());

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
