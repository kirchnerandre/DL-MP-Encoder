
#include "Base/UtilsPgm.h"


namespace MULTIPATH
{
    namespace
    {
        uint8_t* _data_input    = nullptr;
        uint8_t* _data_output   = nullptr;
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    bool MpControllerClient<PacketSize, ImageWidth, ImageHeight>::initialize_client(uint16_t        Port0,
                                                                                    uint16_t        Port1,
                                                                                    uint16_t        Port2,
                                                                                    std::string     Address0,
                                                                                    std::string     Address1,
                                                                                    std::string     Address2,
                                                                                    AES::KEY256&    InitialKeyAes,
                                                                                    AES::WORDS&     InitialKeyOtp)
    {
        this->_enabled_0 = Port0 > 0u;
        this->_enabled_1 = Port1 > 0u;
        this->_enabled_2 = Port2 > 0u;

        return this->_manager.initialize(InitialKeyAes, InitialKeyOtp, Port0, Port1, Port2, Address0, Address1, Address2);
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    bool MpControllerClient<PacketSize, ImageWidth, ImageHeight>::communicate(std::string& Filename)
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

            uint32_t size = width * height - offset < buffer.LENGTH_DATA ? width * height - offset : buffer.LENGTH_DATA;

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
