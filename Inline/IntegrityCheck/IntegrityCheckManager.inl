
#include <stdio.h>


namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize>
    bool IntegrityCheckManager::transmit(PACKET::PACKET_T<PacketSize>& Packet)
    {
        if (this->_type == TYPE::Client)
        {
            bool ret_val = this->_network_client.transmit(Packet);

            return ret_val;
        }
        else if (this->_type == TYPE::Server)
        {
            return this->_network_server.transmit(Packet);
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
    }


    template<uint32_t PacketSize>
    bool IntegrityCheckManager::receive(PACKET::PACKET_T<PacketSize>& Packet)
    {
        if (this->_type == TYPE::Client)
        {
            if (!this->_network_client.receive(Packet))
            {
                return false;
            }
        }
        else if (this->_type == TYPE::Server)
        {
            if (!this->_network_server.receive(Packet))
            {
                return false;
            }
        }
        else
        {
            fprintf(stderr, "%s:%d:%s: Invalid type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        uint32_t header = Endianness::ntoh32(Packet.Dummy.Header);

        if ((header != PACKET::PACKET_TYPE_BUFFER) && (header != PACKET::PACKET_TYPE_HASH))
        {
            fprintf(stderr, "%s:%d:%s: Invalid packet type\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }
}
