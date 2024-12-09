
#include <stdint.h>
#include <string.h>

#include "Base/Endianness.h"


namespace Endianness
{

    namespace
    {
        enum class ByteOrder
        {
            LITTLE,
            BIG,
        };


        constexpr ByteOrder byte_order()
        {
            constexpr uint32_t  integer = 0x00000001;
            constexpr uint8_t   pointer = (const uint8_t&)(integer);

            if constexpr (pointer)
            {
                return ByteOrder::LITTLE;
            }
            else
            {
                return ByteOrder::BIG;
            }
        }


        template<typename T>
        T adjust(T Value)
        {
            if constexpr (byte_order() == ByteOrder::LITTLE)
            {
                T value = 0u;

                uint8_t* input  = reinterpret_cast<uint8_t*>(&Value);
                uint8_t* output = reinterpret_cast<uint8_t*>(&value);

                for (uint32_t i = 0u; i < sizeof(T); i++)
                {
                    output[i] = input[sizeof(T) - i - 1u];
                }

                return value;
            }
            else
            {
                return Value;
            }
        }
    }


    void hton8(uint8_t* Output, uint8_t Input)
    {
        *Output = Input;
    }


    void hton16(uint8_t* Output, uint16_t Input)
    {
        uint16_t input = adjust(Input);

        memcpy(Output, &input, sizeof(Input));
    }


    void hton32(uint8_t* Output, uint32_t Input)
    {
        uint32_t input = adjust(Input);

        memcpy(Output, &input, sizeof(Input));
    }


    void hton64(uint8_t* Output, uint64_t Input)
    {
        uint64_t input = adjust(Input);

        memcpy(Output, &input, sizeof(Input));
    }


    uint8_t ntoh8(uint8_t* Value)
    {
        return *Value;
    }


    uint16_t ntoh16(uint8_t* Value)
    {
        uint16_t value = 0u;

        memcpy(&value, Value, sizeof(value));

        return adjust(value);
    }


    uint32_t ntoh32(uint8_t* Value)
    {
        uint32_t value = 0u;

        memcpy(&value, Value, sizeof(value));

        return adjust(value);
    }


    uint64_t ntoh64(uint8_t* Value)
    {
        uint64_t value = 0u;

        memcpy(&value, Value, sizeof(value));

        return adjust(value);
    }

}
