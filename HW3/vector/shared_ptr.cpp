//
// Created by gaporf on 17.05.19.
//

#include "shared_ptr.h"
#include <iostream>

current_ptr::current_ptr(uint64_t *ptr) : _ptr(ptr) {
    if (_ptr == nullptr) {
        _cnt = 0;
    } else {
        _cnt = 1;
    }
}

current_ptr::~current_ptr() {
    delete[] _ptr;
}

void current_ptr::inc() {
    _cnt++;
}

void current_ptr::dec() {
    _cnt--;
    if (_cnt == 0) {
        delete this;
    }
}

uint64_t *current_ptr::get() {
    return _ptr;
}

size_t current_ptr::count() {
    return _cnt;
}

shared_ptr::shared_ptr(uint64_t *ptr) {
    if (ptr != nullptr) {
        _cur_ptr = new current_ptr(ptr);
    } else {
        _cur_ptr = nullptr;
    }
}

shared_ptr::~shared_ptr() {
    if (_cur_ptr != nullptr) {
        _cur_ptr->dec();
    }
}

shared_ptr::shared_ptr(const shared_ptr &rhs) : _cur_ptr(rhs._cur_ptr) {
    if (!_cur_ptr) {
        _cur_ptr->inc();
    }
}

shared_ptr &shared_ptr::operator=(const shared_ptr &rhs) {
    if (this != &rhs) {
        if (_cur_ptr != nullptr) {
            _cur_ptr->dec();
        }
        _cur_ptr = rhs._cur_ptr;
        if (_cur_ptr != nullptr) {
            _cur_ptr->inc();
        }
    }
    return *this;
}

uint64_t *shared_ptr::get() const {
    if (_cur_ptr != nullptr) {
        return _cur_ptr->get();
    } else {
        return nullptr;
    }
}

void shared_ptr::reset(uint64_t *ptr) {
    if (_cur_ptr != nullptr) {
        _cur_ptr->dec();
    }
    if (ptr != nullptr) {
        _cur_ptr = new current_ptr(ptr);
    } else {
        _cur_ptr = nullptr;
    }
}

size_t shared_ptr::use_count() const {
    if (_cur_ptr == nullptr) {
        return 0;
    } else {
        return _cur_ptr->count();
    }
}