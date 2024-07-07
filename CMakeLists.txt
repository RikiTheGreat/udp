cmake_minimum_required(VERSION 3.28)
project(udp_app)

set(CMAKE_CXX_STANDARD 20)

add_executable(udp_app main.cpp
        Udp.cpp
        Udp.hpp)
