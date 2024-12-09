
#ifndef _OTP_CONTROLLER_CLIENT_H_
#define _OTP_CONTROLLER_CLIENT_H_

#include "Base/Aes.h"
#include "Private/PrivateOtpControllerClient.h"

namespace ONETIMEPAD
{
    template<uint32_t PacketSize, uint32_t Width, uint32_t Height>
    class OtpControllerClient : public PrivateOtpControllerClient<PacketSize, Width, Height>
    {
    public:
        OtpControllerClient(){};
       ~OtpControllerClient(){};

        bool initialize_client(AES::KEY256& InitialKeyAes, AES::WORDS& InitialKeyOtp, uint16_t Port, std::string Address);

        bool communicate(std::string& Filename);
    };
}

#include "OneTimePad/OtpControllerClient.inl"

#endif // _OTP_CONTROLLER_CLIENT_H_
