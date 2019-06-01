//
// Created by gaporf on 30.05.19.
//

#ifndef UTILITY_DECOMPRESS_H
#define UTILITY_DECOMPRESS_H

#include <iostream>
#include <string>

int decompress(std::string const &file_in, std::string const &file_out);

std::string get_string(uint8_t c);

#endif //UTILITY_DECOMPRESS_H
