
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>


namespace ONETIMEPAD
{
    template<uint32_t PacketSize>
    bool encode(BUFFER::BUFFER_T<PacketSize>& Buffer, BUFFER::BUFFER_T<PacketSize>& Key)
    {
        for (uint32_t i = 0u; i < sizeof(Buffer); i++)
        {
            Buffer[i] = (Buffer[i] + Key[i]) & 0xff;
        }

        return true;
    }


    template<uint32_t PacketSize>
    bool encode(BUFFER::BUFFER_T<PacketSize>& Buffer, BUFFER::BUFFER_T<PacketSize>& Key, uint32_t Seed)
    {
        if (Seed)
        {
            srand(Seed);
        }

        for (uint32_t i = 0; i < (sizeof(Key) / sizeof(uint32_t)); i++)
        {
            uint32_t random_number = static_cast<uint32_t>(rand());

            Key[4 * i + 0u] = (random_number & 0x000000ff) >>  0u;
            Key[4 * i + 1u] = (random_number & 0x0000ff00) >>  8u;
            Key[4 * i + 2u] = (random_number & 0x00ff0000) >> 16u;
            Key[4 * i + 3u] = (random_number & 0xff000000) >> 24u;
        }

        if (!encode(Buffer, Key))
        {
            fprintf(stderr, "%s:%d:%s: Failed to encode\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    template<uint32_t PacketSize>
    bool decode(BUFFER::BUFFER_T<PacketSize>& Buffer, BUFFER::BUFFER_T<PacketSize>& Key)
    {
        for (uint32_t i = 0u; i < sizeof(Buffer); i++)
        {
            if (Buffer[i] >= Key[i])
            {
                Buffer[i] = Buffer[i] - Key[i];
            }
            else
            {
                Buffer[i] = 0x100 + Buffer[i] - Key[i];
            }
        }

        return true;
    }
}
