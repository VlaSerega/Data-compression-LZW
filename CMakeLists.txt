cmake_minimum_required(VERSION 3.17)
project(Data-compression-LZW)

set(CMAKE_CXX_STANDARD 14)

add_executable(Data-compression-LZW main/main.cpp coder/Dictionary.cpp coder/Dictionary.h coder/Coder.cpp coder/Coder.h buf_read/buffer_reader.h buf_read/buffer_reader.cpp)