
include_directories(
    ${PROJECT_BASEDIR}/Extras/DirectX-Headers/include/directx
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)

add_library(${PROJECT_NAME} STATIC
    ${PLATFORM}/Time.cpp
    ${PLATFORM}/NetworkClientTcp.cpp
    ${PLATFORM}/NetworkClientUdp.cpp
    ${PLATFORM}/NetworkServerTcp.cpp
    ${PLATFORM}/NetworkServerUdp.cpp
    ${PLATFORM}/Screen.cpp

    Base/Aes.cpp
    Base/Endianness.cpp
    Base/NetworkClient.cpp
    Base/NetworkServer.cpp
    Base/Sha512.cpp
    Base/Statistics.cpp
    Base/UtilsParser.cpp
    Base/UtilsPgm.cpp

    IntegrityCheck/IntegrityCheckManager.cpp

    Multipath/MpManager.cpp

    OneTimePad/OtpManager.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
