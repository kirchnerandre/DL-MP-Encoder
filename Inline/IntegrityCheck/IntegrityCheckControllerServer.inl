
namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckControllerServer<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>::initialize_server(uint16_t Port, uint32_t Size)
    {
        if (!this->_manager.initialize(Port))
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!this->_frames.initialize(Size))
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckControllerServer<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>::communicate(Statistics::STATISTICS_T& Statistics)
    {
        PACKET::PACKET_T<PacketSize> packet{};

        if (!this->_manager.receive(packet))
        {
            fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        uint32_t packet_type = Endianness::ntoh32(packet.Dummy.Header);

        if (packet_type == PACKET::PACKET_TYPE_BUFFER)
        {
            if (!this->_frames.set(packet.Buffer, Statistics))
            {
                fprintf(stderr, "%s:%d:%s: Failed to set\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }
        else if (packet_type == PACKET::PACKET_TYPE_HASH)
        {
            if (!this->_frames.set(packet.Sha512, Statistics))
            {
                fprintf(stderr, "%s:%d:%s: Failed to set\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    IntegrityCheckFrames<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>& IntegrityCheckControllerServer<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>::get_frames()
    {
        return this->_frames;
    }
}
