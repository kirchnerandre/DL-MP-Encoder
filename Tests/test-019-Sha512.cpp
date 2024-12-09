
#include <stdio.h>

#include "Base/Sha512.h"


template<uint32_t PackatSize>
void print_hash(SHA512::SHA512_T<PackatSize>& Sha512)
{
    printf("0x");

    for (uint32_t i = 0u; i < SHA512::SHA512_T<PackatSize>::LENGTH_DATA; i++)
    {
        printf("%02x", Sha512.Data[i]);
    }

    printf("\n");
}


bool verify_hash_1(SHA512::HASHES_T& HashesA, const SHA512::HASHES_T& HashesB)
{
    for (uint32_t i = 0u; i < 8u; i++)
    {
        if (HashesA[i] != HashesB[i])
        {
            fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }

    return true;
}


template<uint32_t PackatSize>
bool verify_hash_2(SHA512::SHA512_T<PackatSize>& HashA, const SHA512::HASHES_T& HashesB)
{
    SHA512::HASHES_T hashes_a{};

    hashes_a[0u] = SHA512::get_hash(HashA, 0u);
    hashes_a[1u] = SHA512::get_hash(HashA, 1u);
    hashes_a[2u] = SHA512::get_hash(HashA, 2u);
    hashes_a[3u] = SHA512::get_hash(HashA, 3u);
    hashes_a[4u] = SHA512::get_hash(HashA, 4u);
    hashes_a[5u] = SHA512::get_hash(HashA, 5u);
    hashes_a[6u] = SHA512::get_hash(HashA, 6u);
    hashes_a[7u] = SHA512::get_hash(HashA, 7u);

    return verify_hash_1(hashes_a, HashesB);
}


bool test_rotl()
{
    uint64_t value = 0x0123456789abcdef;

    if (SHA512::rotl<0u>(value) != 0x0123456789abcdef)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<1u>(value) != 0x02468acf13579bde)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<2u>(value) != 0x048d159e26af37bc)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<3u>(value) != 0x091a2b3c4d5e6f78)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<4u>(value) != 0x123456789abcdef0)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<5u>(value) != 0x2468acf13579bde0)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<6u>(value) != 0x48d159e26af37bc0)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<7u>(value) != 0x91a2b3c4d5e6f780)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<8u>(value) != 0x23456789abcdef01)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<16u>(value) != 0x456789abcdef0123)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<24u>(value) != 0x6789abcdef012345)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<32u>(value) != 0x89abcdef01234567)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<40u>(value) != 0xabcdef0123456789)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<48u>(value) != 0xcdef0123456789ab)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<56u>(value) != 0xef0123456789abcd)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotl<64u>(value) != 0x0123456789abcdef)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_rotr()
{
    uint64_t value = 0x0123456789abcdef;

    if (SHA512::rotr<0u>(value) != 0x0123456789abcdef)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<1u>(value) != 0x8091a2b3c4d5e6f7)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<2u>(value) != 0xc048d159e26af37b)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<3u>(value) != 0xe02468acf13579bd)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<4u>(value) != 0xf0123456789abcde)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<5u>(value) != 0x78091a2b3c4d5e6f)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<6u>(value) != 0xbc048d159e26af37)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<7u>(value) != 0xde02468acf13579b)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<8u>(value) != 0xef0123456789abcd)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<16u>(value) != 0xcdef0123456789ab)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<24u>(value) != 0xabcdef0123456789)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<32u>(value) != 0x89abcdef01234567)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<40u>(value) != 0x6789abcdef012345)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<48u>(value) != 0x456789abcdef0123)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<56u>(value) != 0x23456789abcdef01)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::rotr<64u>(value) != 0x0123456789abcdef)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_shr()
{
    uint64_t value = 0x0123456789abcdef;

    if (SHA512::shr<0u>(value) != 0x0123456789abcdef)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<1u>(value) != 0x0091a2b3c4d5e6f7)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<2u>(value) != 0x0048d159e26af37b)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<3u>(value) != 0x002468acf13579bd)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<4u>(value) != 0x00123456789abcde)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<5u>(value) != 0x00091a2b3c4d5e6f)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<6u>(value) != 0x00048d159e26af37)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<7u>(value) != 0x0002468acf13579b)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<8u>(value) != 0x000123456789abcd)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<16u>(value) != 0x00000123456789ab)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<24u>(value) != 0x0000000123456789)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<32u>(value) != 0x0000000001234567)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<40u>(value) != 0x0000000000012345)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<48u>(value) != 0x0000000000000123)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<56u>(value) != 0x0000000000000001)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (SHA512::shr<64u>(value) != 0x0000000000000000)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_sigma_0()
{
    uint64_t value = 0x0123456789abcdef;

    if (SHA512::sigma_0(value) != 0x6f92c77c6c4f1aa1)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_sigma_1()
{
    uint64_t value = 0x0123456789abcdef;

    if (SHA512::sigma_1(value) != 0x70a3460dbbd4317a)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_sum_0()
{
    uint64_t value = 0x0123456789abcdef;

    if (SHA512::sum_0(value) != 0xb7c57a100c7ec1ab)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_sum_1()
{
    uint64_t value = 0x0123456789abcdef;

    if (SHA512::sum_1(value) != 0x7703112333475567)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_ch()
{
    uint64_t value_x = 0xffffffff00000000;
    uint64_t value_y = 0x1111111111111111;
    uint64_t value_z = 0xaaaaaaaaaaaaaaaa;

    if (SHA512::ch(value_x, value_y, value_z) != 0x11111111aaaaaaaa)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_maj()
{
    uint64_t value_x = 0xffffffff00000000;
    uint64_t value_y = 0x1111111111111111;
    uint64_t value_z = 0xaaaaaaaaaaaaaaaa;

    if (SHA512::maj(value_x, value_y, value_z) != 0xbbbbbbbb00000000)
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_calculate_steps_1()
{
    constexpr uint32_t              packet_size     = 128u;

    constexpr SHA512::HASHES_T      expected[]      = { { 0xf6afceb8bcfcddf5, 0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0x58cb02347ab51f91, 0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, },
                                                        { 0x1320f8c9fb872cc0, 0xf6afceb8bcfcddf5, 0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0xc3d4ebfd48650ffa, 0x58cb02347ab51f91, 0x510e527fade682d1, 0x9b05688c2b3e6c1f, },
                                                        { 0xebcffc07203d91f3, 0x1320f8c9fb872cc0, 0xf6afceb8bcfcddf5, 0x6a09e667f3bcc908, 0xdfa9b239f2697812, 0xc3d4ebfd48650ffa, 0x58cb02347ab51f91, 0x510e527fade682d1, },
                                                        { 0x5a83cb3e80050e82, 0xebcffc07203d91f3, 0x1320f8c9fb872cc0, 0xf6afceb8bcfcddf5, 0x0b47b4bb1928990e, 0xdfa9b239f2697812, 0xc3d4ebfd48650ffa, 0x58cb02347ab51f91, },
                                                        { 0xb680953951604860, 0x5a83cb3e80050e82, 0xebcffc07203d91f3, 0x1320f8c9fb872cc0, 0x745aca4a342ed2e2, 0x0b47b4bb1928990e, 0xdfa9b239f2697812, 0xc3d4ebfd48650ffa, },
                                                        { 0xaf573b02403e89cd, 0xb680953951604860, 0x5a83cb3e80050e82, 0xebcffc07203d91f3, 0x96f60209b6dc35ba, 0x745aca4a342ed2e2, 0x0b47b4bb1928990e, 0xdfa9b239f2697812, },
                                                        { 0xc4875b0c7abc076b, 0xaf573b02403e89cd, 0xb680953951604860, 0x5a83cb3e80050e82, 0x5a6c781f54dcc00c, 0x96f60209b6dc35ba, 0x745aca4a342ed2e2, 0x0b47b4bb1928990e, },
                                                        { 0x8093d195e0054fa3, 0xc4875b0c7abc076b, 0xaf573b02403e89cd, 0xb680953951604860, 0x86f67263a0f0ec0a, 0x5a6c781f54dcc00c, 0x96f60209b6dc35ba, 0x745aca4a342ed2e2, },
                                                        { 0xf1eca5544cb89225, 0x8093d195e0054fa3, 0xc4875b0c7abc076b, 0xaf573b02403e89cd, 0xd0403c398fc40002, 0x86f67263a0f0ec0a, 0x5a6c781f54dcc00c, 0x96f60209b6dc35ba, },
                                                        { 0x81782d4a5db48f03, 0xf1eca5544cb89225, 0x8093d195e0054fa3, 0xc4875b0c7abc076b, 0x00091f460be46c52, 0xd0403c398fc40002, 0x86f67263a0f0ec0a, 0x5a6c781f54dcc00c, },
                                                        { 0x69854c4aa0f25b59, 0x81782d4a5db48f03, 0xf1eca5544cb89225, 0x8093d195e0054fa3, 0xd375471bde1ba3f4, 0x00091f460be46c52, 0xd0403c398fc40002, 0x86f67263a0f0ec0a, },
                                                        { 0xdb0a9963f80c2eaa, 0x69854c4aa0f25b59, 0x81782d4a5db48f03, 0xf1eca5544cb89225, 0x475975b91a7a462c, 0xd375471bde1ba3f4, 0x00091f460be46c52, 0xd0403c398fc40002, },
                                                        { 0x5e41214388186c14, 0xdb0a9963f80c2eaa, 0x69854c4aa0f25b59, 0x81782d4a5db48f03, 0xcdf3bff2883fc9d9, 0x475975b91a7a462c, 0xd375471bde1ba3f4, 0x00091f460be46c52, },
                                                        { 0x44249631255d2ca0, 0x5e41214388186c14, 0xdb0a9963f80c2eaa, 0x69854c4aa0f25b59, 0x860acf9effba6f61, 0xcdf3bff2883fc9d9, 0x475975b91a7a462c, 0xd375471bde1ba3f4, },
                                                        { 0xfa967eed85a08028, 0x44249631255d2ca0, 0x5e41214388186c14, 0xdb0a9963f80c2eaa, 0x874bfe5f6aae9f2f, 0x860acf9effba6f61, 0xcdf3bff2883fc9d9, 0x475975b91a7a462c, },
                                                        { 0x0ae07c86b1181c75, 0xfa967eed85a08028, 0x44249631255d2ca0, 0x5e41214388186c14, 0xa77b7c035dd4c161, 0x874bfe5f6aae9f2f, 0x860acf9effba6f61, 0xcdf3bff2883fc9d9, },
                                                        { 0xcaf81a425d800537, 0x0ae07c86b1181c75, 0xfa967eed85a08028, 0x44249631255d2ca0, 0x2deecc6b39d64d78, 0xa77b7c035dd4c161, 0x874bfe5f6aae9f2f, 0x860acf9effba6f61, },
                                                        { 0x4725be249ad19e6b, 0xcaf81a425d800537, 0x0ae07c86b1181c75, 0xfa967eed85a08028, 0xf47e8353f8047455, 0x2deecc6b39d64d78, 0xa77b7c035dd4c161, 0x874bfe5f6aae9f2f, },
                                                        { 0x3c4b4104168e3edb, 0x4725be249ad19e6b, 0xcaf81a425d800537, 0x0ae07c86b1181c75, 0x29695fd88d81dbd0, 0xf47e8353f8047455, 0x2deecc6b39d64d78, 0xa77b7c035dd4c161, },
                                                        { 0x9a3fb4d38ab6cf06, 0x3c4b4104168e3edb, 0x4725be249ad19e6b, 0xcaf81a425d800537, 0xf14998dd5f70767e, 0x29695fd88d81dbd0, 0xf47e8353f8047455, 0x2deecc6b39d64d78, },
                                                        { 0x8dc5ae65569d3855, 0x9a3fb4d38ab6cf06, 0x3c4b4104168e3edb, 0x4725be249ad19e6b, 0x4bb9e66d1145bfdc, 0xf14998dd5f70767e, 0x29695fd88d81dbd0, 0xf47e8353f8047455, },
                                                        { 0xda34d6673d452dcf, 0x8dc5ae65569d3855, 0x9a3fb4d38ab6cf06, 0x3c4b4104168e3edb, 0x8e30ff09ad488753, 0x4bb9e66d1145bfdc, 0xf14998dd5f70767e, 0x29695fd88d81dbd0, },
                                                        { 0x3e2644567b709a78, 0xda34d6673d452dcf, 0x8dc5ae65569d3855, 0x9a3fb4d38ab6cf06, 0x0ac2b11da8f571c6, 0x8e30ff09ad488753, 0x4bb9e66d1145bfdc, 0xf14998dd5f70767e, },
                                                        { 0x4f6877b58fe55484, 0x3e2644567b709a78, 0xda34d6673d452dcf, 0x8dc5ae65569d3855, 0xc66005f87db55233, 0x0ac2b11da8f571c6, 0x8e30ff09ad488753, 0x4bb9e66d1145bfdc, },
                                                        { 0x9aff71163fa3a940, 0x4f6877b58fe55484, 0x3e2644567b709a78, 0xda34d6673d452dcf, 0xd3ecf13769180e6f, 0xc66005f87db55233, 0x0ac2b11da8f571c6, 0x8e30ff09ad488753, },
                                                        { 0x0bc5f791f8e6816b, 0x9aff71163fa3a940, 0x4f6877b58fe55484, 0x3e2644567b709a78, 0x6ddf1fd7edcce336, 0xd3ecf13769180e6f, 0xc66005f87db55233, 0x0ac2b11da8f571c6, },
                                                        { 0x884c3bc27bc4f941, 0x0bc5f791f8e6816b, 0x9aff71163fa3a940, 0x4f6877b58fe55484, 0xe6e48c9a8e948365, 0x6ddf1fd7edcce336, 0xd3ecf13769180e6f, 0xc66005f87db55233, },
                                                        { 0xeab4a9e5771b8d09, 0x884c3bc27bc4f941, 0x0bc5f791f8e6816b, 0x9aff71163fa3a940, 0x09068a4e255a0dac, 0xe6e48c9a8e948365, 0x6ddf1fd7edcce336, 0xd3ecf13769180e6f, },
                                                        { 0xe62349090f47d30a, 0xeab4a9e5771b8d09, 0x884c3bc27bc4f941, 0x0bc5f791f8e6816b, 0x0fcdf99710f21584, 0x09068a4e255a0dac, 0xe6e48c9a8e948365, 0x6ddf1fd7edcce336, },
                                                        { 0x74bf40f869094c63, 0xe62349090f47d30a, 0xeab4a9e5771b8d09, 0x884c3bc27bc4f941, 0xf0aec2fe1437f085, 0x0fcdf99710f21584, 0x09068a4e255a0dac, 0xe6e48c9a8e948365, },
                                                        { 0x4c4fbbb75f1873a6, 0x74bf40f869094c63, 0xe62349090f47d30a, 0xeab4a9e5771b8d09, 0x73e025d91b9efea3, 0xf0aec2fe1437f085, 0x0fcdf99710f21584, 0x09068a4e255a0dac, },
                                                        { 0xff4d3f1f0d46a736, 0x4c4fbbb75f1873a6, 0x74bf40f869094c63, 0xe62349090f47d30a, 0x3cd388e119e8162e, 0x73e025d91b9efea3, 0xf0aec2fe1437f085, 0x0fcdf99710f21584, },
                                                        { 0xa0509015ca08c8d4, 0xff4d3f1f0d46a736, 0x4c4fbbb75f1873a6, 0x74bf40f869094c63, 0xe1034573654a106f, 0x3cd388e119e8162e, 0x73e025d91b9efea3, 0xf0aec2fe1437f085, },
                                                        { 0x60d4e6995ed91fe6, 0xa0509015ca08c8d4, 0xff4d3f1f0d46a736, 0x4c4fbbb75f1873a6, 0xefabbd8bf47c041a, 0xe1034573654a106f, 0x3cd388e119e8162e, 0x73e025d91b9efea3, },
                                                        { 0x2c59ec7743632621, 0x60d4e6995ed91fe6, 0xa0509015ca08c8d4, 0xff4d3f1f0d46a736, 0x0fbae670fa780fd3, 0xefabbd8bf47c041a, 0xe1034573654a106f, 0x3cd388e119e8162e, },
                                                        { 0x1a081afc59fdbc2c, 0x2c59ec7743632621, 0x60d4e6995ed91fe6, 0xa0509015ca08c8d4, 0xf098082f502b44cd, 0x0fbae670fa780fd3, 0xefabbd8bf47c041a, 0xe1034573654a106f, },
                                                        { 0x88df85b0bbe77514, 0x1a081afc59fdbc2c, 0x2c59ec7743632621, 0x60d4e6995ed91fe6, 0x8fbfd0162bbf4675, 0xf098082f502b44cd, 0x0fbae670fa780fd3, 0xefabbd8bf47c041a, },
                                                        { 0x002bb8e4cd989567, 0x88df85b0bbe77514, 0x1a081afc59fdbc2c, 0x2c59ec7743632621, 0x66adcfa249ac7bbd, 0x8fbfd0162bbf4675, 0xf098082f502b44cd, 0x0fbae670fa780fd3, },
                                                        { 0xb3bb8542b3376de5, 0x002bb8e4cd989567, 0x88df85b0bbe77514, 0x1a081afc59fdbc2c, 0xb49596c20feba7de, 0x66adcfa249ac7bbd, 0x8fbfd0162bbf4675, 0xf098082f502b44cd, },
                                                        { 0x8e01e125b855d225, 0xb3bb8542b3376de5, 0x002bb8e4cd989567, 0x88df85b0bbe77514, 0x0c710a47ba6a567b, 0xb49596c20feba7de, 0x66adcfa249ac7bbd, 0x8fbfd0162bbf4675, },
                                                        { 0xb01521dd6a6be12c, 0x8e01e125b855d225, 0xb3bb8542b3376de5, 0x002bb8e4cd989567, 0x169008b3a4bb170b, 0x0c710a47ba6a567b, 0xb49596c20feba7de, 0x66adcfa249ac7bbd, },
                                                        { 0xe96f89dd48cbd851, 0xb01521dd6a6be12c, 0x8e01e125b855d225, 0xb3bb8542b3376de5, 0xf0996439e7b50cb1, 0x169008b3a4bb170b, 0x0c710a47ba6a567b, 0xb49596c20feba7de, },
                                                        { 0xbc05ba8de5d3c480, 0xe96f89dd48cbd851, 0xb01521dd6a6be12c, 0x8e01e125b855d225, 0x639cb938e14dc190, 0xf0996439e7b50cb1, 0x169008b3a4bb170b, 0x0c710a47ba6a567b, },
                                                        { 0x35d7e7f41defcbd5, 0xbc05ba8de5d3c480, 0xe96f89dd48cbd851, 0xb01521dd6a6be12c, 0xcc5100997f5710f2, 0x639cb938e14dc190, 0xf0996439e7b50cb1, 0x169008b3a4bb170b, },
                                                        { 0xc47c9d5c7ea8a234, 0x35d7e7f41defcbd5, 0xbc05ba8de5d3c480, 0xe96f89dd48cbd851, 0x858d832ae0e8911c, 0xcc5100997f5710f2, 0x639cb938e14dc190, 0xf0996439e7b50cb1, },
                                                        { 0x021fbadbabab5ac6, 0xc47c9d5c7ea8a234, 0x35d7e7f41defcbd5, 0xbc05ba8de5d3c480, 0xe95c2a57572d64d9, 0x858d832ae0e8911c, 0xcc5100997f5710f2, 0x639cb938e14dc190, },
                                                        { 0xf61e672694de2d67, 0x021fbadbabab5ac6, 0xc47c9d5c7ea8a234, 0x35d7e7f41defcbd5, 0xc6bc35740d8daa9a, 0xe95c2a57572d64d9, 0x858d832ae0e8911c, 0xcc5100997f5710f2, },
                                                        { 0x6b69fc1bb482feac, 0xf61e672694de2d67, 0x021fbadbabab5ac6, 0xc47c9d5c7ea8a234, 0x35264334c03ac8ad, 0xc6bc35740d8daa9a, 0xe95c2a57572d64d9, 0x858d832ae0e8911c, },
                                                        { 0x571f323d96b3a047, 0x6b69fc1bb482feac, 0xf61e672694de2d67, 0x021fbadbabab5ac6, 0x271580ed6c3e5650, 0x35264334c03ac8ad, 0xc6bc35740d8daa9a, 0xe95c2a57572d64d9, },
                                                        { 0xca9bd862c5050918, 0x571f323d96b3a047, 0x6b69fc1bb482feac, 0xf61e672694de2d67, 0xdfe091dab182e645, 0x271580ed6c3e5650, 0x35264334c03ac8ad, 0xc6bc35740d8daa9a, },
                                                        { 0x813a43dd2c502043, 0xca9bd862c5050918, 0x571f323d96b3a047, 0x6b69fc1bb482feac, 0x07a0d8ef821c5e1a, 0xdfe091dab182e645, 0x271580ed6c3e5650, 0x35264334c03ac8ad, },
                                                        { 0xd43f83727325dd77, 0x813a43dd2c502043, 0xca9bd862c5050918, 0x571f323d96b3a047, 0x483f80a82eaee23e, 0x07a0d8ef821c5e1a, 0xdfe091dab182e645, 0x271580ed6c3e5650, },
                                                        { 0x03df11b32d42e203, 0xd43f83727325dd77, 0x813a43dd2c502043, 0xca9bd862c5050918, 0x504f94e40591cffa, 0x483f80a82eaee23e, 0x07a0d8ef821c5e1a, 0xdfe091dab182e645, },
                                                        { 0xd63f68037ddf06aa, 0x03df11b32d42e203, 0xd43f83727325dd77, 0x813a43dd2c502043, 0xa6781efe1aa1ce02, 0x504f94e40591cffa, 0x483f80a82eaee23e, 0x07a0d8ef821c5e1a, },
                                                        { 0xf650857b5babda4d, 0xd63f68037ddf06aa, 0x03df11b32d42e203, 0xd43f83727325dd77, 0x9ccfb31a86df0f86, 0xa6781efe1aa1ce02, 0x504f94e40591cffa, 0x483f80a82eaee23e, },
                                                        { 0x63b460e42748817e, 0xf650857b5babda4d, 0xd63f68037ddf06aa, 0x03df11b32d42e203, 0xc6b4dd2a9931c509, 0x9ccfb31a86df0f86, 0xa6781efe1aa1ce02, 0x504f94e40591cffa, },
                                                        { 0x7a52912943d52b05, 0x63b460e42748817e, 0xf650857b5babda4d, 0xd63f68037ddf06aa, 0xd2e89bbd91e00be0, 0xc6b4dd2a9931c509, 0x9ccfb31a86df0f86, 0xa6781efe1aa1ce02, },
                                                        { 0x4b81c3aec976ea4b, 0x7a52912943d52b05, 0x63b460e42748817e, 0xf650857b5babda4d, 0x70505988124351ac, 0xd2e89bbd91e00be0, 0xc6b4dd2a9931c509, 0x9ccfb31a86df0f86, },
                                                        { 0x581ecb3355dcd9b8, 0x4b81c3aec976ea4b, 0x7a52912943d52b05, 0x63b460e42748817e, 0x6a3c9b0f71c8bf36, 0x70505988124351ac, 0xd2e89bbd91e00be0, 0xc6b4dd2a9931c509, },
                                                        { 0x2c074484ef1eac8c, 0x581ecb3355dcd9b8, 0x4b81c3aec976ea4b, 0x7a52912943d52b05, 0x4797cde4ed370692, 0x6a3c9b0f71c8bf36, 0x70505988124351ac, 0xd2e89bbd91e00be0, },
                                                        { 0x3857dfd2fc37d3ba, 0x2c074484ef1eac8c, 0x581ecb3355dcd9b8, 0x4b81c3aec976ea4b, 0xa6af4e9c9f807e51, 0x4797cde4ed370692, 0x6a3c9b0f71c8bf36, 0x70505988124351ac, },
                                                        { 0xcfcd928c5424e2b6, 0x3857dfd2fc37d3ba, 0x2c074484ef1eac8c, 0x581ecb3355dcd9b8, 0x09aee5bda1644de5, 0xa6af4e9c9f807e51, 0x4797cde4ed370692, 0x6a3c9b0f71c8bf36, },
                                                        { 0xa81dedbb9f19e643, 0xcfcd928c5424e2b6, 0x3857dfd2fc37d3ba, 0x2c074484ef1eac8c, 0x84058865d60a05fa, 0x09aee5bda1644de5, 0xa6af4e9c9f807e51, 0x4797cde4ed370692, },
                                                        { 0xab44e86276478d85, 0xa81dedbb9f19e643, 0xcfcd928c5424e2b6, 0x3857dfd2fc37d3ba, 0xcd881ee59ca6bc53, 0x84058865d60a05fa, 0x09aee5bda1644de5, 0xa6af4e9c9f807e51, },
                                                        { 0x5a806d7e9821a501, 0xab44e86276478d85, 0xa81dedbb9f19e643, 0xcfcd928c5424e2b6, 0xaa84b086688a5c45, 0xcd881ee59ca6bc53, 0x84058865d60a05fa, 0x09aee5bda1644de5, },
                                                        { 0xeeb9c21bb0102598, 0x5a806d7e9821a501, 0xab44e86276478d85, 0xa81dedbb9f19e643, 0x3b5fed0d6a1f96e1, 0xaa84b086688a5c45, 0xcd881ee59ca6bc53, 0x84058865d60a05fa, },
                                                        { 0x46c4210ab2cc155d, 0xeeb9c21bb0102598, 0x5a806d7e9821a501, 0xab44e86276478d85, 0x29fab5a7bff53366, 0x3b5fed0d6a1f96e1, 0xaa84b086688a5c45, 0xcd881ee59ca6bc53, },
                                                        { 0x54ba35cf56a0340e, 0x46c4210ab2cc155d, 0xeeb9c21bb0102598, 0x5a806d7e9821a501, 0x1c66f46d95690bcf, 0x29fab5a7bff53366, 0x3b5fed0d6a1f96e1, 0xaa84b086688a5c45, },
                                                        { 0x181839d609c79748, 0x54ba35cf56a0340e, 0x46c4210ab2cc155d, 0xeeb9c21bb0102598, 0x0ada78ba2d446140, 0x1c66f46d95690bcf, 0x29fab5a7bff53366, 0x3b5fed0d6a1f96e1, },
                                                        { 0xfb6aaae5d0b6a447, 0x181839d609c79748, 0x54ba35cf56a0340e, 0x46c4210ab2cc155d, 0xe3711cb6564d112d, 0x0ada78ba2d446140, 0x1c66f46d95690bcf, 0x29fab5a7bff53366, },
                                                        { 0x7652c579cb60f19c, 0xfb6aaae5d0b6a447, 0x181839d609c79748, 0x54ba35cf56a0340e, 0xaff62c9665ff80fa, 0xe3711cb6564d112d, 0x0ada78ba2d446140, 0x1c66f46d95690bcf, },
                                                        { 0xf15e9664b2803575, 0x7652c579cb60f19c, 0xfb6aaae5d0b6a447, 0x181839d609c79748, 0x947c3dfafee570ef, 0xaff62c9665ff80fa, 0xe3711cb6564d112d, 0x0ada78ba2d446140, },
                                                        { 0x358406d165aee9ab, 0xf15e9664b2803575, 0x7652c579cb60f19c, 0xfb6aaae5d0b6a447, 0x8c7b5fd91a794ca0, 0x947c3dfafee570ef, 0xaff62c9665ff80fa, 0xe3711cb6564d112d, },
                                                        { 0x20878dcd29cdfaf5, 0x358406d165aee9ab, 0xf15e9664b2803575, 0x7652c579cb60f19c, 0x054d3536539948d0, 0x8c7b5fd91a794ca0, 0x947c3dfafee570ef, 0xaff62c9665ff80fa, },
                                                        { 0x33d48dabb5521de2, 0x20878dcd29cdfaf5, 0x358406d165aee9ab, 0xf15e9664b2803575, 0x2ba18245b50de4cf, 0x054d3536539948d0, 0x8c7b5fd91a794ca0, 0x947c3dfafee570ef, },
                                                        { 0xc8960e6be864b916, 0x33d48dabb5521de2, 0x20878dcd29cdfaf5, 0x358406d165aee9ab, 0x995019a6ff3ba3de, 0x2ba18245b50de4cf, 0x054d3536539948d0, 0x8c7b5fd91a794ca0, },
                                                        { 0x654ef9abec389ca9, 0xc8960e6be864b916, 0x33d48dabb5521de2, 0x20878dcd29cdfaf5, 0xceb9fc3691ce8326, 0x995019a6ff3ba3de, 0x2ba18245b50de4cf, 0x054d3536539948d0, },
                                                        { 0xd67806db8b148677, 0x654ef9abec389ca9, 0xc8960e6be864b916, 0x33d48dabb5521de2, 0x25c96a7768fb2aa3, 0xceb9fc3691ce8326, 0x995019a6ff3ba3de, 0x2ba18245b50de4cf, },
                                                        { 0x10d9c4c4295599f6, 0xd67806db8b148677, 0x654ef9abec389ca9, 0xc8960e6be864b916, 0x9bb4d39778c07f9e, 0x25c96a7768fb2aa3, 0xceb9fc3691ce8326, 0x995019a6ff3ba3de, },
                                                        { 0x73a54f399fa4b1b2, 0x10d9c4c4295599f6, 0xd67806db8b148677, 0x654ef9abec389ca9, 0xd08446aa79693ed7, 0x9bb4d39778c07f9e, 0x25c96a7768fb2aa3, 0xceb9fc3691ce8326, } };

    BUFFER::BUFFER_T<packet_size>   buffer{ 0x61, 0x62, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, };

    SHA512::HASHES_T hashes{ 0x6a09e667f3bcc908,
                             0xbb67ae8584caa73b,
                             0x3c6ef372fe94f82b,
                             0xa54ff53a5f1d36f1,
                             0x510e527fade682d1,
                             0x9b05688c2b3e6c1f,
                             0x1f83d9abfb41bd6b,
                             0x5be0cd19137e2179, };

    for (uint32_t i = 0u; i < 80u; i++)
    {
        SHA512::calculate_internal(reinterpret_cast<uint8_t*>(&buffer), hashes, i);

        if (!verify_hash_1(hashes, expected[i]))
        {
            fprintf(stderr, "%s:%d:%s: Failed to calculate hash\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }

    return true;
}


bool test_calculate_steps_2()
{
    constexpr uint32_t              packet_size = 128u;

    constexpr SHA512::HASHES_T      expected[]      = { { 0xf6afce9d2263455d, 0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0x58cb0218e01b86f9, 0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, },
                                                        { 0x0b7056a534ae5f62, 0xf6afce9d2263455d, 0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0xf8c7198fe39e4c8c, 0x58cb0218e01b86f9, 0x510e527fade682d1, 0x9b05688c2b3e6c1f, },
                                                        { 0x2ca82233760c9942, 0x0b7056a534ae5f62, 0xf6afce9d2263455d, 0x6a09e667f3bcc908, 0x303eccccd65953de, 0xf8c7198fe39e4c8c, 0x58cb0218e01b86f9, 0x510e527fade682d1, },
                                                        { 0xa023f17ce52cda7b, 0x2ca82233760c9942, 0x0b7056a534ae5f62, 0xf6afce9d2263455d, 0xffdee5eedcc9ca42, 0x303eccccd65953de, 0xf8c7198fe39e4c8c, 0x58cb0218e01b86f9, },
                                                        { 0x8f0a67d9d591a1a7, 0xa023f17ce52cda7b, 0x2ca82233760c9942, 0x0b7056a534ae5f62, 0xcb4cfbb166505f2f, 0xffdee5eedcc9ca42, 0x303eccccd65953de, 0xf8c7198fe39e4c8c, },
                                                        { 0xb466267371acc493, 0x8f0a67d9d591a1a7, 0xa023f17ce52cda7b, 0x2ca82233760c9942, 0x73d6c84c54d399ee, 0xcb4cfbb166505f2f, 0xffdee5eedcc9ca42, 0x303eccccd65953de, },
                                                        { 0x658269f1a312fccd, 0xb466267371acc493, 0x8f0a67d9d591a1a7, 0xa023f17ce52cda7b, 0xcdc40314975fb275, 0x73d6c84c54d399ee, 0xcb4cfbb166505f2f, 0xffdee5eedcc9ca42, },
                                                        { 0x65e3519c5b88181b, 0x658269f1a312fccd, 0xb466267371acc493, 0x8f0a67d9d591a1a7, 0xa657850ab3970c5a, 0xcdc40314975fb275, 0x73d6c84c54d399ee, 0xcb4cfbb166505f2f, },
                                                        { 0x56604fbb4b6393ec, 0x65e3519c5b88181b, 0x658269f1a312fccd, 0xb466267371acc493, 0xe8b3be22fbe64df7, 0xa657850ab3970c5a, 0xcdc40314975fb275, 0x73d6c84c54d399ee, },
                                                        { 0xc4562769a37d02c0, 0x56604fbb4b6393ec, 0x65e3519c5b88181b, 0x658269f1a312fccd, 0x0062e70a1ef705c1, 0xe8b3be22fbe64df7, 0xa657850ab3970c5a, 0xcdc40314975fb275, },
                                                        { 0x27c0b4c9186e1736, 0xc4562769a37d02c0, 0x56604fbb4b6393ec, 0x65e3519c5b88181b, 0xbc9740477a18ae2d, 0x0062e70a1ef705c1, 0xe8b3be22fbe64df7, 0xa657850ab3970c5a, },
                                                        { 0xf17f52fb02f4eb74, 0x27c0b4c9186e1736, 0xc4562769a37d02c0, 0x56604fbb4b6393ec, 0xbe58522cb9590ee1, 0xbc9740477a18ae2d, 0x0062e70a1ef705c1, 0xe8b3be22fbe64df7, },
                                                        { 0xf2c245ac903d4a35, 0xf17f52fb02f4eb74, 0x27c0b4c9186e1736, 0xc4562769a37d02c0, 0x49d5fa3a16dcd502, 0xbe58522cb9590ee1, 0xbc9740477a18ae2d, 0x0062e70a1ef705c1, },
                                                        { 0x9b04175ea8090daa, 0xf2c245ac903d4a35, 0xf17f52fb02f4eb74, 0x27c0b4c9186e1736, 0xec9c5e98ff98760d, 0x49d5fa3a16dcd502, 0xbe58522cb9590ee1, 0xbc9740477a18ae2d, },
                                                        { 0x481b8a6ee5e07031, 0x9b04175ea8090daa, 0xf2c245ac903d4a35, 0xf17f52fb02f4eb74, 0xe4d35b613a5ac420, 0xec9c5e98ff98760d, 0x49d5fa3a16dcd502, 0xbe58522cb9590ee1, },
                                                        { 0x9356ac3ec3e51459, 0x481b8a6ee5e07031, 0x9b04175ea8090daa, 0xf2c245ac903d4a35, 0x701f17d27582443b, 0xe4d35b613a5ac420, 0xec9c5e98ff98760d, 0x49d5fa3a16dcd502, },
                                                        { 0xb889ed34abd7aa37, 0x9356ac3ec3e51459, 0x481b8a6ee5e07031, 0x9b04175ea8090daa, 0x1d05d9ba779a1a78, 0x701f17d27582443b, 0xe4d35b613a5ac420, 0xec9c5e98ff98760d, },
                                                        { 0xbf537b1f3edc7381, 0xb889ed34abd7aa37, 0x9356ac3ec3e51459, 0x481b8a6ee5e07031, 0xc362ff9cf932951d, 0x1d05d9ba779a1a78, 0x701f17d27582443b, 0xe4d35b613a5ac420, },
                                                        { 0xd4e44d54e8242ad8, 0xbf537b1f3edc7381, 0xb889ed34abd7aa37, 0x9356ac3ec3e51459, 0x459e4e6888919f36, 0xc362ff9cf932951d, 0x1d05d9ba779a1a78, 0x701f17d27582443b, },
                                                        { 0x05f3fba454e5de3d, 0xd4e44d54e8242ad8, 0xbf537b1f3edc7381, 0xb889ed34abd7aa37, 0xcaed4b5fa322b984, 0x459e4e6888919f36, 0xc362ff9cf932951d, 0x1d05d9ba779a1a78, },
                                                        { 0xcdb73772dc0248bf, 0x05f3fba454e5de3d, 0xd4e44d54e8242ad8, 0xbf537b1f3edc7381, 0xdc8049afa6acd502, 0xcaed4b5fa322b984, 0x459e4e6888919f36, 0xc362ff9cf932951d, },
                                                        { 0x1d47a3268ff677ed, 0xcdb73772dc0248bf, 0x05f3fba454e5de3d, 0xd4e44d54e8242ad8, 0x8407818e9b28cc12, 0xdc8049afa6acd502, 0xcaed4b5fa322b984, 0x459e4e6888919f36, },
                                                        { 0xaf4e23eb622d0df4, 0x1d47a3268ff677ed, 0xcdb73772dc0248bf, 0x05f3fba454e5de3d, 0x64b5ae5424598428, 0x8407818e9b28cc12, 0xdc8049afa6acd502, 0xcaed4b5fa322b984, },
                                                        { 0xbe50606778de14a6, 0xaf4e23eb622d0df4, 0x1d47a3268ff677ed, 0xcdb73772dc0248bf, 0x0a5d727cc92e7adb, 0x64b5ae5424598428, 0x8407818e9b28cc12, 0xdc8049afa6acd502, },
                                                        { 0x821e44f6678ac478, 0xbe50606778de14a6, 0xaf4e23eb622d0df4, 0x1d47a3268ff677ed, 0xf367e596d0a038a5, 0x0a5d727cc92e7adb, 0x64b5ae5424598428, 0x8407818e9b28cc12, },
                                                        { 0x0c852b1359a77c18, 0x821e44f6678ac478, 0xbe50606778de14a6, 0xaf4e23eb622d0df4, 0x6dec8a3396a80c3f, 0xf367e596d0a038a5, 0x0a5d727cc92e7adb, 0x64b5ae5424598428, },
                                                        { 0xebb574fad4b7a7e4, 0x0c852b1359a77c18, 0x821e44f6678ac478, 0xbe50606778de14a6, 0xa241e7efc1eb6ff9, 0x6dec8a3396a80c3f, 0xf367e596d0a038a5, 0x0a5d727cc92e7adb, },
                                                        { 0xa092821c3cdf08da, 0xebb574fad4b7a7e4, 0x0c852b1359a77c18, 0x821e44f6678ac478, 0xc84e849917a7c08e, 0xa241e7efc1eb6ff9, 0x6dec8a3396a80c3f, 0xf367e596d0a038a5, },
                                                        { 0x82ba2e1a2df2a4f1, 0xa092821c3cdf08da, 0xebb574fad4b7a7e4, 0x0c852b1359a77c18, 0x61845f6924789851, 0xc84e849917a7c08e, 0xa241e7efc1eb6ff9, 0x6dec8a3396a80c3f, },
                                                        { 0x1959ad991c63d06a, 0x82ba2e1a2df2a4f1, 0xa092821c3cdf08da, 0xebb574fad4b7a7e4, 0x231faf24910a891a, 0x61845f6924789851, 0xc84e849917a7c08e, 0xa241e7efc1eb6ff9, },
                                                        { 0x9b32d4cacd9a625b, 0x1959ad991c63d06a, 0x82ba2e1a2df2a4f1, 0xa092821c3cdf08da, 0x533066919d608799, 0x231faf24910a891a, 0x61845f6924789851, 0xc84e849917a7c08e, },
                                                        { 0xdc55339f4d841965, 0x9b32d4cacd9a625b, 0x1959ad991c63d06a, 0x82ba2e1a2df2a4f1, 0xe2517f359998a58d, 0x533066919d608799, 0x231faf24910a891a, 0x61845f6924789851, },
                                                        { 0xfdebb1283b12514f, 0xdc55339f4d841965, 0x9b32d4cacd9a625b, 0x1959ad991c63d06a, 0xb1989170a183c661, 0xe2517f359998a58d, 0x533066919d608799, 0x231faf24910a891a, },
                                                        { 0xb44c7975a83e3334, 0xfdebb1283b12514f, 0xdc55339f4d841965, 0x9b32d4cacd9a625b, 0x009ad175b8d588a4, 0xb1989170a183c661, 0xe2517f359998a58d, 0x533066919d608799, },
                                                        { 0x0bac61bfc53d18b7, 0xb44c7975a83e3334, 0xfdebb1283b12514f, 0xdc55339f4d841965, 0xa7d5416d690557b8, 0x009ad175b8d588a4, 0xb1989170a183c661, 0xe2517f359998a58d, },
                                                        { 0x392893c22e75856a, 0x0bac61bfc53d18b7, 0xb44c7975a83e3334, 0xfdebb1283b12514f, 0x7a7c9eb7bc813248, 0xa7d5416d690557b8, 0x009ad175b8d588a4, 0xb1989170a183c661, },
                                                        { 0x824408631432e09b, 0x392893c22e75856a, 0x0bac61bfc53d18b7, 0xb44c7975a83e3334, 0x5e696a9fda56d6bf, 0x7a7c9eb7bc813248, 0xa7d5416d690557b8, 0x009ad175b8d588a4, },
                                                        { 0xa64162f151a8c1cb, 0x824408631432e09b, 0x392893c22e75856a, 0x0bac61bfc53d18b7, 0x0f57062401dc680b, 0x5e696a9fda56d6bf, 0x7a7c9eb7bc813248, 0xa7d5416d690557b8, },
                                                        { 0x922537abad1e95a1, 0xa64162f151a8c1cb, 0x824408631432e09b, 0x392893c22e75856a, 0x4f4c193d435ff721, 0x0f57062401dc680b, 0x5e696a9fda56d6bf, 0x7a7c9eb7bc813248, },
                                                        { 0xb80591f6fbfadcde, 0x922537abad1e95a1, 0xa64162f151a8c1cb, 0x824408631432e09b, 0x00f4407c0f37237e, 0x4f4c193d435ff721, 0x0f57062401dc680b, 0x5e696a9fda56d6bf, },
                                                        { 0x08f151f4b8d0fa2e, 0xb80591f6fbfadcde, 0x922537abad1e95a1, 0xa64162f151a8c1cb, 0xec8b96fe402094cd, 0x00f4407c0f37237e, 0x4f4c193d435ff721, 0x0f57062401dc680b, },
                                                        { 0x12b5fcc2b68f65c0, 0x08f151f4b8d0fa2e, 0xb80591f6fbfadcde, 0x922537abad1e95a1, 0xd688101dfd24a148, 0xec8b96fe402094cd, 0x00f4407c0f37237e, 0x4f4c193d435ff721, },
                                                        { 0xa71bf5bd64289948, 0x12b5fcc2b68f65c0, 0x08f151f4b8d0fa2e, 0xb80591f6fbfadcde, 0xe052bfb7a6945939, 0xd688101dfd24a148, 0xec8b96fe402094cd, 0x00f4407c0f37237e, },
                                                        { 0x890c2cd670c4aea3, 0xa71bf5bd64289948, 0x12b5fcc2b68f65c0, 0x08f151f4b8d0fa2e, 0xdd13e4edeeff00e7, 0xe052bfb7a6945939, 0xd688101dfd24a148, 0xec8b96fe402094cd, },
                                                        { 0xca61990b43297ffc, 0x890c2cd670c4aea3, 0xa71bf5bd64289948, 0x12b5fcc2b68f65c0, 0x139aa55c51d9ee5f, 0xdd13e4edeeff00e7, 0xe052bfb7a6945939, 0xd688101dfd24a148, },
                                                        { 0x7196e8fa538ba4bf, 0xca61990b43297ffc, 0x890c2cd670c4aea3, 0xa71bf5bd64289948, 0x046735513cdd14d3, 0x139aa55c51d9ee5f, 0xdd13e4edeeff00e7, 0xe052bfb7a6945939, },
                                                        { 0x1f0720944dbeb6a4, 0x7196e8fa538ba4bf, 0xca61990b43297ffc, 0x890c2cd670c4aea3, 0xa41eb7e5a27588e3, 0x046735513cdd14d3, 0x139aa55c51d9ee5f, 0xdd13e4edeeff00e7, },
                                                        { 0xd6d4f8608b8ab199, 0x1f0720944dbeb6a4, 0x7196e8fa538ba4bf, 0xca61990b43297ffc, 0x24b9c216f915da60, 0xa41eb7e5a27588e3, 0x046735513cdd14d3, 0x139aa55c51d9ee5f, },
                                                        { 0x88761eb67845978e, 0xd6d4f8608b8ab199, 0x1f0720944dbeb6a4, 0x7196e8fa538ba4bf, 0x9fe22e39448d50ed, 0x24b9c216f915da60, 0xa41eb7e5a27588e3, 0x046735513cdd14d3, },
                                                        { 0x7d40e6be47d85702, 0x88761eb67845978e, 0xd6d4f8608b8ab199, 0x1f0720944dbeb6a4, 0xd9c900e01968c33e, 0x9fe22e39448d50ed, 0x24b9c216f915da60, 0xa41eb7e5a27588e3, },
                                                        { 0x7d0d988df5768598, 0x7d40e6be47d85702, 0x88761eb67845978e, 0xd6d4f8608b8ab199, 0x2ec2e522a7c7d12c, 0xd9c900e01968c33e, 0x9fe22e39448d50ed, 0x24b9c216f915da60, },
                                                        { 0x48a8b60575b37f31, 0x7d0d988df5768598, 0x7d40e6be47d85702, 0x88761eb67845978e, 0x7059f9bc8c88a373, 0x2ec2e522a7c7d12c, 0xd9c900e01968c33e, 0x9fe22e39448d50ed, },
                                                        { 0x6bc425af294bbf79, 0x48a8b60575b37f31, 0x7d0d988df5768598, 0x7d40e6be47d85702, 0x6a8143b1716ee33d, 0x7059f9bc8c88a373, 0x2ec2e522a7c7d12c, 0xd9c900e01968c33e, },
                                                        { 0x307a456158ee8849, 0x6bc425af294bbf79, 0x48a8b60575b37f31, 0x7d0d988df5768598, 0x4372e85c16ee4440, 0x6a8143b1716ee33d, 0x7059f9bc8c88a373, 0x2ec2e522a7c7d12c, },
                                                        { 0xaf36382c8fd716be, 0x307a456158ee8849, 0x6bc425af294bbf79, 0x48a8b60575b37f31, 0xa8f8b0033187a916, 0x4372e85c16ee4440, 0x6a8143b1716ee33d, 0x7059f9bc8c88a373, },
                                                        { 0x810ebee951c64ca1, 0xaf36382c8fd716be, 0x307a456158ee8849, 0x6bc425af294bbf79, 0x16a64f5997b9cca6, 0xa8f8b0033187a916, 0x4372e85c16ee4440, 0x6a8143b1716ee33d, },
                                                        { 0x2dd7659f1b4d13cd, 0x810ebee951c64ca1, 0xaf36382c8fd716be, 0x307a456158ee8849, 0x5da6793bb7286a4b, 0x16a64f5997b9cca6, 0xa8f8b0033187a916, 0x4372e85c16ee4440, },
                                                        { 0x5ac712acff4b98be, 0x2dd7659f1b4d13cd, 0x810ebee951c64ca1, 0xaf36382c8fd716be, 0x91f6395b301adbfd, 0x5da6793bb7286a4b, 0x16a64f5997b9cca6, 0xa8f8b0033187a916, },
                                                        { 0xc1af358833cb03c0, 0x5ac712acff4b98be, 0x2dd7659f1b4d13cd, 0x810ebee951c64ca1, 0xd4883c0c21dda190, 0x91f6395b301adbfd, 0x5da6793bb7286a4b, 0x16a64f5997b9cca6, },
                                                        { 0x88a306074d388c7d, 0xc1af358833cb03c0, 0x5ac712acff4b98be, 0x2dd7659f1b4d13cd, 0x9fc52468b897f9c8, 0xd4883c0c21dda190, 0x91f6395b301adbfd, 0x5da6793bb7286a4b, },
                                                        { 0xf11bfd0cf67d3040, 0x88a306074d388c7d, 0xc1af358833cb03c0, 0x5ac712acff4b98be, 0x47efb6407f74d318, 0x9fc52468b897f9c8, 0xd4883c0c21dda190, 0x91f6395b301adbfd, },
                                                        { 0x1f065e7828ed4e1b, 0xf11bfd0cf67d3040, 0x88a306074d388c7d, 0xc1af358833cb03c0, 0x7481899904a4ce23, 0x47efb6407f74d318, 0x9fc52468b897f9c8, 0xd4883c0c21dda190, },
                                                        { 0xaebde39f2bc42ec1, 0x1f065e7828ed4e1b, 0xf11bfd0cf67d3040, 0x88a306074d388c7d, 0x62ab526ff177a988, 0x7481899904a4ce23, 0x47efb6407f74d318, 0x9fc52468b897f9c8, },
                                                        { 0xd35a94706e3e5df2, 0xaebde39f2bc42ec1, 0x1f065e7828ed4e1b, 0xf11bfd0cf67d3040, 0x53f92b648d5d815c, 0x62ab526ff177a988, 0x7481899904a4ce23, 0x47efb6407f74d318, },
                                                        { 0xd72d727c53e09ab9, 0xd35a94706e3e5df2, 0xaebde39f2bc42ec1, 0x1f065e7828ed4e1b, 0x10746426ba9824f4, 0x53f92b648d5d815c, 0x62ab526ff177a988, 0x7481899904a4ce23, },
                                                        { 0x3a7235e5a4051d94, 0xd72d727c53e09ab9, 0xd35a94706e3e5df2, 0xaebde39f2bc42ec1, 0xafe455daec5c2b00, 0x10746426ba9824f4, 0x53f92b648d5d815c, 0x62ab526ff177a988, },
                                                        { 0xf7f510fe73ef7e76, 0x3a7235e5a4051d94, 0xd72d727c53e09ab9, 0xd35a94706e3e5df2, 0xf1202c0bb7c4583f, 0xafe455daec5c2b00, 0x10746426ba9824f4, 0x53f92b648d5d815c, },
                                                        { 0x23c2acfb393523e9, 0xf7f510fe73ef7e76, 0x3a7235e5a4051d94, 0xd72d727c53e09ab9, 0xa0bc2a61044ac12e, 0xf1202c0bb7c4583f, 0xafe455daec5c2b00, 0x10746426ba9824f4, },
                                                        { 0x0307d241a1ed7121, 0x23c2acfb393523e9, 0xf7f510fe73ef7e76, 0x3a7235e5a4051d94, 0xfad5f38f1e0aea12, 0xa0bc2a61044ac12e, 0xf1202c0bb7c4583f, 0xafe455daec5c2b00, },
                                                        { 0x191814d82f0a16fb, 0x0307d241a1ed7121, 0x23c2acfb393523e9, 0xf7f510fe73ef7e76, 0x39d325086e66e200, 0xfad5f38f1e0aea12, 0xa0bc2a61044ac12e, 0xf1202c0bb7c4583f, },
                                                        { 0x0a1ed41b6da18c01, 0x191814d82f0a16fb, 0x0307d241a1ed7121, 0x23c2acfb393523e9, 0xb3d3521e166e5df1, 0x39d325086e66e200, 0xfad5f38f1e0aea12, 0xa0bc2a61044ac12e, },
                                                        { 0x8a3f07db93f6c827, 0x0a1ed41b6da18c01, 0x191814d82f0a16fb, 0x0307d241a1ed7121, 0x6b370074be040ed7, 0xb3d3521e166e5df1, 0x39d325086e66e200, 0xfad5f38f1e0aea12, },
                                                        { 0x002744d87ef80d28, 0x8a3f07db93f6c827, 0x0a1ed41b6da18c01, 0x191814d82f0a16fb, 0x8c5a245de2d72fe6, 0x6b370074be040ed7, 0xb3d3521e166e5df1, 0x39d325086e66e200, },
                                                        { 0x778dc7880a4a2aa0, 0x002744d87ef80d28, 0x8a3f07db93f6c827, 0x0a1ed41b6da18c01, 0x45a375b466e5e342, 0x8c5a245de2d72fe6, 0x6b370074be040ed7, 0xb3d3521e166e5df1, },
                                                        { 0xa3f11de5ede05b11, 0x778dc7880a4a2aa0, 0x002744d87ef80d28, 0x8a3f07db93f6c827, 0xf5bbf52f1ab7cc05, 0x45a375b466e5e342, 0x8c5a245de2d72fe6, 0x6b370074be040ed7, },
                                                        { 0x629c8ae6ecd8af4b, 0xa3f11de5ede05b11, 0x778dc7880a4a2aa0, 0x002744d87ef80d28, 0x5a8fe5919d3cf136, 0xf5bbf52f1ab7cc05, 0x45a375b466e5e342, 0x8c5a245de2d72fe6, },
                                                        { 0xc9a8c1e2d063ce94, 0x629c8ae6ecd8af4b, 0xa3f11de5ede05b11, 0x778dc7880a4a2aa0, 0xaacd089bfae8faf9, 0x5a8fe5919d3cf136, 0xf5bbf52f1ab7cc05, 0x45a375b466e5e342, },
                                                        { 0xc517cba6a09bb26a, 0xc9a8c1e2d063ce94, 0x629c8ae6ecd8af4b, 0xa3f11de5ede05b11, 0xe1682bd33c8f8e23, 0xaacd089bfae8faf9, 0x5a8fe5919d3cf136, 0xf5bbf52f1ab7cc05, },
                                                        { 0x11e3570e06e3b74e, 0xc517cba6a09bb26a, 0xc9a8c1e2d063ce94, 0x629c8ae6ecd8af4b, 0x075aabbade34fd01, 0xe1682bd33c8f8e23, 0xaacd089bfae8faf9, 0x5a8fe5919d3cf136, },
                                                        { 0xd90f1b1237b3a561, 0x11e3570e06e3b74e, 0xc517cba6a09bb26a, 0xc9a8c1e2d063ce94, 0x867983f69d3a3ad1, 0x075aabbade34fd01, 0xe1682bd33c8f8e23, 0xaacd089bfae8faf9, } };

    BUFFER::BUFFER_T<packet_size>   buffer{ 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
                                            0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
                                            0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,
                                            0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
                                            0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C,
                                            0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,
                                            0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
                                            0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
                                            0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
                                            0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,
                                            0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72,
                                            0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73,
                                            0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
                                            0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
                                            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

    SHA512::HASHES_T hashes{ 0x6a09e667f3bcc908,
                             0xbb67ae8584caa73b,
                             0x3c6ef372fe94f82b,
                             0xa54ff53a5f1d36f1,
                             0x510e527fade682d1,
                             0x9b05688c2b3e6c1f,
                             0x1f83d9abfb41bd6b,
                             0x5be0cd19137e2179, };

    for (uint32_t i = 0u; i < 80u; i++)
    {
        SHA512::calculate_internal(reinterpret_cast<uint8_t*>(&buffer), hashes, i);

        if (!verify_hash_1(hashes, expected[i]))
        {
            fprintf(stderr, "%s:%d:%s: Failed to calculate hash\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }

    return true;
}


bool test_calculate_all_1()
{
    constexpr uint32_t              packet_size = 128u;

    BUFFER::BUFFER_T<packet_size>   buffer{ 0x61, 0x62, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, };

    SHA512::HASHES_T                expected  { 0xDDAF35A193617ABA, 0xCC417349AE204131, 0x12E6FA4E89A97EA2, 0x0A9EEEE64B55D39A,
                                                0x2192992A274FC1A8, 0x36BA3C23A3FEEBBD, 0x454D4423643CE80E, 0x2A9AC94FA54CA49F };

    SHA512::SHA512_T<packet_size>   sha512{};

    SHA512::calculate(buffer, sha512, true);

    if (!verify_hash_2(sha512, expected))
    {
        fprintf(stderr, "%s:%d:%s: Failed to calculate hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_calculate_all_2()
{
    constexpr uint32_t              packet_size = 128u;

    BUFFER::BUFFER_T<packet_size>   buffer{ 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
                                            0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
                                            0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,
                                            0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
                                            0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C,
                                            0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,
                                            0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
                                            0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
                                            0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
                                            0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,
                                            0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72,
                                            0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73,
                                            0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
                                            0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
                                            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

    SHA512::HASHES_T                expected  { 0x4319017A2B706E69, 0xCD4B05938BAE5E89, 0x0186BF199F30AA95, 0x6EF8B71D2F810585,
                                                0xD787D6764B20BDA2, 0xA260144709736920, 0x00EC057F37D14B8E, 0x06ADD5B50E671C72 };

    SHA512::SHA512_T<packet_size>   sha512{};

    SHA512::calculate(buffer, sha512, true);

    if (!verify_hash_2(sha512, expected))
    {
        fprintf(stderr, "%s:%d:%s: Failed to calculate hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_calculate_many()
{
    constexpr uint32_t              packet_size = 1024u;

    SHA512::HASHES_T                expected  { 0x67258fc72c77f468, 0x43f9accabbbeeaae, 0x312746c6ae354f33, 0x48c2e5ef4dc6c33f,
                                                0xaa7a85c78f6fd685, 0x6e4033afdd2fcef2, 0xa28834a012c2c945, 0xeb9b941dc2f38154 };

    BUFFER::BUFFER_T<packet_size>   buffer{};

    SHA512::SHA512_T<packet_size>   sha512{};

    SHA512::calculate(buffer, sha512, true);


    if (!verify_hash_2(sha512, expected))
    {
        fprintf(stderr, "%s:%d:%s: Failed to calculate hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_calculate_frame_0()
{
    constexpr uint32_t                                  packet_size         = 128u;
    constexpr uint32_t                                  columns             = 3u;
    constexpr uint32_t                                  rows                = 2u;

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_a       { 0x20, 0x9b, 0x28, 0x32, 0x79, 0xda, 0x05, 0xa5, 0xa8, 0x37, 0x3e, 0x35, 0x80, 0x0e, 0x29, 0x3e,
                                                                                0x49, 0x0a, 0x6c, 0x8b, 0x54, 0xba, 0xea, 0x72, 0x7e, 0xb6, 0xb0, 0xde, 0x66, 0x90, 0x27, 0x31,
                                                                                0x7b, 0x40, 0xc5, 0x69, 0xb7, 0x47, 0x6b, 0xa8, 0x62, 0x79, 0x3f, 0x78, 0xc4, 0xc0, 0x12, 0x5f,
                                                                                0xde, 0xd9, 0x3a, 0x49, 0x9d, 0x3c, 0x06, 0x8a, 0xfc, 0x9b, 0x55, 0x1c, 0xf1, 0x36, 0xe2, 0xc3, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_b       { 0xe4, 0x25, 0xb7, 0x65, 0x2a, 0xa4, 0x2c, 0x2f, 0x23, 0x2a, 0x79, 0xef, 0x92, 0xaf, 0xa5, 0xf2,
                                                                                0xe0, 0xcb, 0x2d, 0x79, 0x21, 0x14, 0xb5, 0xbc, 0x82, 0x05, 0x7d, 0xf0, 0xd9, 0x94, 0x24, 0xd3,
                                                                                0x73, 0xd7, 0x40, 0x87, 0xe1, 0xc1, 0x15, 0xc5, 0xb5, 0x13, 0x44, 0xf5, 0x56, 0xd3, 0xdd, 0x27,
                                                                                0x84, 0x11, 0x04, 0xf3, 0xd8, 0xde, 0xd8, 0xef, 0x69, 0x8b, 0xf0, 0xbd, 0x29, 0xff, 0x14, 0x68, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_0       { 0x00, 0xc4, 0xab, 0x0f, 0xac, 0x6a, 0x57, 0x03, 0x66, 0x9e, 0x62, 0x1c, 0xc3, 0xeb, 0xd3, 0xcc,
                                                                                0x31, 0x7b, 0x2b, 0x93, 0xb8, 0x72, 0x8d, 0x6e, 0x40, 0x18, 0x98, 0x13, 0xf9, 0xe1, 0xd9, 0xc2,
                                                                                0x40, 0x1c, 0x9d, 0xeb, 0xfa, 0x56, 0xe2, 0x19, 0x4b, 0xfd, 0xc7, 0x9a, 0xce, 0x56, 0x34, 0x5e,
                                                                                0xd4, 0x29, 0x28, 0x36, 0x93, 0xb4, 0x0a, 0x79, 0x09, 0xd8, 0xa3, 0x76, 0x8f, 0xd9, 0x6f, 0x0f, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_1       { 0xd1, 0xaf, 0x8a, 0x9d, 0x55, 0x17, 0x36, 0xc3, 0x2f, 0x1e, 0xb2, 0x86, 0x2e, 0xe3, 0xe8, 0x1d,
                                                                                0x51, 0xc9, 0xe8, 0x9c, 0x68, 0x3c, 0x14, 0x8b, 0x23, 0x52, 0x97, 0x53, 0x15, 0x08, 0xea, 0x64,
                                                                                0x95, 0xbe, 0xe6, 0x98, 0x5b, 0x43, 0x42, 0x21, 0x86, 0xa9, 0x0f, 0xe8, 0xcf, 0x3f, 0x62, 0xaa,
                                                                                0xd2, 0x30, 0xe3, 0xb6, 0x18, 0x22, 0x2e, 0x8b, 0xbb, 0xb3, 0x9c, 0xd1, 0xe7, 0x5d, 0xcb, 0x70, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_2       { 0x7a, 0x6b, 0x32, 0x05, 0xcf, 0x18, 0x00, 0x2d, 0x7a, 0x97, 0x36, 0x7b, 0x2c, 0xd2, 0x94, 0x63,
                                                                                0x3e, 0x61, 0x65, 0x1e, 0x1e, 0x2d, 0xfb, 0xdb, 0x66, 0xd0, 0x8e, 0xa7, 0x62, 0x53, 0xf3, 0x71,
                                                                                0x8a, 0x97, 0xa8, 0x92, 0x12, 0x03, 0xca, 0xa1, 0xaa, 0x91, 0xf1, 0x15, 0xe4, 0xad, 0xbb, 0x29,
                                                                                0x50, 0x68, 0x35, 0x2b, 0x11, 0xef, 0xd4, 0xdb, 0x6a, 0xe2, 0x44, 0x3a, 0x7e, 0xbf, 0xa0, 0xf9, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a0             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a1             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x70,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                                                                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                                                                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                                                                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                                                                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                                                                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                                                                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a2             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0xe0,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
                                                                                0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
                                                                                0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
                                                                                0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
                                                                                0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
                                                                                0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
                                                                                0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b0             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x01, 0x50,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                                                                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                                                                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                                                                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                                                                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                                                                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                                                                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b1             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x01, 0xc0,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                                                                                0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                                                                                0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                                                                                0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                                                                                0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                                                                                0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                                                                                0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b2             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x02, 0x30,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                                                                                0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                                                                                0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                                                                                0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                                                                                0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                                                                                0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                                                                                0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, };

    SHA512::SHA512_T<packet_size> sha_512_0{};
    SHA512::SHA512_T<packet_size> sha_512_1{};
    SHA512::SHA512_T<packet_size> sha_512_2{};
    SHA512::SHA512_T<packet_size> sha_512_a{};
    SHA512::SHA512_T<packet_size> sha_512_b{};

    SHA512::calculate(buffer_a0, sha_512_a, true);
    SHA512::calculate(buffer_a1, sha_512_a, false);
    SHA512::calculate(buffer_a2, sha_512_a, false);

    SHA512::calculate(buffer_b0, sha_512_b, true);
    SHA512::calculate(buffer_b1, sha_512_b, false);
    SHA512::calculate(buffer_b2, sha_512_b, false);

    SHA512::calculate(buffer_a0, sha_512_0, true);
    SHA512::calculate(buffer_b0, sha_512_0, false);

    SHA512::calculate(buffer_a1, sha_512_1, true);
    SHA512::calculate(buffer_b1, sha_512_1, false);

    SHA512::calculate(buffer_a2, sha_512_2, true);
    SHA512::calculate(buffer_b2, sha_512_2, false);

    if (memcmp(sha_512_a.Data, expected_hash_a, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_b.Data, expected_hash_b, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_0.Data, expected_hash_0, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_1.Data, expected_hash_1, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_2.Data, expected_hash_2, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_calculate_frame_1()
{
    constexpr uint32_t                                  packet_size         = 128u;
    constexpr uint32_t                                  columns             = 3u;
    constexpr uint32_t                                  rows                = 2u;

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_a       { 0x5b, 0x80, 0xaa, 0xd4, 0x58, 0xcb, 0xb0, 0x59, 0xcd, 0xe9, 0xdf, 0x01, 0xee, 0x8c, 0xa7, 0x94,
                                                                                0x6a, 0x5d, 0x03, 0x8a, 0x14, 0xe9, 0x33, 0xbd, 0x9f, 0xab, 0xb0, 0xb9, 0x6a, 0xc9, 0x59, 0x63,
                                                                                0xbe, 0x76, 0x88, 0x00, 0x19, 0xb4, 0x40, 0xd8, 0x48, 0x77, 0x6a, 0xa2, 0xb1, 0xe0, 0x3f, 0x97,
                                                                                0x4e, 0x51, 0xe5, 0x9b, 0xab, 0x9a, 0x9b, 0xc1, 0x48, 0xe8, 0x17, 0xec, 0xc5, 0xe2, 0xe9, 0x2e, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_b       { 0x2b, 0xe0, 0x83, 0xd1, 0x35, 0xe6, 0xfc, 0xb5, 0x38, 0x0e, 0x26, 0xd7, 0x7f, 0xeb, 0x2f, 0xb2,
                                                                                0x6c, 0x07, 0x16, 0xfb, 0x95, 0xd4, 0xe3, 0x95, 0x5f, 0xb6, 0xe0, 0x02, 0xf2, 0x29, 0xcb, 0x82,
                                                                                0x42, 0x09, 0xbd, 0x40, 0xf0, 0x16, 0x5f, 0xe4, 0x76, 0x29, 0x50, 0xb1, 0x19, 0xb7, 0x02, 0xe3,
                                                                                0x7a, 0xa9, 0xd3, 0x3b, 0x38, 0x3f, 0x22, 0xd4, 0x67, 0xf1, 0x0c, 0x7d, 0x80, 0xf5, 0x19, 0xbd, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_0       { 0x3c, 0xa9, 0x0e, 0x53, 0x68, 0x54, 0x15, 0x06, 0x9f, 0x3f, 0x59, 0xcc, 0x93, 0xd0, 0xb7, 0xe0,
                                                                                0xdd, 0x93, 0x54, 0x3d, 0x0e, 0xc7, 0xca, 0xf7, 0x66, 0x67, 0xa5, 0x3d, 0x83, 0x4c, 0xe5, 0x45,
                                                                                0x31, 0x52, 0xe4, 0x7b, 0x34, 0xe8, 0x31, 0xc7, 0x61, 0x93, 0x40, 0x96, 0x2a, 0x0b, 0x14, 0x79,
                                                                                0xd3, 0xd5, 0xb3, 0x4f, 0xc0, 0x7f, 0x24, 0xe4, 0x2c, 0x50, 0x15, 0x4a, 0x03, 0xaf, 0x71, 0xc2, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_1       { 0x9a, 0xc0, 0xb1, 0xb1, 0xd1, 0x9d, 0xef, 0x8d, 0x92, 0x86, 0x0e, 0x65, 0xcd, 0x6c, 0xa6, 0x4e,
                                                                                0x03, 0x0c, 0x72, 0xbc, 0xbd, 0xad, 0x22, 0xbb, 0xdc, 0x94, 0x37, 0x7d, 0x2c, 0x9a, 0x9e, 0xe8,
                                                                                0xa4, 0x90, 0xf2, 0x4d, 0x95, 0xd7, 0x1e, 0x45, 0x99, 0xac, 0xfc, 0x1f, 0x2c, 0xf3, 0x0a, 0x4c,
                                                                                0x7e, 0xd4, 0x0b, 0xc5, 0xbc, 0xa8, 0x56, 0x3e, 0xbb, 0xa3, 0xdd, 0x74, 0x91, 0x05, 0x01, 0x85, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_2       { 0xcd, 0xf9, 0xaa, 0xe1, 0x0d, 0x98, 0x18, 0xc2, 0x0c, 0xaa, 0x5a, 0x3d, 0x29, 0x7e, 0x93, 0x74,
                                                                                0x46, 0xbc, 0x83, 0xfa, 0x87, 0xa8, 0x61, 0x67, 0x30, 0x51, 0x48, 0x19, 0x0c, 0xf3, 0xc6, 0x0f,
                                                                                0x57, 0x80, 0x80, 0x64, 0x0e, 0xc7, 0x38, 0x94, 0x0b, 0x6e, 0x1d, 0xb2, 0xc4, 0xbd, 0x5f, 0x15,
                                                                                0xd1, 0xc4, 0xef, 0x34, 0xa7, 0xc4, 0xfe, 0xa8, 0xfa, 0xf1, 0x8a, 0x6b, 0x34, 0x8f, 0xc5, 0x61, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a0             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x01,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
                                                                                0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
                                                                                0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
                                                                                0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
                                                                                0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
                                                                                0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
                                                                                0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a1             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x01,
                                                                                0x00, 0x00, 0x00, 0x70,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
                                                                                0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
                                                                                0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
                                                                                0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
                                                                                0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
                                                                                0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
                                                                                0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a2             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x01,
                                                                                0x00, 0x00, 0x00, 0xe0,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
                                                                                0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
                                                                                0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
                                                                                0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
                                                                                0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
                                                                                0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
                                                                                0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b0             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x01,
                                                                                0x00, 0x00, 0x01, 0x50,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
                                                                                0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
                                                                                0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
                                                                                0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
                                                                                0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
                                                                                0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
                                                                                0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b1             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x01,
                                                                                0x00, 0x00, 0x01, 0xc0,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
                                                                                0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
                                                                                0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
                                                                                0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
                                                                                0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
                                                                                0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
                                                                                0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b2             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x01,
                                                                                0x00, 0x00, 0x02, 0x30,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
                                                                                0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
                                                                                0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
                                                                                0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
                                                                                0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
                                                                                0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
                                                                                0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, };

    SHA512::SHA512_T<packet_size>   sha_512_0{};
    SHA512::SHA512_T<packet_size>   sha_512_1{};
    SHA512::SHA512_T<packet_size>   sha_512_2{};
    SHA512::SHA512_T<packet_size>   sha_512_a{};
    SHA512::SHA512_T<packet_size>   sha_512_b{};

    SHA512::calculate(buffer_a0, sha_512_a, true);
    SHA512::calculate(buffer_a1, sha_512_a, false);
    SHA512::calculate(buffer_a2, sha_512_a, false);

    SHA512::calculate(buffer_b0, sha_512_b, true);
    SHA512::calculate(buffer_b1, sha_512_b, false);
    SHA512::calculate(buffer_b2, sha_512_b, false);

    SHA512::calculate(buffer_a0, sha_512_0, true);
    SHA512::calculate(buffer_b0, sha_512_0, false);

    SHA512::calculate(buffer_a1, sha_512_1, true);
    SHA512::calculate(buffer_b1, sha_512_1, false);

    SHA512::calculate(buffer_a2, sha_512_2, true);
    SHA512::calculate(buffer_b2, sha_512_2, false);

    if (memcmp(sha_512_a.Data, expected_hash_a, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_b.Data, expected_hash_b, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_0.Data, expected_hash_0, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_1.Data, expected_hash_1, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_2.Data, expected_hash_2, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_calculate_frame_2()
{
    constexpr uint32_t                                  packet_size         = 128u;
    constexpr uint32_t                                  columns             = 3u;
    constexpr uint32_t                                  rows                = 2u;

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_a       { 0xa6, 0xf2, 0xdc, 0xeb, 0x59, 0x15, 0xea, 0x6d, 0xe5, 0xde, 0x64, 0xae, 0x31, 0x1a, 0x2c, 0x9e,
                                                                                0x47, 0xeb, 0x94, 0xfc, 0xb9, 0x7f, 0x4d, 0xd1, 0xb3, 0xe5, 0xcc, 0x0e, 0x6f, 0xea, 0xce, 0xfd,
                                                                                0x7a, 0x5b, 0x32, 0x7c, 0x2a, 0x19, 0x18, 0xb9, 0xf8, 0x6c, 0x47, 0x05, 0x18, 0x72, 0x14, 0x1b,
                                                                                0x42, 0x41, 0x7d, 0x96, 0x1e, 0xb5, 0xf2, 0x69, 0xa3, 0xa4, 0x81, 0x15, 0x46, 0xc7, 0x5c, 0x5f, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_b       { 0x08, 0xa0, 0x47, 0x4e, 0x63, 0x59, 0xd4, 0x3a, 0xd0, 0x3e, 0xac, 0x12, 0xfe, 0xa1, 0x86, 0xf9,
                                                                                0x9d, 0x70, 0x34, 0x48, 0xfe, 0x0e, 0x6a, 0xe1, 0x18, 0x18, 0xed, 0xfc, 0x63, 0x0c, 0x56, 0xab,
                                                                                0x78, 0xcd, 0xc5, 0x10, 0x16, 0xae, 0x67, 0xb9, 0xc2, 0xe2, 0xe9, 0xa9, 0xf4, 0x35, 0x8b, 0x87,
                                                                                0x8d, 0xed, 0xcf, 0xd7, 0x26, 0x01, 0x59, 0xc6, 0x9e, 0xa9, 0x69, 0x20, 0xe1, 0xf4, 0x38, 0x86, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_0       { 0xa3, 0xb7, 0xe4, 0x75, 0xae, 0x9f, 0xd9, 0x5b, 0x1c, 0x08, 0x77, 0xc2, 0x20, 0xb1, 0xa7, 0x39,
                                                                                0xe8, 0xfe, 0x2d, 0x05, 0xb1, 0x3a, 0x10, 0x09, 0x5d, 0x15, 0x4d, 0xc7, 0xa6, 0x0c, 0x3c, 0xdb,
                                                                                0x01, 0x07, 0xdc, 0x1c, 0xc1, 0x98, 0xca, 0x91, 0x85, 0x9c, 0x38, 0x84, 0x77, 0x62, 0xfc, 0xa5,
                                                                                0xca, 0xd6, 0x6c, 0x89, 0x35, 0xc0, 0xd5, 0xa1, 0xd4, 0xa9, 0xdc, 0x29, 0x7e, 0xd3, 0xd4, 0xff, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_1       { 0x9a, 0x7d, 0x45, 0x6c, 0x01, 0x9b, 0x50, 0x1c, 0xfc, 0xef, 0x65, 0x8f, 0x82, 0x3b, 0x9f, 0xe0,
                                                                                0xd2, 0xe8, 0xc2, 0x3a, 0xf0, 0x2a, 0xed, 0x77, 0x10, 0xfc, 0x44, 0xed, 0x5e, 0xec, 0xd3, 0x37,
                                                                                0x2e, 0xc5, 0x7a, 0xe0, 0x37, 0x22, 0xaa, 0x81, 0x24, 0x45, 0xd2, 0xbf, 0x7e, 0xd1, 0x6c, 0xb6,
                                                                                0x2e, 0xe0, 0x26, 0x2b, 0x7b, 0xf5, 0x1e, 0x07, 0x7b, 0x5a, 0xf1, 0x1c, 0x05, 0xa1, 0x37, 0x5a, };

    SHA512::SHA512_T<packet_size>::DATA_T               expected_hash_2       { 0xc4, 0xe1, 0x2f, 0x42, 0x7c, 0x1d, 0xd1, 0x54, 0xb0, 0x3b, 0xd5, 0x44, 0x8c, 0x03, 0xad, 0x77,
                                                                                0xb8, 0x91, 0xb0, 0x69, 0x10, 0x98, 0x51, 0xf8, 0xc0, 0x2e, 0x10, 0x96, 0xce, 0xcc, 0x01, 0x5f,
                                                                                0x6c, 0x11, 0x26, 0x2d, 0x5c, 0x20, 0x66, 0x05, 0x94, 0x43, 0xba, 0x95, 0x57, 0x96, 0x02, 0x9d,
                                                                                0xe4, 0x76, 0x39, 0xbc, 0x41, 0x2e, 0x35, 0x51, 0x04, 0x48, 0x24, 0x19, 0x17, 0x0f, 0x35, 0xe5, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a0             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x02,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                                                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                                                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                                                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                                                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                                                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                                                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a1             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x02,
                                                                                0x00, 0x00, 0x00, 0x70,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                                                0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                                                0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                                                0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                                                0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                                                0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                                                0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, };

    BUFFER::BUFFER_T<packet_size>                       buffer_a2             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x02,
                                                                                0x00, 0x00, 0x00, 0xe0,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
                                                                                0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
                                                                                0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
                                                                                0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
                                                                                0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
                                                                                0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
                                                                                0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b0             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x02,
                                                                                0x00, 0x00, 0x01, 0x50,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
                                                                                0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
                                                                                0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
                                                                                0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
                                                                                0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
                                                                                0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
                                                                                0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b1             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x02,
                                                                                0x00, 0x00, 0x01, 0xc0,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                                                                                0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                                                                                0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                                                                                0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                                                                                0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                                                                                0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                                                                                0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, };

    BUFFER::BUFFER_T<packet_size>                       buffer_b2             { 0x00, 0x00, 0x00, 0x00,
                                                                                0x00, 0x00, 0x00, 0x02,
                                                                                0x00, 0x00, 0x02, 0x30,
                                                                                0x00, 0x00, 0x00, 0x00,
                                                                                0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
                                                                                0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
                                                                                0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
                                                                                0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
                                                                                0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
                                                                                0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
                                                                                0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, };

    SHA512::SHA512_T<packet_size>   sha_512_0{};
    SHA512::SHA512_T<packet_size>   sha_512_1{};
    SHA512::SHA512_T<packet_size>   sha_512_2{};
    SHA512::SHA512_T<packet_size>   sha_512_a{};
    SHA512::SHA512_T<packet_size>   sha_512_b{};

    SHA512::calculate(buffer_a0, sha_512_a, true);
    SHA512::calculate(buffer_a1, sha_512_a, false);
    SHA512::calculate(buffer_a2, sha_512_a, false);

    SHA512::calculate(buffer_b0, sha_512_b, true);
    SHA512::calculate(buffer_b1, sha_512_b, false);
    SHA512::calculate(buffer_b2, sha_512_b, false);

    SHA512::calculate(buffer_a0, sha_512_0, true);
    SHA512::calculate(buffer_b0, sha_512_0, false);

    SHA512::calculate(buffer_a1, sha_512_1, true);
    SHA512::calculate(buffer_b1, sha_512_1, false);

    SHA512::calculate(buffer_a2, sha_512_2, true);
    SHA512::calculate(buffer_b2, sha_512_2, false);

    if (memcmp(sha_512_a.Data, expected_hash_a, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_b.Data, expected_hash_b, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_0.Data, expected_hash_0, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_1.Data, expected_hash_1, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (memcmp(sha_512_2.Data, expected_hash_2, sizeof(SHA512::SHA512_T<packet_size>::LENGTH_DATA)))
    {
        fprintf(stderr, "%s:%d:%s: Incorrect hash\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


int main(int argc, char** argv)
{
    if (!test_rotl())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_rotr())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_shr())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_sigma_0())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_sigma_1())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_sum_0())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_sum_1())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_ch())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_maj())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_steps_1())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_steps_2())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_all_1())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_all_2())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_many())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_frame_0())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_frame_1())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_calculate_frame_2())
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
