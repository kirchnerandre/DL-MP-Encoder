
#ifndef _OTP_CONTROLLER_SERVER_H_
#define _OTP_CONTROLLER_SERVER_H_

#include "Base/Aes.h"
#include "Private/PrivateOtpControllerServer.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class OtpControllerServer : public PrivateOtpControllerServer<PacketSize, Width, Height>
    {
    public:
        OtpControllerServer(){};
       ~OtpControllerServer(){};

        bool initialize_server(AES::KEY256& InitialKeyAes, AES::WORDS& InitialKeyOtp, uint16_t Port, uint32_t Size);

        bool communicate();

        OtpFrames<PacketSize, Width, Height>& get_frames();
    };
}

#include "OneTimePad/OtpControllerServer.inl"

#endif // _OTP_CONTROLLER_SERVER_H_
