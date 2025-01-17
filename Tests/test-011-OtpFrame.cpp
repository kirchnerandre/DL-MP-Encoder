
#include <stdio.h>
#include <string>

#include "Base/Buffer.h"
#include "Base/Endianness.h"
#include "OneTimePad/OtpFrame.h"


bool test_frame()
{
    constexpr uint32_t                  buffer_sise         = 128u;
    constexpr uint32_t                  width               = 16u;
    constexpr uint32_t                  height              = 14u;

    constexpr uint8_t                   expected_frame[]      { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x02, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x04, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x05, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x06, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,

                                                                0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x02, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x03, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x04, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x05, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x06, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb };

    BUFFER::BUFFER_T<buffer_sise>       buffer_a              { 0x00, 0x00, 0x00, 0x00,
                                                                0x00, 0x00, 0x00, 0x00,
                                                                0x00, 0x00, 0x00, 0x00,
                                                                0x00, 0x00, 0x00, 0x00,
                                                                0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x02, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x04, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x05, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x06, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,  };

    BUFFER::BUFFER_T<buffer_sise>       buffer_b              { 0x00, 0x00, 0x00, 0x00,
                                                                0x00, 0x00, 0x00, 0x00,
                                                                0x00, 0x00, 0x00, 0x70,
                                                                0x00, 0x00, 0x00, 0x00,
                                                                0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x02, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x03, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x04, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x05, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
                                                                0x06, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,};

    BUFFER::BUFFER_T<buffer_sise>       buffer_c              { 0x00, 0x00, 0x00, 0x00,
                                                                0x00, 0x00, 0x00, 0x00,
                                                                0x00, 0x00, 0x00, 0xE0,
                                                                0x00, 0x00, 0x00, 0x00,
                                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x02, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x04, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x05, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                                                                0x06, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, };

    uint8_t                             actual_frame[width * height]{};
    ONETIMEPAD::OtpFrame<buffer_sise,
                         width,
                         height>        frame;

    if (!frame.set(buffer_a))
    {
        fprintf(stderr, "%s:%d:%s: Failed to set\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (!frame.set(buffer_b))
    {

        fprintf(stderr, "%s:%d:%s: Failed to set\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (frame.set(buffer_c))
    {
        fprintf(stderr, "%s:%d:%s: Incorrectly set\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (!frame.get(actual_frame, 0u))
    {
        fprintf(stderr, "%s:%d:%s: Failed to get\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(actual_frame, expected_frame, sizeof(expected_frame)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect frame\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


int main(int argc, char** argv)
{
    if (!test_frame())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
