//
// Created by gaporf on 30.05.19.
//

#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "decompress.h"
#include "HUFFMAN/decoder.h"

void decompress(std::string &file_in, std::string &file_out) {
    int32_t rd = open(file_in.c_str(), O_RDONLY);
    if (rd == -1) {
        std::cerr << "Could not open the file " << file_in.c_str() << std::endl;
        exit(1);
    }
    std::string num;
    for (;;) {
        char c;
        size_t n = read(rd, &c, 1);
        if (n == 0) {
            std::cerr << "File damaged " << file_in.c_str() << std::endl;
            exit(1);
        } else if (c == '\n') {
            break;
        } else {
            num += c;
        }
    }
    size_t N = std::stoi(num);
    std::vector<char> symbols(N);
    size_t n = read(rd, symbols.data(), N);
    if (n != N) {
        std::cerr << "File damaged " << file_in.c_str() << std::endl;
        exit(1);
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
        exit(1);
    }
    decoder data(codes);
    N = 1024;
    int32_t wd = open(file_out.c_str(), O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    close(wd);
    wd = open(file_out.c_str(), O_WRONLY | O_TRUNC);
    if (wd == -1) {
        std::cerr << "Could not write the file " << file_out << std::endl;
        exit(4);
    }
    for (std::vector<char> code;;) {
        n = read(rd, symbols.data(), N);
        if (n == 0) {
            break;
        }
        for (size_t i = 0; i < n; i++) {
            auto v = get_string(symbols[i]);
            for (size_t j = 0; j < v.length(); j++) {
                code.push_back(v[j]);
            }
        }
        auto res = data.decode(code);
        write(wd, res.first.data(), res.first.size());
        code = res.second;
    }
    close(wd);
    close(rd);
}

std::string get_string(uint8_t c) {
    std::string str;
    for (size_t i = 128; i > 0; i /= 2) {
        str += static_cast<char>('0' + c / i);
        c %= i;
    }
    return str;
}