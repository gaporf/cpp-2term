//
// Created by gaporf on 17.05.19.
//

#ifndef BIGINT_OPTIMIZED_SHARED_PTR_H
#define BIGINT_OPTIMIZED_SHARED_PTR_H

#include <iostream>

struct current_ptr {
    explicit current_ptr(uint64_t *ptr);

    ~current_ptr();

    void inc();

    void dec();

    uint64_t *get();

    size_t count();
private:
    uint64_t *_ptr;
    size_t _cnt;
};

struct shared_ptr {
    explicit shared_ptr(uint64_t *ptr = nullptr);

    ~shared_ptr();

    shared_ptr(const shared_ptr &rhs);

    shared_ptr &operator=(const shared_ptr &rhs);

    uint64_t *get() const;

    void reset(uint64_t *ptr = nullptr);

    size_t use_count() const;
private:
    current_ptr *_cur_ptr;
};

#endif //BIGINT_OPTIMIZED_SHARED_PTR_H
