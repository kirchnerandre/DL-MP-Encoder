
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <string.h>


namespace UtilsPgm
{
    namespace
    {
        void get_value(std::string& Value, uint8_t* DataInput, uint32_t& Offset)
        {
            constexpr uint8_t line_feed         = 0x0a;
            constexpr uint8_t carriage_return   = 0x0d;
            constexpr uint8_t space             = 0x20;

            while ((DataInput[Offset] == line_feed) || (DataInput[Offset] == carriage_return) || (DataInput[Offset] == space))
            {
                Offset++;
            }

            while ((DataInput[Offset] != line_feed) && (DataInput[Offset] != carriage_return) && (DataInput[Offset] != space))
            {
                Value += DataInput[Offset];
                Offset++;
            }
        }


        bool get_value(uint32_t& Value, uint8_t* DataInput, uint32_t& Offset)
        {
            std::string value;

            get_value(value, DataInput, Offset);

            try
            {
                Value = std::stoul(value);
            }
            catch(...)
            {
                fprintf(stderr, "%s:%d:%s: Failed to get value\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            return true;
        }
    }


    bool read(uint8_t* DataOutput, uint32_t& Width, uint32_t& Height, uint32_t& Maximum, uint8_t* DataInput)
    {
        std::string type;
        uint32_t    offset = 0u;

        if (!DataInput)
        {
            fprintf(stderr, "%s:%d:%s: Invalid parameter\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        get_value(type, DataInput, offset);

        if (type != std::string("P5"))
        {
fprintf(stderr, "%zu '%s'\n", type.length(), type.c_str());
fprintf(stderr, "%zu '%s'\n", std::string("P5").length(), std::string("P5").c_str());
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!get_value(Height, DataInput, offset))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read height\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!get_value(Width, DataInput, offset))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read width\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!get_value(Maximum, DataInput, offset))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read maximum\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (DataOutput)
        {
            memcpy(DataOutput, &DataInput[++offset], Width * Height);
        }

        return true;
    }


    bool read(uint8_t** DataOutput, uint32_t& Width, uint32_t& Height, uint32_t& Maximum, uint8_t** DataInput, std::string& Filename)
    {
        bool        ret_val             = true;
        bool        good_data_input     = false;
        bool        good_data_output    = false;
        uint8_t*    data_input          = nullptr;
        uint8_t*    data_output         = nullptr;
        int32_t     length_signed       = 0;
        uint32_t    length_unsigned     = 0u;
        FILE*       file                = nullptr;

        if (DataInput)
        {
            good_data_input     = *DataInput  ? true : false;
            data_input          = *DataInput;
        }

        if (DataOutput)
        {
            good_data_output    = *DataOutput ? true : false;
            data_output         = *DataOutput;
        }

        file = fopen(Filename.c_str(), "rb");

        if (!file)
        {
            fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (fseek(file, 0L, SEEK_END))
        {
            fprintf(stderr, "%s:%d:%s: Failed to seek end\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        length_signed = ftell(file);

        if (length_signed < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to seek end\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (fseek(file, 0, SEEK_SET))
        {
            fprintf(stderr, "%s:%d:%s: Failed to seek begin\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        length_unsigned = static_cast<uint32_t>(length_signed);

        if (data_input == nullptr)
        {
            data_input = new uint8_t[length_unsigned]{};
        }

        if (data_input == nullptr)
        {
            fprintf(stderr, "%s:%d:%s: Failed to allocate memory\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (fread(data_input, 1u, length_unsigned, file) != length_unsigned)
        {
            fprintf(stderr, "%s:%d:%s: Failed to read file\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (!read(nullptr, Width, Height, Maximum, data_input))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read data\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (data_output == nullptr)
        {
            data_output = new uint8_t[Width * Height]{};
        }

        if (data_output == nullptr)
        {
            fprintf(stderr, "%s:%d:%s: Failed to allocate memory\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (!read(data_output, Width, Height, Maximum, data_input))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read data\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (DataInput)
        {
            *DataInput = data_input;
        }

        if (DataOutput)
        {
            *DataOutput = data_output;
        }

    terminate:
        if (!DataInput)
        {
            delete[] data_input;
        }

        if (!DataOutput)
        {
            delete[] data_output;
        }

        if (file)
        {
            fclose(file);
        }

        return ret_val;
    }
}
