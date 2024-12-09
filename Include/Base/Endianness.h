
#ifndef _ENDIANNESS_H_
#define _ENDIANNESS_H_

#include <stdint.h>

namespace Endianness
{

    /**
     * Converts 1-byte input in host-byte-order to 1-byte output in network-byte-order.
     * @param Output 1-byte unsigned output in network-byte-order
     * @param Input 1-byte unsigned input data in host-byte-order
    */
    void hton8 (uint8_t* Output, uint8_t  Input);

    /**
     * Converts 2-byte input in host-byte-order to 2-byte output in network-byte-order.
     * @param Output 2-byte unsigned output in network-byte-order
     * @param Input 2-byte unsigned input data in host-byte-order
    */
    void hton16(uint8_t* Output, uint16_t Input);

    /**
     * Converts 4-byte input in host-byte-order to 4-byte output in network-byte-order.
     * @param Output 4-byte unsigned output in network-byte-order
     * @param Input 4-byte unsigned input data in host-byte-order
    */
    void hton32(uint8_t* Output, uint32_t Input);

    /**
     * Converts 8-byte input in host-byte-order to 8-byte output in network-byte-order.
     * @param Output 8-byte unsigned output in network-byte-order
     * @param Input 8-byte unsigned input data in host-byte-order
    */
    void hton64(uint8_t* Output, uint64_t Input);

    /**
     * Converts 1-byte input in network-byte-order to 1-byte output in host-byte-order.
     * @param Input 1-byte unsigned input data in network-byte-order
     * @return 1-byte unsigned output in host-byte-order
    */
    uint8_t  ntoh8 (uint8_t* Input);

    /**
     * Converts 2-byte input in network-byte-order to 2-byte output in host-byte-order.
     * @param Input 2-byte unsigned input data in network-byte-order
     * @return 2-byte unsigned output in host-byte-order
    */
    uint16_t ntoh16(uint8_t* Input);

    /**
     * Converts 4-byte input in network-byte-order to 4-byte output in host-byte-order.
     * @param Input 4-byte unsigned input data in network-byte-order
     * @return 4-byte unsigned output in host-byte-order
    */
    uint32_t ntoh32(uint8_t* Input);

    /**
     * Converts 8-byte input in network-byte-order to 8-byte output in host-byte-order.
     * @param Input 8-byte unsigned input data in network-byte-order
     * @return 8-byte unsigned output in host-byte-order
    */
    uint64_t ntoh64(uint8_t* Input);

}

#endif // _ENDIANNESS_H_
