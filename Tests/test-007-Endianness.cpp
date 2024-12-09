
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Base/Endianness.h"


template<typename T>
bool test_hton(T Input, uint8_t* Output)
{
    uint8_t output[sizeof(T)]{};

    if (sizeof(T) == 1u)
    {
        Endianness::hton8(output, Input);

        if (memcmp(output, Output, sizeof(T)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to network byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else if (sizeof(T) == 2u)
    {
        Endianness::hton16(output, Input);

        if (memcmp(output, Output, sizeof(T)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to network byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else if (sizeof(T) == 4u)
    {
        Endianness::hton32(output, Input);

        if (memcmp(output, Output, sizeof(T)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to network byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else if (sizeof(T) == 8u)
    {
        Endianness::hton64(output, Input);

        if (memcmp(output, Output, sizeof(T)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to network byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else
    {
        fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


template<typename T>
bool test_ntoh(uint8_t* Input, T Output)
{
    if (sizeof(T) == 1u)
    {
        if (Endianness::ntoh8(Input) != Output)
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to host byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else if (sizeof(T) == 2u)
    {
        if (Endianness::ntoh16(Input) != Output)
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to host byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else if (sizeof(T) == 4u)
    {
        if (Endianness::ntoh32(Input) != Output)
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to host byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else if (sizeof(T) == 8u)
    {
        if (Endianness::ntoh64(Input) != Output)
        {
            fprintf(stderr, "%s:%d:%s: Failed to convert to host byte order\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }
    else
    {
        fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


int main(int argc, char** argv)
{
    uint8_t  host_8  = 0x01;
    uint16_t host_16 = 0x0102;
    uint32_t host_32 = 0x01020304;
    uint64_t host_64 = 0x0102030405060708;

    uint8_t network_08[]{ 0x01 };
    uint8_t network_16[]{ 0x01, 0x02 };
    uint8_t network_32[]{ 0x01, 0x02, 0x03, 0x04 };
    uint8_t network_64[]{ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    if (!test_hton(host_8, network_08))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_hton(host_16, network_16))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_hton(host_32, network_32))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_hton(host_64, network_64))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_ntoh(network_08, host_8))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_ntoh(network_16, host_16))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_ntoh(network_32, host_32))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_ntoh(network_64, host_64))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
