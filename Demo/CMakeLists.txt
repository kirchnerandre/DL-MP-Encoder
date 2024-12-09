
if (${PLATFORM} MATCHES Linux)
    set (LIBRARY_NETWORK    "")
    set (LIBRARY_SCREEN_1   "GL")
    set (LIBRARY_SCREEN_2   "GLEW")
    set (LIBRARY_SCREEN_3   "glfw")
    set (FILE_EXTENSION     ".exe")
    set (LIBRARY_OTHER_1    "")
elseif (${PLATFORM} MATCHES Windows)
    set (LIBRARY_NETWORK    "ws2_32.lib")
    set (LIBRARY_SCREEN_1   "d3d12")
    set (LIBRARY_SCREEN_2   "DXGI")
    set (LIBRARY_SCREEN_3   "dxguid")
    set (LIBRARY_OTHER_1    "D3DCompiler")
    set (FILE_EXTENSION     "")
endif ()

set (ATTACKER "Attacker-001")
add_executable(
    ${ATTACKER}${FILE_EXTENSION}
    Attacker.cpp
    Attack-001-Dummy.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${ATTACKER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${ATTACKER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (ATTACKER "Attacker-002")
add_executable(
    ${ATTACKER}${FILE_EXTENSION}
    Attacker.cpp
    Attack-002-Modify.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${ATTACKER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${ATTACKER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (ATTACKER "Attacker-003")
add_executable(
    ${ATTACKER}${FILE_EXTENSION}
    Attacker.cpp
    Attack-003-Drop.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${ATTACKER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${ATTACKER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (ATTACKER "Attacker-004")
add_executable(
    ${ATTACKER}${FILE_EXTENSION}
    Attacker.cpp
    Attack-004-Random.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${ATTACKER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${ATTACKER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (GATEWAY "Gateway")
add_executable(
    ${GATEWAY}${FILE_EXTENSION}
    ${GATEWAY}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${GATEWAY}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${GATEWAY}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (OTP_IMAGE_RECEIVER "OTP_RX_Image")
add_executable(
    ${OTP_IMAGE_RECEIVER}${FILE_EXTENSION}
    ${OTP_IMAGE_RECEIVER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${OTP_IMAGE_RECEIVER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${OTP_IMAGE_RECEIVER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (OTP_IMAGE_TRANSMITTER "OTP_TX_Image")
add_executable(
    ${OTP_IMAGE_TRANSMITTER}${FILE_EXTENSION}
    ${OTP_IMAGE_TRANSMITTER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${OTP_IMAGE_TRANSMITTER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${OTP_IMAGE_TRANSMITTER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (OTP_VIDEO_RECEIVER "OTP_RX_Video")
add_executable(
    ${OTP_VIDEO_RECEIVER}${FILE_EXTENSION}
    ${OTP_VIDEO_RECEIVER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${OTP_VIDEO_RECEIVER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK}
    ${LIBRARY_SCREEN_1}
    ${LIBRARY_SCREEN_2}
    ${LIBRARY_SCREEN_3}
    ${LIBRARY_OTHER_1})
set_property(
    TARGET      ${OTP_VIDEO_RECEIVER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (OTP_VIDEO_TRANSMITTER "OTP_TX_Video")
add_executable(
    ${OTP_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    ${OTP_VIDEO_TRANSMITTER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${OTP_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${OTP_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (MP_VIDEO_RECEIVER "MP_RX_Video")
add_executable(
    ${MP_VIDEO_RECEIVER}${FILE_EXTENSION}
    ${MP_VIDEO_RECEIVER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Extras/DirectX-Headers/include/directx
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${MP_VIDEO_RECEIVER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK}
    ${LIBRARY_SCREEN_1}
    ${LIBRARY_SCREEN_2}
    ${LIBRARY_SCREEN_3}
    ${LIBRARY_OTHER_1})
set_property(
    TARGET      ${MP_VIDEO_RECEIVER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (MP_VIDEO_TRANSMITTER "MP_TX_Video")
add_executable(
    ${MP_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    ${MP_VIDEO_TRANSMITTER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${MP_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${MP_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (INTEGRITY_CHECK_VIDEO_RECEIVER "IC_RX_Video")
add_executable(
    ${INTEGRITY_CHECK_VIDEO_RECEIVER}${FILE_EXTENSION}
    ${INTEGRITY_CHECK_VIDEO_RECEIVER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Extras/DirectX-Headers/include/directx
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${INTEGRITY_CHECK_VIDEO_RECEIVER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK}
    ${LIBRARY_SCREEN_1}
    ${LIBRARY_SCREEN_2}
    ${LIBRARY_SCREEN_3}
    ${LIBRARY_OTHER_1})
set_property(
    TARGET      ${INTEGRITY_CHECK_VIDEO_RECEIVER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)

set (INTEGRITY_CHECK_VIDEO_TRANSMITTER "IC_TX_Video")
add_executable(
    ${INTEGRITY_CHECK_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    ${INTEGRITY_CHECK_VIDEO_TRANSMITTER}.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${INTEGRITY_CHECK_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
set_property(
    TARGET      ${INTEGRITY_CHECK_VIDEO_TRANSMITTER}${FILE_EXTENSION}
    PROPERTY    CXX_STANDARD 17)
