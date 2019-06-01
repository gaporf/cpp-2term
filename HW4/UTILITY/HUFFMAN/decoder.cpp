//
// Created by gaporf on 31.05.19.
//

#include "decoder.h"
#include "tree.h"

decoder::decoder(std::vector<std::string> &codes) : root(new tree(nullptr, nullptr)) {
    for (size_t i = 0; i < 256; i++) {
        add(root, codes[i], 0, i);
    }
}

decoder::~decoder() {
    delete root;
}

void decoder::add(tree *cur, std::string &code, size_t pos, uint8_t c) {
    if (pos == code.length()) {
        cur->is_final = true;
        cur->symbol = c;
    } else {
        if (code[pos] == '0') {
            if (cur->next_level.first == nullptr) {
                cur->next_level.first = new tree(nullptr, nullptr);
            }
            add(cur->next_level.first, code, pos + 1, c);
        } else {
            if (cur->next_level.second == nullptr) {
                cur->next_level.second = new tree(nullptr, nullptr);
            }
            add(cur->next_level.second, code, pos + 1, c);
        }
    }
}

std::pair<std::vector<char>, std::vector<char>> decoder::decode(const std::vector<char>& code) {
    std::vector<char> ans_str,
            cur;
    auto cur_tree = root;
    for (char i : code) {
        if (i == '0') {
            cur_tree = cur_tree->next_level.first;
        } else {
            cur_tree = cur_tree->next_level.second;
        }
        if (cur_tree == nullptr) {
            std::cerr << "file damaged" << std::endl;
            exit(5);
        } else if (cur_tree->is_final) {
            ans_str.push_back(cur_tree->symbol);
            cur.clear();
            cur_tree = root;
        } else {
            cur.push_back(i);
        }
    }
    return std::make_pair(ans_str, cur);
}