cmake_minimum_required(VERSION 3.5)

project(cryptor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cryptor src/main.cpp include/defines.hpp include/crypt.hpp src/crypt.cpp)
