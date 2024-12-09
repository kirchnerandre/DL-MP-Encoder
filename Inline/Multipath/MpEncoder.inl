
#include <string.h>

#include "Base/Endianness.h"


namespace MULTIPATH
{
    namespace
    {
        template<typename T>
        void build(uint8_t* Output, uint8_t* Input, size_t& OffsetCurrent, size_t OffsetMaximum)
        {
            T* output = reinterpret_cast<T*>(Output);
            T* input  = reinterpret_cast<T*>(Input );

            while (1)
            {
                if (OffsetCurrent + sizeof(T) > OffsetMaximum)
                {
                    break;
                }

                *output++ ^= *input++;

                OffsetCurrent += sizeof(T);
            }
        }


        void build_0(uint8_t* DataFrameOutput0,
                     uint8_t* DataFrameInput,
                     uint8_t* DataFrameKey,
                     size_t   DataFrameSize)
        {
            memcpy(DataFrameOutput0, DataFrameKey, DataFrameSize);

            size_t i = DataFrameSize / 2u;

            build<uint64_t>(&DataFrameOutput0[i], &DataFrameInput[i], i, DataFrameSize);
            build<uint32_t>(&DataFrameOutput0[i], &DataFrameInput[i], i, DataFrameSize);
            build<uint16_t>(&DataFrameOutput0[i], &DataFrameInput[i], i, DataFrameSize);
            build<uint8_t >(&DataFrameOutput0[i], &DataFrameInput[i], i, DataFrameSize);
        }


        void build_1(uint8_t* DataFrameOutput1,
                     uint8_t* DataFrameInput,
                     uint8_t* DataFrameKey,
                     size_t   DataFrameSize)
        {
            memcpy(DataFrameOutput1, DataFrameKey, DataFrameSize);

            size_t i = 0u;

            build<uint64_t>(&DataFrameOutput1[i], &DataFrameInput[i], i, DataFrameSize / 2u);
            build<uint32_t>(&DataFrameOutput1[i], &DataFrameInput[i], i, DataFrameSize / 2u);
            build<uint16_t>(&DataFrameOutput1[i], &DataFrameInput[i], i, DataFrameSize / 2u);
            build<uint8_t >(&DataFrameOutput1[i], &DataFrameInput[i], i, DataFrameSize / 2u);
        }


        void build_2(uint8_t* DataFrameOutput2,
                     uint8_t* DataFrameInput,
                     uint8_t* DataFrameKey,
                     size_t   DataFrameSize)
        {
            memcpy(DataFrameOutput2, DataFrameInput, DataFrameSize);

            size_t i = 0u;

            build<uint64_t>(&DataFrameOutput2[i], &DataFrameKey[i + DataFrameSize / 2u], i, DataFrameSize / 2u);
            build<uint32_t>(&DataFrameOutput2[i], &DataFrameKey[i + DataFrameSize / 2u], i, DataFrameSize / 2u);
            build<uint16_t>(&DataFrameOutput2[i], &DataFrameKey[i + DataFrameSize / 2u], i, DataFrameSize / 2u);
            build<uint8_t >(&DataFrameOutput2[i], &DataFrameKey[i + DataFrameSize / 2u], i, DataFrameSize / 2u);

            build<uint64_t>(&DataFrameOutput2[i], &DataFrameKey[i - DataFrameSize / 2u], i, DataFrameSize);
            build<uint32_t>(&DataFrameOutput2[i], &DataFrameKey[i - DataFrameSize / 2u], i, DataFrameSize);
            build<uint16_t>(&DataFrameOutput2[i], &DataFrameKey[i - DataFrameSize / 2u], i, DataFrameSize);
            build<uint8_t >(&DataFrameOutput2[i], &DataFrameKey[i - DataFrameSize / 2u], i, DataFrameSize);
        }


        void decode_01(uint8_t* DataFrameOutput,
                       uint8_t* DataFrameInputA,
                       uint8_t* DataFrameInputB,
                       size_t   DataFrameSize)
        {
            for (size_t i = 0u; i < DataFrameSize; i++)
            {
                DataFrameOutput[i] = DataFrameInputA[i] ^ DataFrameInputB[i];
            }
        }


        void decode_02(uint8_t* DataFrameOutput,
                       uint8_t* DataFrameInputA,
                       uint8_t* DataFrameInputB,
                       size_t   DataFrameSize)
        {
            for (size_t i = 0u; i < DataFrameSize / 2u; i++)
            {
                DataFrameOutput[i + DataFrameSize / 2u] = DataFrameInputA[i] ^ DataFrameInputB[i + DataFrameSize / 2u];
                DataFrameOutput[i]                      = DataFrameInputA[i] ^ DataFrameInputB[i + DataFrameSize / 2u]
                                                        ^ DataFrameInputB[i] ^ DataFrameInputA[i + DataFrameSize / 2u];
            }
        }


        void decode_03(uint8_t* DataFrameOutput,
                       uint8_t* DataFrameInputA,
                       uint8_t* DataFrameInputB,
                       size_t   DataFrameSize)
        {
            for (size_t i = 0u; i < DataFrameSize / 2u; i++)
            {
                DataFrameOutput[i]                      = DataFrameInputB[i] ^ DataFrameInputA[i + DataFrameSize / 2u];
                DataFrameOutput[i + DataFrameSize / 2u] = DataFrameInputB[i] ^ DataFrameInputA[i + DataFrameSize / 2u]
                                                        ^ DataFrameInputA[i] ^ DataFrameInputB[i + DataFrameSize / 2u];
            }
        }
    }


    template<uint32_t PacketSize>
    bool encode_buffer(BUFFER::BUFFER_T<PacketSize>& BufferOutput0,
                       BUFFER::BUFFER_T<PacketSize>& BufferOutput1,
                       BUFFER::BUFFER_T<PacketSize>& BufferOutput2,
                       BUFFER::BUFFER_T<PacketSize>& BufferInput,
                       BUFFER::BUFFER_T<PacketSize>& Key)
    {
        uint32_t frame_number = Endianness::ntoh32(BufferInput.Frame);
        uint32_t frame_offset = Endianness::ntoh32(BufferInput.Offset);

        build_0(BufferOutput0.Data, BufferInput.Data, Key.Data, sizeof(BufferInput.Data));
        build_1(BufferOutput1.Data, BufferInput.Data, Key.Data, sizeof(BufferInput.Data));
        build_2(BufferOutput2.Data, BufferInput.Data, Key.Data, sizeof(BufferInput.Data));

        Endianness::hton32(BufferOutput0.Frame, frame_number);
        Endianness::hton32(BufferOutput1.Frame, frame_number);
        Endianness::hton32(BufferOutput2.Frame, frame_number);

        Endianness::hton32(BufferOutput0.Offset, frame_offset);
        Endianness::hton32(BufferOutput1.Offset, frame_offset);
        Endianness::hton32(BufferOutput2.Offset, frame_offset);

        return true;
    }


    template<uint32_t PacketSize>
    bool decode_buffer(BUFFER::BUFFER_T<PacketSize>& BufferOutput,
                       BUFFER::BUFFER_T<PacketSize>& BufferInputA,
                       BUFFER::BUFFER_T<PacketSize>& BufferInputB,
                       TYPE_DOUBLE                   Type)
    {
        if (Type == TYPE_DOUBLE::TYPE_01)
        {
            decode_01(BufferOutput.Data, BufferInputA.Data, BufferInputB.Data, sizeof(BufferOutput.Data));
        }
        else if (Type == TYPE_DOUBLE::TYPE_02)
        {
            decode_02(BufferOutput.Data, BufferInputA.Data, BufferInputB.Data, sizeof(BufferOutput.Data));
        }
        else if (Type == TYPE_DOUBLE::TYPE_12)
        {
            decode_03(BufferOutput.Data, BufferInputA.Data, BufferInputB.Data, sizeof(BufferOutput.Data));
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }
}
