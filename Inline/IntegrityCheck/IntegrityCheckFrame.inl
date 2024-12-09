
#include <stdio.h>

#include "Base/Endianness.h"
#include "Base/Sha512.h"


namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    void IntegrityCheckFrame<PacketSize, Width, Height, HashColumns, HashRows>::process_column(uint32_t Offset, Statistics::STATISTICS_T& Statistics)
    {
        if (!this->_grid_hashes_columns[Offset])
        {
            return;
        }

        for (uint32_t i = 0u; i < HashRows; i++)
        {
            if (this->_grid_buffers[HashColumns * i + Offset] == STATE::EMPTY)
            {
                return;
            }
        }

        this->_grid_hashes_columns[Offset] = false;

        SHA512::SHA512_T<PacketSize> sha_512{};

        for (uint32_t i = 0; i < HashRows; i++)
        {
            if (!i)
            {
                SHA512::calculate(this->_buffers[HashColumns * i + Offset], sha_512, true);
            }
            else
            {
                SHA512::calculate(this->_buffers[HashColumns * i + Offset], sha_512, false);
            }
        }

        if (!memcmp(sha_512.Data, this->_sha512_columns[Offset].Data, SHA512::SHA512_T<PacketSize>::LENGTH_DATA))
        {
            Statistics.PacketHashTypeColumnGood++; 

            for (uint32_t i = 0; i < HashRows; i++)
            {
                if (this->_grid_buffers[HashColumns * i + Offset] == STATE::AVAILABLE)
                {
                    this->_grid_buffers[HashColumns * i + Offset] = STATE::PROCESSED;

                    Statistics.PacketDataGood++;

                    memcpy(&this->_FrameData[(HashColumns * i + Offset) * BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA], this->_buffers[HashColumns * i + Offset].Data, BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA);
                }
            }
        }
        else
        {
            Statistics.PacketHashTypeColumnBad++; 
        }
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    void IntegrityCheckFrame<PacketSize, Width, Height, HashColumns, HashRows>::process_row(uint32_t Offset, Statistics::STATISTICS_T& Statistics)
    {
        if (!this->_grid_hashes_rows[Offset])
        {
            return;
        }

        for (uint32_t i = 0u; i < HashColumns; i++)
        {
            if (this->_grid_buffers[HashColumns * Offset + i] == STATE::EMPTY)
            {
                return;
            }
        }

        this->_grid_hashes_rows[Offset] = false;

        SHA512::SHA512_T<PacketSize> sha_512{};

        for (uint32_t i = 0; i < HashColumns; i++)
        {
            if (!i)
            {
                SHA512::calculate(this->_buffers[HashColumns * Offset + i], sha_512, true);
            }
            else
            {
                SHA512::calculate(this->_buffers[HashColumns * Offset + i], sha_512, false);
            }
        }

        if (!memcmp(sha_512.Data, this->_sha512_rows[Offset].Data, SHA512::SHA512_T<PacketSize>::LENGTH_DATA))
        {
            Statistics.PacketHashTypeRowGood++; 

            for (uint32_t i = 0; i < HashColumns; i++)
            {
                if (this->_grid_buffers[HashColumns * Offset + i] == STATE::AVAILABLE)
                {
                    this->_grid_buffers[HashColumns * Offset + i] = STATE::PROCESSED;

                    Statistics.PacketDataGood++;

                    memcpy(&this->_FrameData[(HashColumns * Offset + i) * BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA], this->_buffers[HashColumns * Offset + i].Data, BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA);
                }
            }
        }
        else
        {
            Statistics.PacketHashTypeRowBad++; 
        }
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckFrame<PacketSize, Width, Height, HashColumns, HashRows>::set(BUFFER::BUFFER_T<PacketSize>& Buffer, Statistics::STATISTICS_T& Statistics)
    {
        Statistics.PacketDataTotal++;

        uint32_t frame_offset = Endianness::ntoh32(Buffer.Offset);
        uint32_t frame_number = Endianness::ntoh32(Buffer.Frame);

        if (this->_FrameFirst)
        {
            this->_FrameNumber  = frame_number;
            this->_FrameFirst   = false;
        }

        if (this->_FrameNumber != frame_number)
        {
            fprintf(stderr, "%s:%d:%s: Invalid frame number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (frame_offset + Buffer.LENGTH_DATA > this->_FrameSize)
        {
            fprintf(stderr, "%s:%d:%s: Invalid offset\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        uint32_t grid_column = (frame_offset / BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA) % HashColumns;
        uint32_t grid_row    = (frame_offset / BUFFER::BUFFER_T<PacketSize>::LENGTH_DATA) / HashColumns;

        if (grid_column >= HashColumns)
        {
            fprintf(stderr, "%s:%d:%s: Invalid hash column\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (grid_row >= HashRows)
        {
            fprintf(stderr, "%s:%d:%s: Invalid hash row\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (this->_grid_buffers[grid_row * HashColumns + grid_column] != STATE::EMPTY)
        {
            fprintf(stderr, "%s:%d:%s: Invalid duplicated hash\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        memcpy(&this->_buffers[frame_offset / Buffer.LENGTH_DATA], &Buffer, PacketSize);

        this->_grid_buffers[grid_row * HashColumns + grid_column] = STATE::AVAILABLE;

        process_column(grid_column, Statistics);
        process_row   (grid_row,    Statistics);

        return true;
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckFrame<PacketSize, Width, Height, HashColumns, HashRows>::set(SHA512::SHA512_T<PacketSize>& Sha512, Statistics::STATISTICS_T& Statistics)
    {
        uint32_t number = Endianness::ntoh32(Sha512.Frame);
        uint32_t offset = Endianness::ntoh32(Sha512.Offset);
        uint32_t type   = Endianness::ntoh32(Sha512.Type);

        if (this->_FrameFirst)
        {
            this->_FrameNumber  = number;
            this->_FrameFirst   = false;
        }

        if (this->_FrameNumber != number)
        {
            fprintf(stderr, "%s:%d:%s: Invalid frame number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if ((type == SHA512::SHA512_T<PacketSize>::TYPE_COLUMN) && (offset >= HashColumns))
        {
            fprintf(stderr, "%s:%d:%s: Invalid column offset\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if ((type == SHA512::SHA512_T<PacketSize>::TYPE_ROW) && (offset >= HashRows))
        {
            fprintf(stderr, "%s:%d:%s: Invalid row offset\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if ((type != SHA512::SHA512_T<PacketSize>::TYPE_COLUMN) && (type != SHA512::SHA512_T<PacketSize>::TYPE_ROW))
        {
            fprintf(stderr, "%s:%d:%s: Invalid hash type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (type == SHA512::SHA512_T<PacketSize>::TYPE_COLUMN)
        {
            Statistics.PacketHashTypeColumnTotal++;

            this->_grid_hashes_columns[offset] = true;

            memcpy(&this->_sha512_columns[offset], &Sha512, PacketSize);

            process_column(offset, Statistics);
        }
        else if (type == SHA512::SHA512_T<PacketSize>::TYPE_ROW)
        {
            Statistics.PacketHashTypeRowTotal++;

            this->_grid_hashes_rows[offset] = true;

            memcpy(&this->_sha512_rows[offset], &Sha512, PacketSize);

            process_row(offset, Statistics);
        }

        return true;
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckFrame<PacketSize, Width, Height, HashColumns, HashRows>::get(uint8_t* Data, uint32_t Frame)
    {
        if (Frame != this->_FrameNumber)
        {
            fprintf(stderr, "%s:%d:%s: Invalid frame number\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        memcpy(Data, this->_FrameData, Width * Height);

        this->_FrameFirst   = true;
        this->_FrameNumber  = 0u;

        memset(this->_grid_buffers,         static_cast<int>(STATE::EMPTY), sizeof(this->_grid_buffers));
        memset(this->_grid_hashes_columns,  false,                          sizeof(this->_grid_hashes_columns));
        memset(this->_grid_hashes_rows,     false,                          sizeof(this->_grid_hashes_rows));

        return true;
    }
}
