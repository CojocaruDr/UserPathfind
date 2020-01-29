cmake_minimum_required(VERSION 3.15)
project(UserFinding)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(UserFinding main.cpp src/User.cpp include/User.h)