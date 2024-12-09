
#ifndef _UTILS_PGM_H_
#define _UTILS_PGM_H_

#include <stdint.h>
#include <string>

namespace UtilsPgm
{
    bool read(uint8_t*  DataOutput, uint32_t& Width, uint32_t& Height, uint32_t& Maximum, uint8_t*  DataInput);
    bool read(uint8_t** DataOutput, uint32_t& Width, uint32_t& Height, uint32_t& Maximum, uint8_t** DataInput, std::string & Filename);
}

#endif // _UTILS_PGM_H_
