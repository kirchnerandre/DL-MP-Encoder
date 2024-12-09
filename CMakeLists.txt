
set (PROJECT_NAME           "Encoder")
set (PROJECT_VERSION        0.02)
set (PROJECT_DESCRIPTION    "DL and MP Encoder/Decoder")
set (PROJECT_BASEDIR        ${CMAKE_CURRENT_SOURCE_DIR})

cmake_minimum_required(VERSION 3.22)

project (${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION ${PROJECT_DESCRIPTION})

enable_testing ()

if (${PLATFORM} MATCHES Linux)
    add_compile_definitions(ENCODER_PLATFORM_LINUX)
elseif (${PLATFORM} MATCHES Windows)
    add_compile_definitions(ENCODER_PLATFORM_WINDOWS UNICODE)
endif ()

add_subdirectory (Demo)
add_subdirectory (Source)
add_subdirectory (Tests)
