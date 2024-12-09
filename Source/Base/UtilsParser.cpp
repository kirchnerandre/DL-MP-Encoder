
#include <stdio.h>
#include <stdint.h>
#include <string>

#include "Base/Aes.h"


namespace Utils
{
    namespace
    {
        bool read_dec(uint32_t& Value, FILE* File)
        {
            bool        valid = false;
            std::string value;

            while (1)
            {
                const int32_t symbol = getc(File);

                if (symbol == EOF)
                {
                    return false;
                }
                else if (('0' <= symbol) && (symbol <= '9'))
                {
                    value.append(1, symbol);
                    valid = true;
                }
                else if (valid)
                {
                    Value = std::stoul(value);
                    return true;
                }
            }
        }


        bool read_hex(uint32_t& Value, FILE* File)
        {
            bool        valid = false;
            std::string value;

            while (1)
            {
                const uint8_t symbol = static_cast<uint8_t>(getc(File));

                if (symbol == EOF)
                {
                    Value = std::stoul(value, nullptr, 16);
                    return false;
                }
                else if (('0' <= symbol) && (symbol <= '9'))
                {
                    value.append(1, symbol);
                    valid = true;
                }
                else if (('a' <= symbol) && (symbol <= 'f'))
                {
                    value.append(1, symbol);
                    valid = true;
                }
                else if (symbol == 'x')
                {
                    value.append(1, symbol);
                    valid = true;
                }
                else if (valid)
                {
                    Value = std::stoul(value, nullptr, 16);
                    return true;
                }
            }

            return true;
        }


        bool read_key(AES::KEY256& Key, FILE* File)
        {
            if (!read_dec(Key.Round, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read round\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word0, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 0\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word1, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 1\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word2, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 2\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word3, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 3\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word4, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 4\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word5, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 5\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word6, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 6\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Key.Word7, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 7\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            return true;
        }


        bool read_words(AES::WORDS& Words, FILE* File)
        {
            if (!read_hex(Words.Word0, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 0\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Words.Word1, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 1\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Words.Word2, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 2\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (!read_hex(Words.Word3, File))
            {
                fprintf(stderr, "%s:%d:%s: Failed to read word 3\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            return true;
        }
    }


    bool read_aes_data(AES::KEY256& KeyRaw, AES::WORDS& WordsRaw, AES::WORDS& WordsExpected, FILE* File)
    {
        if (!read_key(KeyRaw, File))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read raw key\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!read_words(WordsRaw, File))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read raw words\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!read_words(WordsExpected, File))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read expected words\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool read_aes_key(AES::KEY256& KeyRaw, AES::KEY256& KeyExpected, FILE* File)
    {
        if (!read_key(KeyRaw, File))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read raw key\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!read_key(KeyExpected, File))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read expected key\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }
}
