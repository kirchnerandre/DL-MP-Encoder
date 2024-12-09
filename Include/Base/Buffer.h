
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdint.h>

namespace BUFFER
{
    template<uint32_t PacketSize>
    struct BUFFER_T
    {
        static constexpr uint32_t   DATA_SIZE       = 128u;

        static_assert(PacketSize % DATA_SIZE == 0u, "Packet size must be a multiple of 128 bytes\n");

        static constexpr uint32_t   LENGTH_HEADER   = 4u;
        static constexpr uint32_t   LENGTH_FRAME    = 4u;
        static constexpr uint32_t   LENGTH_OFFSET   = 4u;
        static constexpr uint32_t   LENGTH_RESERVED = 4u;
        static constexpr uint32_t   LENGTH_DATA     = PacketSize - LENGTH_HEADER - LENGTH_FRAME - LENGTH_OFFSET - LENGTH_RESERVED;

        typedef uint8_t             HEADER_T        [LENGTH_HEADER];
        typedef uint8_t             FRAME_T         [LENGTH_FRAME];
        typedef uint8_t             OFFSET_T        [LENGTH_OFFSET];
        typedef uint8_t             RESERVED_T      [LENGTH_RESERVED];
        typedef uint8_t             DATA_T          [LENGTH_DATA];

        HEADER_T                    Header;
        FRAME_T                     Frame;
        OFFSET_T                    Offset;
        RESERVED_T                  Reserved;
        DATA_T                      Data;

        uint8_t &operator[](uint32_t Offset);
    };

    /**
     * Prints the contents of the byte stream of the BUFFER_T structure to the screen for debugging.
     * @param Buffer BUFFER_T structure.
    */
    template<uint32_t PacketSize>
    void print(BUFFER_T<PacketSize>& Buffer);

    /**
     * Verifies the contents of the byte stream of the BUFFER_T structure are all zeros.
     * @param Buffer BUFFER_T structure.
     * @return True if the contents of the byte stream of BUFFER_T structure are all zeros, and false otherwise.
    */
    template<uint32_t PacketSize>
    bool zero(BUFFER_T<PacketSize>& Buffer);

    /**
     * Adds the contents of the byte stream of two BUFFER_T structures. Carry is ignored if it happens at the most
     * significant byte.
     * @param Output BUFFER_T structure containing the result of the add operation.
     * @param InputA BUFFER_T structure input.
     * @param InputB BUFFER_T structure input.
    */
    template<uint32_t PacketSize>
    void add(BUFFER_T<PacketSize>& Output, BUFFER_T<PacketSize>& InputA, BUFFER_T<PacketSize>& InputB);

    /**
     * Executes the bitwise AND operation between parameters Buffer and Value starting at the Offset byte, and
     * writes the result to the Buffer parameter.
     * @param Buffer BUFFER_T structure.
     * @param Value  Parameter of integer type.
     * @param Offset Offset in bytes.
     * @return True if Value will fit inside the byte stream of the BUFFER_T structure, and false otherwise.
    */
    template <uint32_t PacketSize, typename T>
    bool and2(BUFFER_T<PacketSize>& Buffer, T Value, uint32_t Offset);
}

#include "Base/Buffer.inl"

#endif // _BUFFER_H_
