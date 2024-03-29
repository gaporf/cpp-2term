//
// Created by gaporf on 31.05.19.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include <vector>
#include <string>
#include "file_reader.h"

struct tree;

struct decoder {
    explicit decoder();

    ~decoder();

    decoder &operator=(decoder const &rhs) = delete;

    decoder(decoder const &rhs) = delete;

    int init(file_reader &fr);

    std::pair<std::vector<char>, std::vector<char>> decode(const std::vector<char> &code);

private:
    tree *root;

    int add(tree *cur, std::string &code, size_t pos, uint8_t c);
};

#endif //HUFFMAN_DECODER_H
