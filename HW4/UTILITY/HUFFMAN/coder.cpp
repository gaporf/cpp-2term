//
// Created by gaporf on 31.05.19.
//

#include "coder.h"
#include "tree.h"
#include <set>

coder::coder() : count(256, 0), ans(256), root(nullptr) {}

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

void coder::code(size_t n, char *str, std::vector<char> &cur) {
    for (size_t i = 0; i < n; i++) {
        auto v = ans[static_cast<uint8_t>(str[i])];
        for (size_t j = 0; j < v.length(); j++) {
            cur.push_back(v[j]);
        }
    }
}

std::string coder::long_code() {
    for (size_t i = 0; i < 255; i++) {
        if (ans[i].length() > 8) {
            return ans[i];
        }
    }
    return ans[255];
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