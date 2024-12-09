
#ifndef _UTILS_PARSER_H_
#define _UTILS_PARSER_H_

#include <stdio.h>

#include "Base/Aes.h"

namespace Utils
{
    bool read_aes_key(AES::KEY256& KeyRaw, AES::KEY256& KeyExpected, FILE* File);

    bool read_aes_data(AES::KEY256& KeyRaw, AES::WORDS& WordsRaw, AES::WORDS& WordsExpected, FILE* File);
}

#endif // _UTILS_PARSER_H_
