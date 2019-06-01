//
// Created by gaporf on 31.05.19.
//

#include "decoder.h"
#include "tree.h"

decoder::decoder() : root(new tree(nullptr, nullptr)) {}

decoder::~decoder() {
    delete root;
}

int decoder::init(file_reader &fr) {
    std::string num;
    for (;;) {
        char c;
        size_t n = fr.get_char(1, &c);
        if (n == 0 || n == -1) {
            std::cerr << "File damaged" << std::endl;
            return 2;
        } else if (c == '\n') {
            break;
        } else {
            num += c;
        }
    }
    size_t N = std::stoi(num);
    std::vector<char> symbols(N);
    size_t n = fr.get_char(N, symbols.data());
    if (n != N) {
        std::cerr << "File damaged" << std::endl;
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
        std::cerr << "File damaged" << std::endl;
        return 2;
    }
    for (size_t i = 0; i < 256; i++) {
        add(root, codes[i], 0, i);
    }
    return 0;
}

int decoder::add(tree *cur, std::string &code, size_t pos, uint8_t c) {
    if (pos == code.length()) {
        if (cur->is_final) {
            std::cerr << "File damaged" << std::endl;
            return 2;
        }
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
    return 0;
}

std::pair<std::vector<char>, std::vector<char>> decoder::decode(const std::vector<char> &code) {
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
            std::cerr << "File damaged" << std::endl;
            return {{},
                    {}};
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