cmake_minimum_required(VERSION 3.17)
project(Data-compression-LZW)

set(CMAKE_CXX_STANDARD 21)

add_executable(Data-compression-LZW main.cpp Dictionary.cpp Dictionary.h Coder.cpp Coder.h buffer_reader.h buffer_reader.cpp)