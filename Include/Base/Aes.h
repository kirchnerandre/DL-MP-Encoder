
#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>

namespace AES
{
    struct WORDS
    {
        uint32_t Word0;
        uint32_t Word1;
        uint32_t Word2;
        uint32_t Word3;
    };

    struct KEY256
    {
        uint32_t    Round;
        uint32_t    Word0;
        uint32_t    Word1;
        uint32_t    Word2;
        uint32_t    Word3;
        uint32_t    Word4;
        uint32_t    Word5;
        uint32_t    Word6;
        uint32_t    Word7;
    };

    /**
     * Encodes Words using the AES-256 algorithm and the 256-bits Key parameter.
     * @param Key 256-bit key t be used for encryption. Key.Round should be set to ZERO.
     * @param Words Output parameter containing initially the raw data, and then the encrypted data.
     * @return True emcoding succeeded, and false otherwise.
    */
    bool encode(KEY256& Key, WORDS& Words);
}

#endif // _AES_H_
