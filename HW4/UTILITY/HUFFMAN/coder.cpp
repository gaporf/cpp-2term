//
// Created by gaporf on 31.05.19.
//

#include "coder.h"
#include "tree.h"
#include <set>

coder::coder() : count(256, 0), ans(256), cur_bit(), root(nullptr) {}

coder::~coder() {
    delete root;
}

void coder::add(size_t n, char *str) {
    for (size_t i = 0; i < n; i++) {
        count[static_cast<uint8_t>(str[i])]++;
    }
}

std::string coder::get_tree() {
    build_tree();
    dfs(root, "");
    std::string all;
    for (size_t i = 0; i < 256; i++) {
        all += ans[i] + "\n";
    }
    return all;
}

void coder::code(size_t n, char *str, std::vector<char> &bytes) {
    for (size_t i = 0; i < n; i++) {
        cur_bit += ans[static_cast<uint8_t>(str[i])];
    }
    for (size_t i = 0; i + 8 <= cur_bit.length(); i += 8) {
        uint8_t c = 0;
        for (size_t j = i; j < i + 8; j++) {
            c *= 2;
            if (cur_bit[j] == '1') {
                c++;
            }
        }
        bytes.push_back(c);
    }
    std::string new_cur;
    for (size_t i = (cur_bit.length() / 8 * 8); i < cur_bit.length(); i++) {
        new_cur += cur_bit[i];
    }
    cur_bit = new_cur;
}

void coder::build_tree() {
    std::set<std::pair<size_t, tree *>> set;
    for (size_t i = 0; i < 256; i++) {
        tree *cur = new tree(i);
        set.insert(std::make_pair(count[static_cast<uint8_t>(i)], cur));
    }
    while (set.size() > 1) {
        auto first = *set.begin();
        set.erase(set.begin());
        auto second = *set.begin();
        set.erase(set.begin());
        tree *cur = new tree(first.second, second.second);
        set.insert(std::make_pair(first.first + second.first, cur));
    }
    root = set.begin()->second;
}

uint8_t coder::get_tail() {
    std::string str = long_code();
    uint8_t c = 0;
    for (size_t i = 0; i < 8; i++) {
        c *= 2;
        if (i < cur_bit.length()) {
            if (cur_bit[i] == '1') {
                c++;
            }
        } else if (str[i - cur_bit.length()] == '1') {
            c++;
        }
    }
    cur_bit = "";
    return c;
}

bool coder::has_tail() {
    return cur_bit.length() > 0;
}

void coder::dfs(tree *cur, const std::string &cur_code) {
    if (cur->is_final) {
        ans[cur->symbol] = cur_code;
    } else {
        if (cur->next_level.first != nullptr) {
            dfs(cur->next_level.first, cur_code + "0");
        }
        if (cur->next_level.second != nullptr) {
            dfs(cur->next_level.second, cur_code + "1");
        }
    }
}


std::string coder::long_code() {
    for (size_t i = 0; i < 255; i++) {
        if (ans[i].length() > 7) {
            return ans[i];
        }
    }
    return ans[255];
}