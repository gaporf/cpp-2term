//
// Created by gaporf on 17.05.19.
//

#ifndef BIGINT_OPTIMIZED_VECTOR_H
#define BIGINT_OPTIMIZED_VECTOR_H

#include <iostream>
#include <memory>
#include <vector>
#include "shared_ptr.h"

struct vector {
    vector();

    vector(size_t initial_size, uint64_t initial_value);

    explicit vector(size_t initial_size);

    ~vector();

    vector(vector const &rhs);

    vector &operator=(vector const &rhs);

    void push_back(uint64_t a);

    bool empty() const;

    size_t size() const;

    uint64_t &back();

    void pop_back();

    void resize(size_t new_size, uint64_t initial = 0);

    void assign(size_t new_size, uint64_t initial);

    uint64_t &operator[](uint32_t index);

    uint64_t const &operator[](uint32_t index) const;

    friend bool operator==(vector const &a, vector const &b);

    void reverse();

    void erase(size_t till);

    uint64_t const *begin() const;

    uint64_t *begin();

private:
    static size_t const SMALL_SIZE = 6;

    struct big_data {
        shared_ptr _ptr;
        size_t _capacity;
        uint64_t *_begin;

        big_data() : _ptr(nullptr), _capacity(0) {}
    };

    union any {
        uint64_t _arr[SMALL_SIZE];
        big_data _big;

        any() {}

        ~any() {}
    } _data;

    bool _is_big;
    size_t _size;

    void small_to_big();

    void big_to_small();

    void expand(size_t new_size);

    void make_copy();
};

bool operator==(vector const &a, vector const &b);

#endif //BIGINT_OPTIMIZED_VECTOR_H
