
#include <stdio.h>

#include "Base/Buffer.h"


namespace Crc
{
    namespace
    {
        template<uint32_t PacketSize>
        void compute(BUFFER::BUFFER_T<PacketSize>& Buffer, uint32_t CrcPolynomial)
        {
            const uint8_t p0 = static_cast<uint8_t>((CrcPolynomial & 0xfe000000) >> 25u) + 0x80;
            const uint8_t p1 = static_cast<uint8_t>((CrcPolynomial & 0x01fe0000) >> 17u);
            const uint8_t p2 = static_cast<uint8_t>((CrcPolynomial & 0x0001fe00) >>  9u);
            const uint8_t p3 = static_cast<uint8_t>((CrcPolynomial & 0x000001fe) >>  1u);
            const uint8_t p4 = static_cast<uint8_t>((CrcPolynomial & 0x00000001) <<  7u);

            for (uint32_t j = 0u; j < sizeof(Buffer) - sizeof(CrcPolynomial); j++)
            {
                uint8_t polynomial[] = { p0, p1, p2, p3, p4, 0u };

                for (uint32_t i = 0u; i < 8u; i++)
                {
                    if ((Buffer[j] >> (7u - i)) & 0x01)
                    {
                        for (uint32_t k = 0u; k < sizeof(polynomial); k++)
                        {
                            if (j + k >= sizeof(Buffer))
                            {
                                break;
                            }

                            Buffer[j + k] ^= polynomial[k];
                        }
                    }

                    polynomial[5] = (polynomial[5] >> 1) + ((polynomial[4] & 0x01) << 7u );
                    polynomial[4] = (polynomial[4] >> 1) + ((polynomial[3] & 0x01) << 7u );
                    polynomial[3] = (polynomial[3] >> 1) + ((polynomial[2] & 0x01) << 7u );
                    polynomial[2] = (polynomial[2] >> 1) + ((polynomial[1] & 0x01) << 7u );
                    polynomial[1] = (polynomial[1] >> 1) + ((polynomial[0] & 0x01) << 7u );
                    polynomial[0] = (polynomial[0] >> 1);
                }
            }
        }
    }


    template<uint32_t PacketSize>
    void calculate(BUFFER::BUFFER_T<PacketSize>& Buffer, uint32_t CrcPolynomial)
    {
        BUFFER::BUFFER_T<PacketSize> crc{};

        memcpy(&crc, &Buffer, sizeof(crc));

        compute(crc, CrcPolynomial);

        BUFFER::add(Buffer, Buffer, crc);
    }


    template<uint32_t PacketSize>
    bool verify(BUFFER::BUFFER_T<PacketSize>& Buffer, uint32_t CrcPolynomial)
    {
        BUFFER::BUFFER_T<PacketSize> crc{};

        memcpy(&crc, &Buffer, sizeof(crc));

        compute(crc, CrcPolynomial);

        if (!BUFFER::zero(crc))
        {
            fprintf(stderr, "%s:%d:%s: Invalid CRC\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        uint32_t cleaner = 0u;

        if (!BUFFER::and2(Buffer, cleaner, sizeof(Buffer) - sizeof(cleaner)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to execute AND operation\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }
}
