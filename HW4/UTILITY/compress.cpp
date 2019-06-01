//
// Created by gaporf on 30.05.19.
//

#include <cstring>
#include <vector>
#include <iostream>

#include "compress.h"
#include "HUFFMAN/coder.h"
#include "file_reader.h"
#include "file_writer.h"

int compress(std::string &file_in, std::string &file_out) {
    file_reader in(file_in);
    if (!in.is_open()) {
        std::cerr << "Could not open_file the file " << file_in << std::endl;
        return 2;
    }
    const size_t N = 1024;
    std::vector<char> symbols(N);
    coder data;
    for (;;) {
        size_t n = in.get_char(N, symbols.data());
        if (n == 0) {
            break;
        }
        data.add(n, symbols.data());
    }
    file_writer out(file_out);
    if (!out.is_open()) {
        std::cerr << "Could not write the file " << file_out << std::endl;
        return 2;
    }
    auto str = data.get_tree();
    auto num = std::to_string(str.length()) + '\n';
    out.put_char(num.length(), num.c_str());
    out.put_char(str.length(), str.c_str());
    in.open_file(file_in);
    if (!in.is_open()) {
        std::cerr << "Could not open_file the file " << file_in << "std::endl";
        return 2;
    }
    std::vector<char> cur;
    for (;;) {
        size_t n = in.get_char(N, symbols.data());
        if (n == 0) {
            break;
        }
        data.code(n, symbols.data(), cur);
        if (!cur.empty()) {
            out.put_char(cur.size(), cur.data());
            cur.clear();
        }
    }
    if (data.has_tail()) {
        char c = data.get_tail();
        out.put_char(1, &c);
    }
    return 0;
}