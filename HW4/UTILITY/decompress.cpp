//
// Created by gaporf on 30.05.19.
//

#include <cstring>
#include <vector>
#include <iostream>

#include "decompress.h"
#include "HUFFMAN/coder.h"
#include "HUFFMAN/decoder.h"
#include "file_reader.h"
#include "file_writer.h"

int decompress(std::string &file_in, std::string &file_out) {
    file_reader in(file_in);
    if (!in.is_open()) {
        std::cerr << "Could not open_file the file " << file_in.c_str() << std::endl;
        return 2;
    }
    std::string num;
    for (;;) {
        char c;
        size_t n = in.get_char(1, &c);
        if (n == 0) {
            std::cerr << "File damaged " << file_in.c_str() << std::endl;
            return 2;
        } else if (c == '\n') {
            break;
        } else {
            num += c;
        }
    }
    size_t N = std::stoi(num);
    std::vector<char> symbols(N);
    size_t n = in.get_char(N, symbols.data());
    if (n != N) {
        std::cerr << "File damaged " << file_in.c_str() << std::endl;
        return 2;
    }
    std::vector<std::string> codes;
    std::string cur;
    for (size_t i = 0; i < n; i++) {
        if (symbols[i] != '\n') {
            cur += symbols[i];
        } else {
            codes.push_back(cur);
            cur = "";
        }
    }
    if (codes.size() != 256) {
        std::cerr << "File damaged " << file_in.c_str() << std::endl;
        return 2;
    }
    decoder data(codes);
    N = 1024;
    file_writer out(file_out);
    if (!out.is_open()) {
        std::cerr << "Could not write the file " << file_out << std::endl;
        return 2;
    }
    for (std::vector<char> code;;) {
        n = in.get_char(N, symbols.data());
        if (n == 0) {
            break;
        }
        for (size_t i = 0; i < n; i++) {
            auto v = get_string(symbols[i]);
            for (char j : v) {
                code.push_back(j);
            }
        }
        auto res = data.decode(code);
        out.put_char(res.first.size(), res.first.data());
        code = res.second;
    }
    return 0;
}

std::string get_string(uint8_t c) {
    std::string str;
    for (size_t i = 128; i > 0; i /= 2) {
        str += static_cast<char>('0' + c / i);
        c %= i;
    }
    return str;
}