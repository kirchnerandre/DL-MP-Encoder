
namespace INTEGRITYCHECK
{
    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckController<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>::konnect(uint32_t Timeout)
    {
        while (1)
        {
            if (this->_manager.konnect())
            {
                fprintf(stderr, "%s:%d:%s: Succeed connecting\n", __FILE__, __LINE__, __FUNCTION__);
                return true;
            }
            else if (!--Timeout)
            {
                fprintf(stderr, "%s:%d:%s: Failed to connect\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
            else
            {
                fprintf(stderr, "%s:%d:%s: Trying to connect\n", __FILE__, __LINE__, __FUNCTION__);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
            }
        }
    }


    template<uint32_t PacketSize, uint32_t ImageWidth, uint32_t ImageHeight, uint32_t HashColumns, uint32_t HashRows>
    bool IntegrityCheckController<PacketSize, ImageWidth, ImageHeight, HashColumns, HashRows>::deinitialize()
    {
        return this->_manager.deinitialize();
    }
}
