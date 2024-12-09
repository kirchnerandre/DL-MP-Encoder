
#ifndef _CRC_H_
#define _CRC_H_

#include <stdint.h>

#include "Base/Buffer.h"

namespace Crc
{
    /**
     * Calculates the CRC of byte stream of the BUFFER_T structure using the respective NR polynomial specified by the
     * parameter Mode, and updates the byte stream of BUFFER_T itself. The last N bits of the byte stream of BUFFER_T
     * should be 0s, where N is the size of the CRC polynomial minus 1.
     * @param Buffer BUFFER_T structure.
     * @param CrcPolynomial The CRC polynomial. This are the 32 least significant bits of the CRC polynomial. 1 is
                            internally added as the most significant bit bring the size of 33 bits.
    */
    template<uint32_t PacketSize>
    void calculate(BUFFER::BUFFER_T<PacketSize>& Buffer, uint32_t CrcPolynomial);

    /**
     * Calculates the CRC of byte stream of the BUFFER_T structure using the respective NR polynomial specified by the
     * parameter Mode, and verifies it is correct.
     * @param Buffer BUFFER_T structure.
     * @param CrcPolynomial The CRC polynomial.This are the 32 least significant bits of the CRC polynomial. 1 is
                            internally added as the most significant bit bring the size of 33 bits.
     * @return True if operation was successful, and false otherwise.
    */
    template<uint32_t PacketSize>
    bool verify(BUFFER::BUFFER_T<PacketSize>& Buffer, uint32_t CrcPolynomial);
}

#include "Base/Crc.inl"

#endif // _CRC_H_
