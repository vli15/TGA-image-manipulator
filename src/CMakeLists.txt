cmake_minimum_required(VERSION 3.29)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(image-processor src/main.cpp
        src/Header.h
        src/Pixel.cpp
        src/Pixel.h
        src/Image.cpp
        src/Image.h
)
