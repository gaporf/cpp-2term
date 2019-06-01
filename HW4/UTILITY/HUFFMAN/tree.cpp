//
// Created by gaporf on 31.05.19.
//

#include "tree.h"

tree::tree(uint8_t symbol) : symbol(symbol), is_final(true), next_level(nullptr, nullptr) {}

tree::tree(tree *first, tree *second) : symbol(0), is_final(false), next_level(first, second) {}

tree::~tree() {
    delete next_level.first;
    delete next_level.second;
}

bool tree::operator<(tree const &rhs) {
    return false;
}

bool operator<(tree const &a, tree const &b) {
    return false;
}