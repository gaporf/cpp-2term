//
// Created by gaporf on 30.05.19.
//

#include <cstring>
#include <vector>
#include <iostream>

#include "decompress.h"
#include "HUFFMAN/coder.h"
#include "HUFFMAN/decoder.h"
#include "HUFFMAN/file_reader.h"
#include "HUFFMAN/file_writer.h"

int decompress(std::string const &file_in, std::string const &file_out) {
    file_reader in(file_in);
    if (!in.is_open()) {
        std::cerr << "Could not open the file " << file_in.c_str() << std::endl;
        return 2;
    }
    decoder data;
    int check = data.init(in);
    if (check != 0) {
        return check;
    }
    const size_t N = 1024;
    std::vector<char> symbols(N);
    file_writer out(file_out);
    if (!out.is_open()) {
        std::cerr << "Could not write the file " << file_out << std::endl;
        return 2;
    }
    for (std::vector<char> code;;) {
        size_t n = in.get_char(N, symbols.data());
        if (n == 0) {
            break;
        } else if (n == -1) {
            std::cerr << "Could not open the file " << file_in << std::endl;
            return 2;
        }
        for (size_t i = 0; i < n; i++) {
            uint8_t c = symbols[i];
            for (size_t i = 128; i > 0; i /= 2) {
                code.push_back('0' + c / i);
                c %= i;
            }
        }
        auto res = data.decode(code);
        if (res.first.empty() && res.second.empty()) {
            return 2;
        }
        out.put_char(res.first.size(), res.first.data());
        code = res.second;
    }
    return 0;
}
