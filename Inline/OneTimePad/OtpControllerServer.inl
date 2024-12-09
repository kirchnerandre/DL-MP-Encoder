
namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool OtpControllerServer<PacketSize, Width, Height>::initialize_server(AES::KEY256& InitialKeyAes, AES::WORDS& InitialKeyOtp, uint16_t Port, uint32_t Size)
    {
        if (!this->_manager.initialize(InitialKeyAes, InitialKeyOtp, Port))
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


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    bool OtpControllerServer<PacketSize, Width, Height>::communicate()
    {
        BUFFER::BUFFER_T<PacketSize> buffer{};

        if (!this->_manager.receive(buffer))
        {
            fprintf(stderr, "%s:%d:%s: Failed to communicate\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!this->_frames.set(buffer))
        {
            fprintf(stderr, "%s:%d:%s: Failed to set\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    OtpFrames<PacketSize, Width, Height>& OtpControllerServer<PacketSize, Width, Height>::get_frames()
    {
        return this->_frames;
    }
}
