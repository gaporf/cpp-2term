//
// Created by gaporf on 31.05.19.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <iostream>

struct tree {
    explicit tree(uint8_t symbol);

    tree(tree *first, tree *second);

    tree(tree const &rhs) = delete;

    ~tree();

    tree& operator=(tree const &rhs) = delete;

    uint8_t symbol;
    bool is_final;
    std::pair<tree *, tree *> next_level;

    bool operator<(tree const &rhs);

    friend bool operator<(tree const &a, tree const &b);
};

bool operator<(tree const &a, tree const &b);

#endif //HUFFMAN_TREE_H
