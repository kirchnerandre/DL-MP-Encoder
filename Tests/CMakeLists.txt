
if (${PLATFORM} MATCHES Linux)
    set (LIBRARY_NETWORK    "")
    set (LIBRARY_SCREEN_1   "GL")
    set (LIBRARY_SCREEN_2   "GLEW")
    set (LIBRARY_SCREEN_3   "glfw")
    set (LIBRARY_OTHER_1    "")
    set (FILE_EXTENSION     ".exe")
elseif (${PLATFORM} MATCHES Windows)
    set (LIBRARY_NETWORK    "ws2_32.lib")
    set (LIBRARY_SCREEN_1   "d3d12")
    set (LIBRARY_SCREEN_2   "DXGI")
    set (LIBRARY_SCREEN_3   "dxguid")
    set (LIBRARY_OTHER_1    "D3DCompiler")
    set (FILE_EXTENSION     "")
endif ()

set (TEST_NAME "test-001")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Buffer.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-002")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Crc.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-003")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Screen.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Extras/DirectX-Headers/include/directx
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_SCREEN_1}
    ${LIBRARY_SCREEN_2}
    ${LIBRARY_SCREEN_3}
    ${LIBRARY_OTHER_1})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-004")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Time.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_SCREEN_1}
    ${LIBRARY_SCREEN_2}
    ${LIBRARY_SCREEN_3})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-005")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Aes.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-006")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-UtilsPgm.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-007")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Endianness.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-008")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Network.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-009")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-OtpEncoder.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-010")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-OtpManager.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-011")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-OtpFrame.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Private)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
     ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-012")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-OtpFrames.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-013")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-OtpController.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-014")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-MpEncoder.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-015")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-MpManager.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-016")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-MpFrame.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include
    ${PROJECT_BASEDIR}/Inline)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-017")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-MpFrames.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-018")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-MpController.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-019")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Sha512.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-020")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-IntegrityCheckManager.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-021")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-IntegrityCheckFrame.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-022")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-IntegrityCheckFrames.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-023")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-IntegrityCheckController.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME}
    ${LIBRARY_NETWORK})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

set (TEST_NAME "test-024")
add_executable(
    ${TEST_NAME}${FILE_EXTENSION}
    ${TEST_NAME}-Lua.cpp)
include_directories(
    ${PROJECT_BASEDIR}/Include)
target_link_libraries(
    ${TEST_NAME}${FILE_EXTENSION}
    ${PROJECT_NAME})
add_test(
    NAME                ${TEST_NAME}
    COMMAND             ${TEST_NAME}${FILE_EXTENSION}
    WORKING_DIRECTORY   ${PROJECT_BASEDIR})
set_property(
    TARGET              ${TEST_NAME}${FILE_EXTENSION}
    PROPERTY            CXX_STANDARD 17)

