cmake_minimum_required(VERSION 3.16)
project(CipherClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(cipher_client ${SOURCES})

# Link Winsock on Windows
if(WIN32)
    target_link_libraries(cipher_client ws2_32)
endif()
