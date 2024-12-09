
#include <stdint.h>
#include <stdio.h>

#include "Base/Aes.h"


namespace AES
{
    namespace
    {
            constexpr uint8_t box_s[]           = { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                                                    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                                                    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                                                    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                                                    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                                                    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                                                    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                                                    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                                                    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                                                    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                                                    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                                                    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                                                    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                                                    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                                                    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                                                    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

        constexpr uint8_t table_multiply_by_2[] = { 0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
                                                    0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,
                                                    0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e,
                                                    0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e,
                                                    0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e,
                                                    0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe,
                                                    0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde,
                                                    0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe,
                                                    0x1b, 0x19, 0x1f, 0x1d, 0x13, 0x11, 0x17, 0x15, 0x0b, 0x09, 0x0f, 0x0d, 0x03, 0x01, 0x07, 0x05,
                                                    0x3b, 0x39, 0x3f, 0x3d, 0x33, 0x31, 0x37, 0x35, 0x2b, 0x29, 0x2f, 0x2d, 0x23, 0x21, 0x27, 0x25,
                                                    0x5b, 0x59, 0x5f, 0x5d, 0x53, 0x51, 0x57, 0x55, 0x4b, 0x49, 0x4f, 0x4d, 0x43, 0x41, 0x47, 0x45,
                                                    0x7b, 0x79, 0x7f, 0x7d, 0x73, 0x71, 0x77, 0x75, 0x6b, 0x69, 0x6f, 0x6d, 0x63, 0x61, 0x67, 0x65,
                                                    0x9b, 0x99, 0x9f, 0x9d, 0x93, 0x91, 0x97, 0x95, 0x8b, 0x89, 0x8f, 0x8d, 0x83, 0x81, 0x87, 0x85,
                                                    0xbb, 0xb9, 0xbf, 0xbd, 0xb3, 0xb1, 0xb7, 0xb5, 0xab, 0xa9, 0xaf, 0xad, 0xa3, 0xa1, 0xa7, 0xa5,
                                                    0xdb, 0xd9, 0xdf, 0xdd, 0xd3, 0xd1, 0xd7, 0xd5, 0xcb, 0xc9, 0xcf, 0xcd, 0xc3, 0xc1, 0xc7, 0xc5,
                                                    0xfb, 0xf9, 0xff, 0xfd, 0xf3, 0xf1, 0xf7, 0xf5, 0xeb, 0xe9, 0xef, 0xed, 0xe3, 0xe1, 0xe7, 0xe5 };

        constexpr uint8_t table_multiply_by_3[] = { 0x00, 0x03, 0x06, 0x05, 0x0c, 0x0f, 0x0a, 0x09, 0x18, 0x1b, 0x1e, 0x1d, 0x14, 0x17, 0x12, 0x11,
                                                    0x30, 0x33, 0x36, 0x35, 0x3c, 0x3f, 0x3a, 0x39, 0x28, 0x2b, 0x2e, 0x2d, 0x24, 0x27, 0x22, 0x21,
                                                    0x60, 0x63, 0x66, 0x65, 0x6c, 0x6f, 0x6a, 0x69, 0x78, 0x7b, 0x7e, 0x7d, 0x74, 0x77, 0x72, 0x71,
                                                    0x50, 0x53, 0x56, 0x55, 0x5c, 0x5f, 0x5a, 0x59, 0x48, 0x4b, 0x4e, 0x4d, 0x44, 0x47, 0x42, 0x41,
                                                    0xc0, 0xc3, 0xc6, 0xc5, 0xcc, 0xcf, 0xca, 0xc9, 0xd8, 0xdb, 0xde, 0xdd, 0xd4, 0xd7, 0xd2, 0xd1,
                                                    0xf0, 0xf3, 0xf6, 0xf5, 0xfc, 0xff, 0xfa, 0xf9, 0xe8, 0xeb, 0xee, 0xed, 0xe4, 0xe7, 0xe2, 0xe1,
                                                    0xa0, 0xa3, 0xa6, 0xa5, 0xac, 0xaf, 0xaa, 0xa9, 0xb8, 0xbb, 0xbe, 0xbd, 0xb4, 0xb7, 0xb2, 0xb1,
                                                    0x90, 0x93, 0x96, 0x95, 0x9c, 0x9f, 0x9a, 0x99, 0x88, 0x8b, 0x8e, 0x8d, 0x84, 0x87, 0x82, 0x81,
                                                    0x9b, 0x98, 0x9d, 0x9e, 0x97, 0x94, 0x91, 0x92, 0x83, 0x80, 0x85, 0x86, 0x8f, 0x8c, 0x89, 0x8a,
                                                    0xab, 0xa8, 0xad, 0xae, 0xa7, 0xa4, 0xa1, 0xa2, 0xb3, 0xb0, 0xb5, 0xb6, 0xbf, 0xbc, 0xb9, 0xba,
                                                    0xfb, 0xf8, 0xfd, 0xfe, 0xf7, 0xf4, 0xf1, 0xf2, 0xe3, 0xe0, 0xe5, 0xe6, 0xef, 0xec, 0xe9, 0xea,
                                                    0xcb, 0xc8, 0xcd, 0xce, 0xc7, 0xc4, 0xc1, 0xc2, 0xd3, 0xd0, 0xd5, 0xd6, 0xdf, 0xdc, 0xd9, 0xda,
                                                    0x5b, 0x58, 0x5d, 0x5e, 0x57, 0x54, 0x51, 0x52, 0x43, 0x40, 0x45, 0x46, 0x4f, 0x4c, 0x49, 0x4a,
                                                    0x6b, 0x68, 0x6d, 0x6e, 0x67, 0x64, 0x61, 0x62, 0x73, 0x70, 0x75, 0x76, 0x7f, 0x7c, 0x79, 0x7a,
                                                    0x3b, 0x38, 0x3d, 0x3e, 0x37, 0x34, 0x31, 0x32, 0x23, 0x20, 0x25, 0x26, 0x2f, 0x2c, 0x29, 0x2a,
                                                    0x0b, 0x08, 0x0d, 0x0e, 0x07, 0x04, 0x01, 0x02, 0x13, 0x10, 0x15, 0x16, 0x1f, 0x1c, 0x19, 0x1a };


#if defined(ENCODER_PLATFORM_LINUX)
        inline uint8_t get_s(uint8_t Value)
        {
            return box_s[Value];
        }


        inline uint8_t multiply_by_1(uint8_t Value)
        {
            return Value;
        }


        inline uint8_t multiply_by_2(uint8_t Value)
        {
            return table_multiply_by_2[Value];
        }


        inline uint8_t multiply_by_3(uint8_t Value)
        {
            return table_multiply_by_3[Value];
        }
#elif defined(ENCODER_PLATFORM_WINDOWS)
        __forceinline uint8_t get_s(uint8_t Value)
        {
            return box_s[Value];
        }


        __forceinline uint8_t multiply_by_1(uint8_t Value)
        {
            return Value;
        }


        __forceinline uint8_t multiply_by_2(uint8_t Value)
        {
            return table_multiply_by_2[Value];
        }


        __forceinline uint8_t multiply_by_3(uint8_t Value)
        {
            return table_multiply_by_3[Value];
        }
#endif


        bool schedule_words(uint32_t Round, uint32_t KeyWord0, uint32_t KeyWord1, uint32_t KeyWord2, uint32_t KeyWord3, WORDS& Words)
        {
            constexpr uint32_t max_round = 14u;

            if (Round == 0u)
            {
                Words.Word0 ^= KeyWord0;
                Words.Word1 ^= KeyWord1;
                Words.Word2 ^= KeyWord2;
                Words.Word3 ^= KeyWord3;
            }
            else
            {
                uint8_t a00 = get_s((Words.Word0 & 0xff000000) >> 24u);
                uint8_t a01 = get_s((Words.Word1 & 0xff000000) >> 24u);
                uint8_t a02 = get_s((Words.Word2 & 0xff000000) >> 24u);
                uint8_t a03 = get_s((Words.Word3 & 0xff000000) >> 24u);

                uint8_t a10 = get_s((Words.Word0 & 0x00ff0000) >> 16u);
                uint8_t a11 = get_s((Words.Word1 & 0x00ff0000) >> 16u);
                uint8_t a12 = get_s((Words.Word2 & 0x00ff0000) >> 16u);
                uint8_t a13 = get_s((Words.Word3 & 0x00ff0000) >> 16u);

                uint8_t a20 = get_s((Words.Word0 & 0x0000ff00) >>  8u);
                uint8_t a21 = get_s((Words.Word1 & 0x0000ff00) >>  8u);
                uint8_t a22 = get_s((Words.Word2 & 0x0000ff00) >>  8u);
                uint8_t a23 = get_s((Words.Word3 & 0x0000ff00) >>  8u);

                uint8_t a30 = get_s((Words.Word0 & 0x000000ff) >>  0u);
                uint8_t a31 = get_s((Words.Word1 & 0x000000ff) >>  0u);
                uint8_t a32 = get_s((Words.Word2 & 0x000000ff) >>  0u);
                uint8_t a33 = get_s((Words.Word3 & 0x000000ff) >>  0u);

                uint8_t b00 = a00;
                uint8_t b01 = a01;
                uint8_t b02 = a02;
                uint8_t b03 = a03;
                uint8_t b10 = a11;
                uint8_t b11 = a12;
                uint8_t b12 = a13;
                uint8_t b13 = a10;
                uint8_t b20 = a22;
                uint8_t b21 = a23;
                uint8_t b22 = a20;
                uint8_t b23 = a21;
                uint8_t b30 = a33;
                uint8_t b31 = a30;
                uint8_t b32 = a31;
                uint8_t b33 = a32;

                uint8_t c00 = a00;
                uint8_t c01 = a01;
                uint8_t c02 = a02;
                uint8_t c03 = a03;
                uint8_t c10 = a11;
                uint8_t c11 = a12;
                uint8_t c12 = a13;
                uint8_t c13 = a10;
                uint8_t c20 = a22;
                uint8_t c21 = a23;
                uint8_t c22 = a20;
                uint8_t c23 = a21;
                uint8_t c30 = a33;
                uint8_t c31 = a30;
                uint8_t c32 = a31;
                uint8_t c33 = a32;

                if (Round != max_round)
                {
                    c00 = multiply_by_2(b00) ^ multiply_by_3(b10) ^ multiply_by_1(b20) ^ multiply_by_1(b30);
                    c10 = multiply_by_1(b00) ^ multiply_by_2(b10) ^ multiply_by_3(b20) ^ multiply_by_1(b30);
                    c20 = multiply_by_1(b00) ^ multiply_by_1(b10) ^ multiply_by_2(b20) ^ multiply_by_3(b30);
                    c30 = multiply_by_3(b00) ^ multiply_by_1(b10) ^ multiply_by_1(b20) ^ multiply_by_2(b30);

                    c01 = multiply_by_2(b01) ^ multiply_by_3(b11) ^ multiply_by_1(b21) ^ multiply_by_1(b31);
                    c11 = multiply_by_1(b01) ^ multiply_by_2(b11) ^ multiply_by_3(b21) ^ multiply_by_1(b31);
                    c21 = multiply_by_1(b01) ^ multiply_by_1(b11) ^ multiply_by_2(b21) ^ multiply_by_3(b31);
                    c31 = multiply_by_3(b01) ^ multiply_by_1(b11) ^ multiply_by_1(b21) ^ multiply_by_2(b31);

                    c02 = multiply_by_2(b02) ^ multiply_by_3(b12) ^ multiply_by_1(b22) ^ multiply_by_1(b32);
                    c12 = multiply_by_1(b02) ^ multiply_by_2(b12) ^ multiply_by_3(b22) ^ multiply_by_1(b32);
                    c22 = multiply_by_1(b02) ^ multiply_by_1(b12) ^ multiply_by_2(b22) ^ multiply_by_3(b32);
                    c32 = multiply_by_3(b02) ^ multiply_by_1(b12) ^ multiply_by_1(b22) ^ multiply_by_2(b32);

                    c03 = multiply_by_2(b03) ^ multiply_by_3(b13) ^ multiply_by_1(b23) ^ multiply_by_1(b33);
                    c13 = multiply_by_1(b03) ^ multiply_by_2(b13) ^ multiply_by_3(b23) ^ multiply_by_1(b33);
                    c23 = multiply_by_1(b03) ^ multiply_by_1(b13) ^ multiply_by_2(b23) ^ multiply_by_3(b33);
                    c33 = multiply_by_3(b03) ^ multiply_by_1(b13) ^ multiply_by_1(b23) ^ multiply_by_2(b33);
                }

                Words.Word0 = (c00 << 24u) + (c10 << 16u) + (c20 << 8u) + c30;
                Words.Word1 = (c01 << 24u) + (c11 << 16u) + (c21 << 8u) + c31;
                Words.Word2 = (c02 << 24u) + (c12 << 16u) + (c22 << 8u) + c32;
                Words.Word3 = (c03 << 24u) + (c13 << 16u) + (c23 << 8u) + c33;

                Words.Word0 ^= KeyWord0;
                Words.Word1 ^= KeyWord1;
                Words.Word2 ^= KeyWord2;
                Words.Word3 ^= KeyWord3;
            }

            return true;
        }
    }

    bool schedule_key(KEY256& Key)
    {
        constexpr uint32_t r_con[]  = { 0x01000000,
                                        0x02000000,
                                        0x04000000,
                                        0x08000000,
                                        0x10000000,
                                        0x20000000,
                                        0x40000000,
                                        0x80000000,
                                        0x1b000000,
                                        0x36000000 };

        uint32_t max_round = 14u;

        if (Key.Round >= max_round)
        {
            fprintf(stderr, "%s:%d:%s: Invalid round\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        uint8_t a0 = (Key.Word7 & 0x00ff0000) >> 16u;
        uint8_t a1 = (Key.Word7 & 0x0000ff00) >>  8u;
        uint8_t a2 = (Key.Word7 & 0x000000ff) >>  0u;
        uint8_t a3 = (Key.Word7 & 0xff000000) >> 24u;

        uint8_t r0 = (r_con[(Key.Round + 1u) / 2u] & 0xff000000) >> 24u;
        uint8_t r1 = (r_con[(Key.Round + 1u) / 2u] & 0x00ff0000) >> 16u;
        uint8_t r2 = (r_con[(Key.Round + 1u) / 2u] & 0x0000ff00) >>  8u;
        uint8_t r3 = (r_con[(Key.Round + 1u) / 2u] & 0x000000ff) >>  0u;

        a0 = get_s(a0);
        a1 = get_s(a1);
        a2 = get_s(a2);
        a3 = get_s(a3);

        a0 ^= r0;
        a1 ^= r1;
        a2 ^= r2;
        a3 ^= r3;

        Key.Word0 ^= (a0 << 24u) + (a1 << 16u) + (a2 << 8u) + (a3 << 0u);
        Key.Word1 ^= Key.Word0;
        Key.Word2 ^= Key.Word1;
        Key.Word3 ^= Key.Word2;

        uint8_t b0 = (Key.Word3 & 0xff000000) >> 24u;
        uint8_t b1 = (Key.Word3 & 0x00ff0000) >> 16u;
        uint8_t b2 = (Key.Word3 & 0x0000ff00) >>  8u;
        uint8_t b3 = (Key.Word3 & 0x000000ff) >>  0u;

        b0 = get_s(b0);
        b1 = get_s(b1);
        b2 = get_s(b2);
        b3 = get_s(b3);

        Key.Word4 ^= (b0 << 24u) + (b1 << 16u) + (b2 << 8u) + (b3 << 0u);
        Key.Word5 ^= Key.Word4;
        Key.Word6 ^= Key.Word5;
        Key.Word7 ^= Key.Word6;

        Key.Round += 2u;

        return true;
    }


    bool schedule_words(KEY256& Key, WORDS& Words)
    {
        constexpr uint32_t max_round = 14u;

        if (Key.Round % 2u)
        {
            fprintf(stderr, "%s:%d:%s: Invalid round\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (Key.Round + 0u <= max_round)
        {
            if (!schedule_words(Key.Round + 0u, Key.Word0, Key.Word1, Key.Word2, Key.Word3, Words))
            {
                fprintf(stderr, "%s:%d:%s: Failed to schedule worlds\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        if (Key.Round + 1u <= max_round)
        {
            if (!schedule_words(Key.Round + 1u, Key.Word4, Key.Word5, Key.Word6, Key.Word7, Words))
            {
                fprintf(stderr, "%s:%d:%s: Failed to schedule worlds\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        return true;
    }


    bool encode(KEY256& Key, WORDS& Words)
    {
        constexpr uint32_t max_round = 14u;

        if (!schedule_words(Key, Words))
        {
            fprintf(stderr, "%s:%d:%s: Failed to schedule word\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        while (1)
        {
            if (!schedule_key(Key))
            {
                fprintf(stderr, "%s:%d:%s: Failed to schedule key\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!schedule_words(Key, Words))
            {
                fprintf(stderr, "%s:%d:%s: Failed to schedule word\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (Key.Round >= max_round)
            {
                break;
            }
        }

        return true;
    }
}
