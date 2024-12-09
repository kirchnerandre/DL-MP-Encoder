
#include "Base/Endianness.h"


namespace SHA512
{
    // https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
    // https://csrc.nist.gov/csrc/media/projects/cryptographic-standards-and-guidelines/documents/examples/sha512.pdf

    typedef uint64_t HASHES_T[8u];

    uint64_t sigma_0(uint64_t Value);
    uint64_t sigma_1(uint64_t Value);
    uint64_t sum_0  (uint64_t Value);
    uint64_t sum_1  (uint64_t Value);
    uint64_t ch     (uint64_t ValueX, uint64_t ValueY, uint64_t ValueZ);
    uint64_t maj    (uint64_t ValueX, uint64_t ValueY, uint64_t ValueZ);

    void calculate_internal(uint8_t* Buffer, HASHES_T& Hashes, uint32_t T);


    template<uint32_t PacketSize>
    void set_hash(SHA512_T<PacketSize>& Sha512NetworkByteOrder, uint32_t HashNumber, uint64_t& HashHostByteOrder)
    {
        Endianness::hton64(&Sha512NetworkByteOrder.Data[8u * HashNumber], HashHostByteOrder);
    }


    template<uint32_t PacketSize>
    uint64_t get_hash(SHA512_T<PacketSize>& Sha512NetworkByteOrder, uint32_t HashNumber)
    {
        return Endianness::ntoh64(&Sha512NetworkByteOrder.Data[8u * HashNumber]);
    }


    template<size_t Steps>
    inline uint64_t rotl(uint64_t Value)
    {
        constexpr size_t steps = Steps % 64u;

        if constexpr(steps == 0u)
        {
            return Value;
        }
        else
        {
            return (Value << steps) + (Value >> (64u - steps));
        }
    }


    template<size_t Steps>
    inline uint64_t rotr(uint64_t Value)
    {
        constexpr size_t steps = Steps % 64u;

        if constexpr(steps == 0u)
        {
            return Value;
        }
        else
        {
            return (Value >> steps) + (Value << (64u - steps));
        }
    }


    template<size_t Steps>
    inline uint64_t shr(uint64_t Value)
    {
        if constexpr(Steps == 0u)
        {
            return Value;
        }
        else if constexpr(Steps >= 64u)
        {
            return 0u;
        }
        else
        {
            return Value >> Steps;
        }
    }


    template<uint32_t PacketSize>
    void calculate(BUFFER::BUFFER_T<PacketSize>& Buffer, SHA512_T<PacketSize>& Sha512, bool Reset)
    {
        constexpr uint32_t  iterations  = 80u;

        constexpr uint64_t  hash_a      = 0x6a09e667f3bcc908;
        constexpr uint64_t  hash_b      = 0xbb67ae8584caa73b;
        constexpr uint64_t  hash_c      = 0x3c6ef372fe94f82b;
        constexpr uint64_t  hash_d      = 0xa54ff53a5f1d36f1;
        constexpr uint64_t  hash_e      = 0x510e527fade682d1;
        constexpr uint64_t  hash_f      = 0x9b05688c2b3e6c1f;
        constexpr uint64_t  hash_g      = 0x1f83d9abfb41bd6b;
        constexpr uint64_t  hash_h      = 0x5be0cd19137e2179;

        HASHES_T            hashes      { hash_a, hash_b, hash_c, hash_d, hash_e, hash_f, hash_g, hash_h };

        if (!Reset)
        {
            hashes[0u] = get_hash(Sha512, 0u);
            hashes[1u] = get_hash(Sha512, 1u);
            hashes[2u] = get_hash(Sha512, 2u);
            hashes[3u] = get_hash(Sha512, 3u);
            hashes[4u] = get_hash(Sha512, 4u);
            hashes[5u] = get_hash(Sha512, 5u);
            hashes[6u] = get_hash(Sha512, 6u);
            hashes[7u] = get_hash(Sha512, 7u);
        }

        uint8_t* buffer = reinterpret_cast<uint8_t*>(&Buffer);

        for (uint32_t i = 0u; i < PacketSize; i += SHA512_T<PacketSize>::DATA_SIZE)
        {
            for (uint32_t j = 0u; j < iterations; j++)
            {
                calculate_internal(&buffer[i], hashes, j);
            }
        }

        hashes[0u] += hash_a;
        hashes[1u] += hash_b;
        hashes[2u] += hash_c;
        hashes[3u] += hash_d;
        hashes[4u] += hash_e;
        hashes[5u] += hash_f;
        hashes[6u] += hash_g;
        hashes[7u] += hash_h;

        set_hash(Sha512, 0u, hashes[0u]);
        set_hash(Sha512, 1u, hashes[1u]);
        set_hash(Sha512, 2u, hashes[2u]);
        set_hash(Sha512, 3u, hashes[3u]);
        set_hash(Sha512, 4u, hashes[4u]);
        set_hash(Sha512, 5u, hashes[5u]);
        set_hash(Sha512, 6u, hashes[6u]);
        set_hash(Sha512, 7u, hashes[7u]);
    }
}
