
#include "Base/Endianness.h"
#include "Base/Sha512.h"
#include "Base/UtilsPgm.h"


namespace INTEGRITYCHECK
{
    namespace
    {
        uint8_t* _data_input    = nullptr;
        uint8_t* _data_output   = nullptr;
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckControllerClient<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>::initialize_client(uint16_t Port, std::string Address)
    {
        return this->_manager.initialize(Port, Address);
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckControllerClient<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>::communicate(std::string& Filename, Statistics::STATISTICS_T& Statistics)
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

        SHA512::SHA512_T<PacketSize>    sha_512_columns[HashColumns]{};
        SHA512::SHA512_T<PacketSize>    sha_512_row                 {};

        while (offset < width * height)
        {
            PACKET::PACKET_T<PacketSize> packet_buffer{};

            uint32_t size = width * height - offset <BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA ? width * height - offset :BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA;

            memcpy(packet_buffer.Buffer.Data, &_data_output[offset], size);

            Endianness::hton32(packet_buffer.Buffer.Header, PACKET::PACKET_TYPE_BUFFER);
            Endianness::hton32(packet_buffer.Buffer.Frame,  this->_frame_number);
            Endianness::hton32(packet_buffer.Buffer.Offset, offset);

            if (!this->_manager.transmit(packet_buffer))
            {
                fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            Statistics.PacketDataGood++;

            uint32_t column = (offset / BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA) % HashColumns;
            uint32_t row    = (offset / BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA) / HashColumns;

            if (!row)
            {
                SHA512::calculate(packet_buffer.Buffer, sha_512_columns[column], true);
            }
            else
            {
                SHA512::calculate(packet_buffer.Buffer, sha_512_columns[column], false);
            }

            if (row + 1u == HashRows)
            {
                PACKET::PACKET_T<PacketSize> packet_sha512{};

                memcpy(packet_sha512.Sha512.Data, &sha_512_columns[column].Data, SHA512::SHA512_T<PacketSize>::LENGTH_DATA);

                Endianness::hton32(packet_sha512.Sha512.Header,  PACKET::PACKET_TYPE_HASH);
                Endianness::hton32(packet_sha512.Sha512.Frame,   this->_frame_number);
                Endianness::hton32(packet_sha512.Sha512.Offset,  column);
                Endianness::hton32(packet_sha512.Sha512.Type,    SHA512::SHA512_T<PacketSize>::TYPE_COLUMN);

                if (!this->_manager.transmit(packet_sha512))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }

                Statistics.PacketHashTypeRowGood++;
            }

            if (!column)
            {
                SHA512::calculate(packet_buffer.Buffer, sha_512_row, true);
            }
            else
            {
                SHA512::calculate(packet_buffer.Buffer, sha_512_row, false);
            }

            if (column + 1u == HashColumns)
            {
                PACKET::PACKET_T<PacketSize> packet_sha512{};

                memcpy(packet_sha512.Sha512.Data, &sha_512_row.Data, SHA512::SHA512_T<PacketSize>::LENGTH_DATA);

                Endianness::hton32(packet_sha512.Sha512.Header,  PACKET::PACKET_TYPE_HASH);
                Endianness::hton32(packet_sha512.Sha512.Frame,   this->_frame_number);
                Endianness::hton32(packet_sha512.Sha512.Offset,  row);
                Endianness::hton32(packet_sha512.Sha512.Type,    SHA512::SHA512_T<PacketSize>::TYPE_ROW);

                if (!this->_manager.transmit(packet_sha512))
                {
                    fprintf(stderr, "%s:%d:%s: Failed to transmit\n", __FILE__, __LINE__, __FUNCTION__);
                    return false;
                }

                Statistics.PacketHashTypeColumnGood++;
            }

            offset += size;
        }

        this->_frame_number++;

        return true;
    }
}
