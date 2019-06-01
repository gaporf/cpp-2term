cmake_minimum_required(VERSION 3.14)
project(UTILITY)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(HUFFMAN)

include_directories(${UTILITY_SOURCE_DIR})

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif ()

add_executable(UTILITY
        main.cpp
        compress.h
        compress.cpp
        decompress.h
        decompress.cpp
        test.h
        test.cpp
        HUFFMAN/file_reader.h
        HUFFMAN/file_reader.cpp
        HUFFMAN/file_writer.h
        HUFFMAN/file_writer.cpp)

target_link_libraries(UTILITY HUFFMAN)