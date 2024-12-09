
namespace MULTIPATH
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    bool MpControllerServer<PacketSize, ImageWidth, ImageHeight>::initialize_server(uint16_t Port0,
                                                                                    uint16_t Port1,
                                                                                    uint16_t Port2,
                                                                                    uint32_t Size)
    {
        this->_enabled_0 = Port0 > 0u;
        this->_enabled_1 = Port1 > 0u;
        this->_enabled_2 = Port2 > 0u;

        AES::KEY256 initial_key_aes{};
        AES::WORDS  initial_key_otp{};

        if (!this->_manager.initialize(initial_key_aes, initial_key_otp, Port0, Port1, Port2))
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


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    bool MpControllerServer<PacketSize, ImageWidth, ImageHeight>::communicate()
    {
        TYPE_SINGLE                     type = TYPE_SINGLE::EMPTY;
        BUFFER::BUFFER_T<PacketSize>    buffer{};

        if (!this->_manager.receive(buffer, type))
        {
            fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!this->_frames.set(buffer, type))
        {
            fprintf(stderr, "%s:%d:%s: Failed to set\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight>
    MpFrames<PacketSize, ImageWidth, ImageHeight>& MpControllerServer<PacketSize, ImageWidth, ImageHeight>::get_frames()
    {
        return this->_frames;
    }
}
