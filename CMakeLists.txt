cmake_minimum_required(VERSION 3.29)
project(GemXP C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "src/*.c")

add_executable(gemxp ${SOURCES}
        include/common.h)

target_include_directories(gemxp PUBLIC include)