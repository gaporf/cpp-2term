cmake_minimum_required(VERSION 3.14)
project(HUFFMAN)

set(CMAKE_CXX_STANDARD 17)

include_directories(${HUFFMAN_SOURCE_DIR})

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif ()

add_library(HUFFMAN
        coder.h
        coder.cpp
        decoder.h
        decoder.cpp
        tree.h
        tree.cpp)