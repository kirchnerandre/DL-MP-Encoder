
#include <stdint.h>
#include <stdio.h>
#include <string>

#include "Base/Aes.h"
#include "Base/UtilsParser.h"


namespace AES
{
    bool schedule_key  (KEY256& Key);
    bool schedule_words(KEY256& Key, WORDS& Words);
}


bool test_scheduling_key256(AES::KEY256 KeyRaw, AES::KEY256 KeyExpected)
{
    if (!AES::schedule_key(KeyRaw))
    {
        fprintf(stderr, "%s:%d:%s: Failed to schedule key\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Round != KeyExpected.Round)
    {
        fprintf(stderr, "%s:%d:%s: Invalid round\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word0 != KeyExpected.Word0)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 0\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word1 != KeyExpected.Word1)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 1\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word2 != KeyExpected.Word2)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 2\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word3 != KeyExpected.Word3)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 3\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word4 != KeyExpected.Word4)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 4\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word5 != KeyExpected.Word5)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 5\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word6 != KeyExpected.Word6)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 6\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (KeyRaw.Word7 != KeyExpected.Word7)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 7\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_scheduling_key256(std::string Filename)
{
    bool    ret_val = true;
    FILE*   file    = fopen(Filename.c_str(), "r");

    if (!file)
    {
        fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    while (1)
    {
        AES::KEY256 key_raw     {};
        AES::KEY256 key_expected{};

        if (Utils::read_aes_key(key_raw, key_expected, file))
        {
            if (!test_scheduling_key256(key_raw, key_expected))
            {
                fprintf(stderr, "%s:%d:%s: Failed to calculate key\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else
        {
            break;
        }
    }

terminate:
    if (file)
    {
        fclose(file);
    }

    return ret_val;
}


bool test_scheduling_words256(AES::KEY256 Key, AES::WORDS WordsInitial, AES::WORDS WordsExpected)
{
    if (!AES::schedule_words(Key, WordsInitial))
    {
        fprintf(stderr, "%s:%d:%s: Failed to schedule words\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word0 != WordsExpected.Word0)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 0\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word1 != WordsExpected.Word1)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 1\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word2 != WordsExpected.Word2)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 2\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word3 != WordsExpected.Word3)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 3\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_scheduling_words256(std::string Filename)
{
    bool    ret_val = true;
    FILE*   file    = fopen(Filename.c_str(), "r");

    if (!file)
    {
        fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    while (1)
    {
        AES::KEY256 key_raw       {};
        AES::WORDS  words_raw     {};
        AES::WORDS  words_expected{};

        if (Utils::read_aes_data(key_raw, words_raw, words_expected, file))
        {
            if (!test_scheduling_words256(key_raw, words_raw, words_expected))
            {
                fprintf(stderr, "%s:%d:%s: Failed to encode word\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else
        {
            break;
        }
    }

terminate:
    if (file)
    {
        fclose(file);
    }

    return ret_val;
}


bool test_encoding256(AES::KEY256 Key, AES::WORDS WordsInitial, AES::WORDS WordsExpected)
{
    if (!AES::encode(Key, WordsInitial))
    {
        fprintf(stderr, "%s:%d:%s: Failed to encrypt\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word0 != WordsExpected.Word0)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 0\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word1 != WordsExpected.Word1)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 1\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word2 != WordsExpected.Word2)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 2\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (WordsInitial.Word3 != WordsExpected.Word3)
    {
        fprintf(stderr, "%s:%d:%s: Invalid word 3\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    return true;
}


bool test_encoding256(std::string Filename)
{
    bool    ret_val = true;
    FILE*   file    = fopen(Filename.c_str(), "r");

    if (!file)
    {
        fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
        ret_val = false;
        goto terminate;
    }

    while (1)
    {
        AES::KEY256 key_raw       {};
        AES::WORDS  words_raw     {};
        AES::WORDS  words_expected{};

        if (Utils::read_aes_data(key_raw, words_raw, words_expected, file))
        {
            if (!test_encoding256(key_raw, words_raw, words_expected))
            {
                fprintf(stderr, "%s:%d:%s: Failed to encode word\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }
        }
        else
        {
            break;
        }
    }

terminate:
    if (file)
    {
        fclose(file);
    }

    return ret_val;
}


int main(int argc, char** argv)
{
    if (!test_scheduling_key256("./Data/Input/aes-256-key.txt"))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_scheduling_words256("./Data/Input/aes-256-data.txt"))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    if (!test_encoding256("./Data/Input/aes-256-full.txt"))
    {
        fprintf(stderr, "%s:%d:%s: Test failed\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }

    return 0;
}
