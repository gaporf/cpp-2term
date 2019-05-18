//
// Created by gaporf on 17.05.19.
//

#include <algorithm>
#include "vector.h"

vector::vector() : _is_big(false), _size(0) {}

vector::vector(size_t initial_size) : _is_big(initial_size > SMALL_SIZE), _size(initial_size) {
    if (_is_big) {
        new(&_data._big) big_data();
        _data._big._capacity = 2 * initial_size;
        _data._big._ptr.reset(new uint64_t[_data._big._capacity]);
        _data._big._begin = _data._big._ptr.get();
    }
}

vector::vector(size_t initial_size, uint64_t initial_value) : vector(initial_size) {
    if (!_is_big) {
        for (size_t i = 0; i < initial_size; i++) {
            _data._arr[i] = initial_value;
        }
    } else {
        for (size_t i = 0; i < initial_size; i++) {
            _data._big._begin[i] = initial_value;
        }
    }
}

vector::vector(vector const &rhs) : _is_big(rhs._is_big), _size(rhs._size) {
    if (!_is_big) {
        for (size_t i = 0; i < _size; i++) {
            _data._arr[i] = rhs._data._arr[i];
        }
    } else {
        new(&_data._big) big_data();
        _data._big = rhs._data._big;
    }
}

vector::~vector() {
    if (_is_big) {
        _data._big._ptr.reset(nullptr);
    }
}

vector &vector::operator=(vector const &rhs) {
    if (this != &rhs) {
        if (_is_big) {
            _data._big._ptr.reset();
        }
        new(&_data._big) big_data();
        _is_big = rhs._is_big;
        _size = rhs._size;
        if (!_is_big) {
            for (size_t i = 0; i < _size; i++) {
                _data._arr[i] = rhs._data._arr[i];
            }
        } else {
            _data._big = rhs._data._big;
        }
    }
    return *this;
}

void vector::push_back(uint64_t a) {
    if (!_is_big) {
        if (_size + 1 <= SMALL_SIZE) {
            _data._arr[_size] = a;
        } else {
            small_to_big();
        }
    }
    if (_is_big) {
        if (_size == _data._big._capacity) {
            expand(_data._big._capacity * 2);
        } else if (_data._big._ptr.use_count() != 1) {
            make_copy();
        }
        _data._big._begin[_size] = a;
    }
    _size++;
}

bool vector::empty() const {
    return _size == 0;
}

size_t vector::size() const {
    return _size;
}

uint64_t &vector::back() {
    if (!_is_big) {
        return _data._arr[_size - 1];
    } else {
        if (_data._big._ptr.use_count() != 1) {
            make_copy();
        }
        return _data._big._begin[_size - 1];
    }
}

void vector::pop_back() {
    _size--;
    if (_size == SMALL_SIZE) {
        big_to_small();
    }
}

void vector::resize(size_t new_size, uint64_t initial) {
    if (new_size > SMALL_SIZE && !_is_big) {
        small_to_big();
    } else if (new_size <= SMALL_SIZE && _is_big) {
        big_to_small();
    }
    if (!_is_big) {
        for (size_t i = _size; i < new_size; i++) {
            _data._arr[i] = initial;
        }
    } else {
        if (new_size > _data._big._capacity) {
            expand(2 * new_size);
        }
        if (_data._big._ptr.use_count() != 1) {
            make_copy();
        }
        for (size_t i = _size; i < new_size; i++) {
            _data._big._begin[i] = initial;
        }
    }
    _size = new_size;
}

void vector::assign(size_t new_size, uint64_t initial) {
    if (new_size > SMALL_SIZE && !_is_big) {
        small_to_big();
    } else if (new_size <= SMALL_SIZE && _is_big) {
        big_to_small();
    }
    if (!_is_big) {
        for (size_t i = 0; i < new_size; i++) {
            _data._arr[i] = initial;
        }
    } else {
        if (new_size > _data._big._capacity) {
            expand(2 * new_size);
        }
        if (_data._big._ptr.use_count() != 1) {
            make_copy();
        }
        for (size_t i = 0; i < new_size; i++) {
            _data._big._begin[i] = initial;
        }
    }
    _size = new_size;
}

uint64_t &vector::operator[](uint32_t index) {
    if (!_is_big) {
        return _data._arr[index];
    } else {
        if (_data._big._ptr.use_count() != 1) {
            make_copy();
        }
        return _data._big._begin[index];
    }
}

uint64_t const &vector::operator[](uint32_t index) const {
    return *(begin() + index);
}

bool operator==(vector const &a, vector const &b) {
    if (a._is_big != b._is_big || a._size != b._size) {
        return false;
    } else {
        if (!a._is_big) {
            for (size_t i = 0; i < a._size; i++) {
                if (a._data._arr[i] != b._data._arr[i]) {
                    return false;
                }
            }
        } else {
            for (size_t i = 0; i < a._size; i++) {
                if (a._data._big._begin[i] != b._data._big._begin[i]) {
                    return false;
                }
            }
        }
        return true;
    }
}

void vector::reverse() {
    if (!_is_big) {
        for (size_t i = 0, j = _size - 1; i < j; i++, j--) {
            std::swap(_data._arr[i], _data._arr[j]);
        }
    } else {
        if (_data._big._ptr.use_count() != 1) {
            make_copy();
        }
        for (size_t i = 0, j = _size - 1; i < j; i++, j--) {
            std::swap(_data._big._begin[i], _data._big._begin[j]);
        }
    }
}

void vector::erase(size_t till) {
    if (!_is_big) {
        for (size_t i = 0; i + till < _size; i++) {
            _data._arr[i] = _data._arr[i + till];
        }
    } else {
        if (_data._big._ptr.use_count() != 1) {
            make_copy();
        }
        for (size_t i = 0; i + till < _size; i++) {
            _data._big._begin[i] = _data._big._begin[i + till];
        }
    }
    _size -= till;
}

uint64_t const *vector::begin() const {
    if (!_is_big) {
        return _data._arr;
    } else {
        return _data._big._begin;
    }
}

uint64_t *vector::begin() {
    if (!_is_big) {
        return _data._arr;
    } else {
        return _data._big._begin;
    }
}

void vector::small_to_big() {
    uint64_t old[SMALL_SIZE];
    for (size_t i = 0; i < SMALL_SIZE; i++) {
        old[i] = _data._arr[i];
    }
    new(&_data._big) big_data();
    _data._big._capacity = 2 * SMALL_SIZE;
    _data._big._ptr = shared_ptr(new uint64_t[_data._big._capacity]);
    _data._big._begin = _data._big._ptr.get();
    for (size_t i = 0; i < SMALL_SIZE; i++) {
        _data._big._begin[i] = old[i];
    }
    _is_big = true;
}

void vector::big_to_small() {
    uint64_t old[SMALL_SIZE];
    for (size_t i = 0; i < SMALL_SIZE; i++) {
        old[i] = _data._big._begin[i];
    }
    _data._big._ptr.reset(nullptr);
    for (size_t i = 0; i < SMALL_SIZE; i++) {
        _data._arr[i] = old[i];
    }
    _is_big = false;
}

void vector::expand(size_t new_size) {
    auto new_ptr = new uint64_t[new_size];
    for (size_t i = 0; i < _size; i++) {
        new_ptr[i] = _data._big._begin[i];
    }
    _data._big._begin = new_ptr;
    _data._big._ptr.reset(new_ptr);
    _data._big._capacity = new_size;
}

void vector::make_copy() {
    auto new_ptr = new uint64_t[_data._big._capacity];
    for (size_t i = 0; i < _size; i++) {
        new_ptr[i] = _data._big._begin[i];
    }
    _data._big._begin = new_ptr;
    _data._big._ptr.reset(new_ptr);
}