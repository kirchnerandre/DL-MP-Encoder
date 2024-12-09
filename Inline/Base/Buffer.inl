
#include <stdio.h>
#include <string.h>

#include "Base/Buffer.h"


namespace BUFFER
{
    template<uint32_t PacketSize>
    uint8_t& BUFFER_T<PacketSize>::operator[](uint32_t Offset)
    {
        uint8_t* buffer = reinterpret_cast<uint8_t*>(this);

        return buffer[Offset];
    }


    template<uint32_t PacketSize>
    void print(BUFFER_T<PacketSize>& Buffer)
    {
        for (size_t i = 0u; i < sizeof(Buffer); i++)
        {
            if (!i)
            {
                fprintf(stderr, "0x%02x", Buffer[i]);
            }
            else if (i % 16u == 0u)
            {
                fprintf(stderr, "\n0x%02x", Buffer[i]);
            }
            else
            {
                fprintf(stderr, " 0x%02x", Buffer[i]);
            }
        }

        fprintf(stderr, "\n");
    }


    template<uint32_t PacketSize>
    bool zero(BUFFER_T<PacketSize>& Buffer)
    {
        constexpr BUFFER_T<PacketSize> zero{};

        return memcmp(&Buffer, &zero, sizeof(Buffer)) == 0;
    }


    template<uint32_t PacketSize>
    void add(BUFFER_T<PacketSize>& Output, BUFFER_T<PacketSize>& InputA, BUFFER_T<PacketSize>& InputB)
    {
        uint8_t*    output  = reinterpret_cast<uint8_t*>(&Output);
        uint32_t    i       = sizeof(Output) - 1u;
        uint8_t     flag    = 0x00u;

        while (1)
        {
            uint32_t value = InputA[i] + InputB[i] + flag;

            if (value & 0x00000100)
            {
                flag = 1u;
            }
            else
            {
                flag = 0u;
            }

            output[i--] = static_cast<uint8_t>(value & 0x000000ff);

            if (!i)
            {
                break;
            }
        }
    }


    template <uint32_t PacketSize, typename T>
    bool and2(BUFFER_T<PacketSize>& Buffer, T Value, uint32_t Offset)
    {
        if (Offset + sizeof(Value) - 1u > sizeof(Buffer))
        {
            fprintf(stderr, "%s:%d:%s: Invalid Parameter\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        constexpr uint32_t  integer = 0x00000001;
        constexpr uint8_t   pointer = (const uint8_t&)(integer);

        uint8_t*            value   = reinterpret_cast<uint8_t*>(&Value);

        if constexpr(pointer)
        {
            for (uint32_t i = 0; i < sizeof(Value); i++)
            {
                Buffer[Offset + i] &= value[sizeof(Value) - 1 - i];
            }
        }
        else
        {
            for (uint32_t i = 0; i < sizeof(Value); i++)
            {
                Buffer[Offset + i] &= value[i];
            }
        }

        return true;
    }
}
