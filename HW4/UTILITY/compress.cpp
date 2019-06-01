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

#include "compress.h"
#include "HUFFMAN/coder.h"

void compress(std::string &file_in, std::string &file_out) {
    int32_t rd = open(file_in.c_str(), O_RDONLY);
    if (rd == -1) {
        std::cerr << "Could not open the file " << file_in << std::endl;
        exit(3);
    }
    const size_t N = 1024;
    std::vector<char> symbols(N);
    coder data;
    for (;;) {
        size_t n = read(rd, symbols.data(), N);
        if (n == 0) {
            break;
        }
        data.add(n, symbols.data());
    }
    close(rd);
    int32_t wd = open(file_out.c_str(), O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    close(wd);
    wd = open(file_out.c_str(), O_TRUNC | O_WRONLY);
    if (wd == -1) {
        std::cerr << "Could not write the file " << file_out << std::endl;
        exit(4);
    }
    auto str = data.get_tree();
    auto num = std::to_string(str.length()) + '\n';
    write(wd, num.c_str(), num.length());
    write(wd, str.c_str(), str.length());
    rd = open(file_in.c_str(), O_RDONLY);
    if (rd == -1) {
        std::cerr << "Could not open the file " << file_in << "std::endl";
        exit(3);
    }
    std::vector<char> cur;
    for (;;) {
        size_t n = read(rd, symbols.data(), N);
        if (n == 0) {
            break;
        }
        data.code(n, symbols.data(), cur);
        std::vector<char> coding_symbols;
        for (size_t i = 0; i + 8 <= cur.size(); i += 8) {
            uint8_t c = 0;
            for (size_t j = i; j < i + 8; j++) {
                c *= 2;
                if (cur[j] == '1') {
                    c += 1;
                }
            }
            coding_symbols.push_back(c);
        }
        if (!coding_symbols.empty()) {
            write(wd, coding_symbols.data(), coding_symbols.size());
        }
        std::vector<char> new_cur;
        for (size_t i = (cur.size() / 8) * 8; i < cur.size(); i++) {
            new_cur.push_back(cur[i]);
        }
        cur = new_cur;
    }
    if (!cur.empty()) {
        uint8_t c = 0;
        auto long_code = data.long_code();
        for (size_t i = 0; i < 8; i++) {
            c *= 2;
            if (i < cur.size()) {
                if (cur[i] == '1') {
                    c += 1;
                }
            } else {
                if (long_code[i - cur.size()] == '1') {
                    c += 1;
                }
            }
        }
        write(wd, &c, 1);
    }
    close(rd);
    close(wd);
}