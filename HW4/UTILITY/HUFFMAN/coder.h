//
// Created by gaporf on 31.05.19.
//

#ifndef HUFFMAN_CODER_H
#define HUFFMAN_CODER_H

#include <iostream>
#include <vector>

struct tree;

struct coder {
    coder();

    ~coder();

    void add(size_t n, char *str);

    std::string get_tree();

    void code(size_t n, char *str, std::vector<char> &bytes);

    uint8_t get_tail();

    bool has_tail();

private:
    void build_tree();

    void dfs(tree *cur, const std::string &cur_code);

    std::vector<size_t> count;

    std::vector<std::string> ans;

    std::string cur_bit;

    std::string long_code();

    tree *root;
};

#endif //HUFFMAN_CODER_H
