
#include <stdio.h>
#include <string>
#include <string.h>

#include "Base/UtilsPgm.h"


void get_header_size(uint32_t& HeaderSize, uint8_t* DataInput)
{
    constexpr uint8_t   line_feed   = 0x0a;
    constexpr uint8_t   space       = 0x20;
    constexpr uint32_t  values      = 4u;

    uint32_t            value       = 0u;

    HeaderSize = 0u;

    while (1)
    {
        if ((DataInput[HeaderSize] == line_feed) || (DataInput[HeaderSize] == space))
        {
            value++;
        }

        HeaderSize++;

        if (value >= values)
        {
            break;
        }
    }
}


bool test()
{
    constexpr uint32_t  expected_width      = 512u;
    constexpr uint32_t  expected_height     = 512u;
    constexpr uint32_t  expected_maximum    = 255u;
    std::string         expected_type       = "P5";
    std::string         filename            = "./Data/Input/barbara.pgm";

    bool                ret_val             = true;
    uint8_t*            file_data           = nullptr;
    uint8_t*            actual_data         = nullptr;
    uint32_t            actual_width        = 0u;
    uint32_t            actual_height       = 0u;
    uint32_t            actual_maximum      = 0u;
    uint32_t            header_size         = 0u;
    uint32_t            length_unsigned     = 0u;
    int32_t             length_signed       = 0;
    std::string         actual_type;

    FILE* file = fopen(filename.c_str(), "rb");

    if (!file)
    {
        fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (fseek(file, 0L, SEEK_END))
    {
        fprintf(stderr, "%s:%d:%s: Failed to seek end\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    length_signed = ftell(file);

    if (length_signed < 0)
    {
        fprintf(stderr, "%s:%d:%s: Failed to query size\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (fseek(file, 0, SEEK_SET))
    {
        fprintf(stderr, "%s:%d:%s: Failed to seek begin\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    length_unsigned = static_cast<uint32_t>(length_signed);

    file_data = new uint8_t[length_unsigned]{};

    if (!file_data)
    {
        fprintf(stderr, "%s:%d:%s: Failed to allocate memory\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (fread(file_data, 1u, length_unsigned, file) != length_unsigned)
    {
        fprintf(stderr, "%s:%d:%s: Failed to read file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!UtilsPgm::read(nullptr, actual_width, actual_height, actual_maximum, file_data))
    {
        fprintf(stderr, "%s:%d:%s: Failed to read header\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (actual_width != expected_width)
    {
        fprintf(stderr, "%s:%d:%s: Invalid width\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (actual_height != expected_height)
    {
        fprintf(stderr, "%s:%d:%s: Invalid height\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (actual_maximum != expected_maximum)
    {
        fprintf(stderr, "%s:%d:%s: Invalid maximum\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    get_header_size(header_size, file_data);

    if (length_unsigned != header_size + actual_width * actual_height)
    {
        fprintf(stderr, "%s:%d:%s: Invalid data length\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    actual_data = new uint8_t[actual_width * actual_height]{};

    if (!actual_data)
    {
        fprintf(stderr, "%s:%d:%s: Failed to allocate memory\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (!UtilsPgm::read(actual_data, actual_width, actual_height, actual_maximum, file_data))
    {
        fprintf(stderr, "%s:%d:%s: Failed to read header\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    if (memcmp(actual_data, &file_data[header_size], actual_width * actual_height))
    {
        fprintf(stderr, "%s:%d:%s: Invalid data\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

terminate:
    if (actual_data)
    {
        delete[] actual_data;
    }

    if (file_data)
    {
        delete[] file_data;
    }

    if (file)
    {
        fclose(file);
    }

    return ret_val;
}


int main(int argc, char** argv)
{
    if (!test())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
