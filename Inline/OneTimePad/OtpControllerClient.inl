
#include "Base/Endianness.h"
#include "Base/UtilsPgm.h"


namespace ONETIMEPAD
{
    namespace
    {
        uint8_t* _data_input    = nullptr;
        uint8_t* _data_output   = nullptr;
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool OtpControllerClient<PacketSize, Width, Height>::initialize_client(AES::KEY256& InitialKeyAes, AES::WORDS& InitialKeyOtp, uint16_t Port, std::string Address)
    {
        return this->_manager.initialize(InitialKeyAes, InitialKeyOtp, Port, Address);
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool OtpControllerClient<PacketSize, Width, Height>::communicate(std::string& Filename)
    {
        uint32_t width   = 0u;
        uint32_t height  = 0u;
        uint32_t maximum = 0u;
        uint32_t offset  = 0u;

        if (!UtilsPgm::read(&_data_output, width, height, maximum, &_data_input, Filename))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read file\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        while (offset < width * height)
        {
            BUFFER::BUFFER_T<PacketSize> buffer{};

            uint32_t size = width * height - offset < sizeof(BUFFER::BUFFER_T<PacketSize>::Data) ? width * height - offset : sizeof(BUFFER::BUFFER_T<PacketSize>::Data);

            memcpy(buffer.Data, &_data_output[offset], size);

            Endianness::hton32(buffer.Frame,  this->_frame_number);
            Endianness::hton32(buffer.Offset, offset);

            if (!this->_manager.transmit(buffer))
            {
                fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            offset += size;
        }

        this->_frame_number++;

        return true;
    }
}
