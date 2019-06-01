//
// Created by gaporf on 31.05.19.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include <vector>
#include <string>

struct tree;

struct decoder {
    explicit decoder(std::vector<std::string> &codes);

    ~decoder();

    std::pair<std::vector<char>, std::vector<char>> decode(const std::vector<char>& code);

private:
    tree *root;

    void add(tree *cur, std::string &code, size_t pos, uint8_t c);
};

#endif //HUFFMAN_DECODER_H
