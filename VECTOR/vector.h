//
// Created by gaporf on 18.06.19.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <algorithm>
#include <memory>

template<typename T>
struct vector {
    typedef T value_type;

    typedef T *iterator;
    typedef T const *const_iterator;
    typedef std::reverse_iterator<T *> reverse_iterator;
    typedef std::reverse_iterator<T const *> const_reverse_iterator;

    vector() : type_('e'), data_() {}

    vector(vector const &rhs) : type_(rhs.type_), data_(rhs.type_, rhs.data_) {}

    template<typename InputIterator>
    vector(InputIterator first, InputIterator second) : type_('e'), data_() {
        size_t n = std::distance(first, second);
        data_.reserve(type_, n);
        while (first < second) {
            data_.push_back(*first++, type_);
        }
    }

    vector &operator=(vector const &rhs) {
        if (this != &rhs) {
            data_.checked_delete(type_);
            data_.assignment(rhs.type_, rhs.data_);
            type_ = rhs.type_;
        }
        return *this;
    }

    ~vector() {
        data_.checked_delete(type_);
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator second) {
        size_t n = std::distance(first, second);
        reserve(n);
        for (size_t i = 0; i < std::min(n, size()); i++) {
            (*this)[i] = *first++;
        }
        if (size() < n) {
            for (size_t i = size(); i < n; i++) {
                push_back(*first++);
            }
        } else {
            erase(begin() + n, end());
        }
    }

    T const &operator[](size_t index) const {
        return data_.get_value(type_, index);
    }

    T &operator[](size_t index) {
        return data_.get_value(type_, index);
    }

    T const &front() const {
        return (*this)[0];
    }

    T &front() {
        return (*this)[0];
    }

    T const &back() const {
        return (*this)[size() - 1];
    }

    T &back() {
        return (*this)[size() - 1];
    }

    void push_back(T const &val) {
        data_.push_back(val, type_);
    }

    void pop_back() {
        data_.pop_back(type_);
    }

    T const *data() const {
        return data_.begin(type_);
    }

    T *data() {
        return data_.begin(type_);
    }

    iterator begin() {
        return data_.begin(type_);
    }

    const_iterator begin() const {
        return data_.begin(type_);
    }

    iterator end() {
        return data_.end(type_);
    }

    const_iterator end() const {
        return data_.end(type_);
    }

    reverse_iterator rbegin() {
        return data_.rbegin(type_);
    }

    const_reverse_iterator rbegin() const {
        return data_.rbegin(type_);
    }

    reverse_iterator rend() {
        return data_.rend(type_);
    }

    const_reverse_iterator rend() const {
        return data_.rend(type_);
    }

    bool empty() const {
        return size() == 0;
    }

    size_t size() const {
        return data_.get_size(type_);
    }

    void reserve(size_t new_capacity) {
        if (capacity() < new_capacity) {
            data_.reserve(type_, new_capacity);
        }
    }

    size_t capacity() const {
        return data_.get_capacity(type_);
    }

    void shrink_to_fit() {
        if (type_ == 'b' && capacity() > size()) {
            data_.shrink_to_fit();
        }
    }

    template<typename ...Args>
    void resize(size_t n, Args ...args) {
        if (n < size()) {
            erase(begin() + n, end());
        } else if (n > size()) {
            reserve(n);
            for (size_t i = size(); i < n; i++) {
                push_back(T(args...));
            }
        }
    }

    void clear() {
        data_.clear(type_);
    }

    iterator insert(const_iterator pos, T const &val) {
        return data_.insert(type_, pos - begin(), val);
    }

    iterator erase(const_iterator pos) {
        return data_.erase(type_, pos - begin(), pos - begin() + 1);
    }

    iterator erase(const_iterator first, const_iterator last) {
        return data_.erase(type_, first - begin(), last - begin());
    }

    template<typename V>
    friend bool operator==(vector<V> const &a, vector<V> const &b);

    template<typename V>
    friend bool operator!=(vector<V> const &a, vector<V> const &b);

    template<typename V>
    friend bool operator<(vector<V> const &a, vector<V> const &b);

    template<typename V>
    friend bool operator>(vector<V> const &a, vector<V> const &b);

    template<typename V>
    friend bool operator<=(vector<V> const &a, vector<V> const &b);

    template<typename V>
    friend bool operator>=(vector<V> const &a, vector<V> const &b);

    template<typename V>
    friend void swap(vector<V> &a, vector<V> &b);

private:
    char type_;

    union data {
        data() {
            big_ = nullptr;
        }

        data(char type, data const &rhs) {
            if (type == 'e') {
                big_ = nullptr;
            } else if (type == 's') {
                new(&small_) T(rhs.small_);
            } else {
                big_ = rhs.big_;
                add_usage(big_);
            }
        }

        void assignment(char b, data const &rhs) {
            if (b == 's') {
                new(&small_) T(rhs.small_);
            } else if (b == 'b') {
                big_ = rhs.big_;
                add_usage(big_);
            }
        }

        void swap(char &a, char &b, data &rhs) {
            if (a == 'e') {
                if (b == 's') {
                    new(&small_) T(rhs.small_);
                    a = 's';
                    rhs.small_.~T();
                    rhs.big_ = nullptr;
                    b = 'e';
                } else if (b == 'b') {
                    big_ = rhs.big_;
                    a = 'b';
                    rhs.big_ = nullptr;
                    b = 'e';
                }
            } else if (a == 's') {
                if (b == 'e') {
                    new(&rhs.small_) T(small_);
                    b = 's';
                    small_.~T();
                    big_ = nullptr;
                    a = 'e';
                } else if (b == 's') {
                    std::swap(small_, rhs.small_);
                } else {
                    auto local_copy = std::make_unique<T>(small_);
                    small_.~T();
                    big_ = rhs.big_;
                    add_usage(big_);
                    a = 'b';
                    new(&rhs.small_) T(*local_copy.get());
                    dec_usage(big_);
                    b = 's';
                }
            } else {
                if (b == 'e') {
                    rhs.big_ = big_;
                    b = 'b';
                    big_ = nullptr;
                    a = 'e';
                } else if (b == 's') {
                    auto local_copy = std::make_unique<T>(rhs.small_);
                    rhs.small_.~T();
                    rhs.big_ = big_;
                    add_usage(big_);
                    b = 'b';
                    new(&small_) T(*local_copy.get());
                    dec_usage(rhs.big_);
                    a = 's';
                } else {
                    std::swap(big_, rhs.big_);
                }
            }
        }

        ~data() {}

        void *allocate_new_memory(size_t size, size_t capacity) {
            void *rhs = malloc(3 * sizeof(size_t) + capacity * sizeof(T));
            set_size(rhs, size);
            set_usage(rhs);
            set_capacity(rhs, capacity);
            return rhs;
        }

        T const *begin(void *rhs) const {
            return reinterpret_cast<T const *>(reinterpret_cast<size_t *>(rhs) + 3);
        }

        T *begin(void *rhs) {
            return reinterpret_cast<T *>(reinterpret_cast<size_t *>(rhs) + 3);
        }

        void *copy(T *src, size_t size, size_t capacity, bool is_delete = false) {
            auto new_data = allocate_new_memory(0, capacity);
            try {
                for (size_t index = 0; index < size; index++) {
                    set_value(new_data, index, *(src + index));
                    add_size(new_data);
                }
            } catch (std::exception &e) {
                delete_all(new_data);
                throw e;
            }
            if (is_delete) {
                for (size_t index = 0; index < size; index++, src++) {
                    src->~T();
                }
            }
            return new_data;
        }

        void *expand(void *rhs) {
            auto new_big = copy(begin(rhs), get_size(rhs), get_capacity(rhs) * 2);
            dec_usage(rhs);
            return new_big;
        }

        void *expand(void *rhs, size_t new_capacity) {
            auto new_big = copy(begin(rhs), get_size(rhs), new_capacity);
            dec_usage(rhs);
            return new_big;
        }

        bool is_unique(char type) {
            return type != 'b' || get_usage(big_) == 1;
        }

        void make_unique(char type) {
            if (type == 'b' && get_usage(big_) > 1) {
                auto cur = copy(begin(big_), get_size(big_), get_capacity(big_));
                dec_usage(big_);
                big_ = cur;
            }
        }

        void checked_delete(char &type) {
            if (type == 's') {
                small_.~T();
            } else if (type == 'b') {
                dec_usage(big_);
                big_ = nullptr;
            }
            type = 'e';
        }

        void delete_all(void *rhs) {
            size_t size = *reinterpret_cast<size_t *>(rhs);
            for (auto it = begin(rhs); it != begin(rhs) + size; it++) {
                it->~T();
            }
            free(rhs);
        }

        void push_back(T const &val, char &type) {
            if (type == 'e') {
                new(&small_) T(val);
                type = 's';
            } else {
                if (type == 's' || get_capacity(big_) == get_size(big_) || !is_unique(type)) {
                    auto local_copy = std::make_unique<T>(val);
                    if (type == 's') {
                        big_ = copy(&small_, 1, 10, true);
                        type = 'b';
                    } else if (get_capacity(big_) == get_size(big_)) {
                        big_ = expand(big_);
                    } else {
                        make_unique(type);
                    }
                    set_value(big_, get_size(big_), *local_copy.get());
                } else {
                    set_value(big_, get_size(big_), val);
                }
                add_size(big_);
            }
        }

        void pop_back(char &type) {
            if (type == 's') {
                small_.~T();
                type = 'e';
            } else if (type == 'b') {
                make_unique(type);
                (begin(big_) + get_size(big_) - 1)->~T();
                dec_size(big_);
                if (get_size(big_) == 0) {
                    free(big_);
                    big_ = nullptr;
                    type = 'e';
                }
            }
        }

        iterator begin(char type) {
            if (type != 'b') {
                return &small_;
            } else {
                make_unique(type);
                return begin(big_);
            }
        }

        const_iterator begin(char type) const {
            if (type != 'b') {
                return &small_;
            } else {
                return begin(big_);
            }
        }

        iterator end(char type) {
            if (type == 'e') {
                return &small_;
            } else if (type == 's') {
                return &small_ + 1;
            } else {
                make_unique(type);
                return begin(big_) + get_size(big_);
            }
        }

        const_iterator end(char type) const {
            if (type == 'e') {
                return &small_;
            } else if (type == 's') {
                return &small_ + 1;
            } else {
                return begin(big_) + get_size(big_);
            }
        }

        reverse_iterator rbegin(char type) {
            return reverse_iterator(end(type));
        }

        const_reverse_iterator rbegin(char type) const {
            return const_reverse_iterator(end(type));
        }

        reverse_iterator rend(char type) {
            return reverse_iterator(begin(type));
        }

        const_reverse_iterator rend(char type) const {
            return const_reverse_iterator(begin(type));
        }

        size_t get_size(char type) const {
            if (type == 'e') {
                return 0;
            } else if (type == 's') {
                return 1;
            } else {
                return get_size(big_);
            }
        }

        size_t get_size(void *rhs) const {
            return *reinterpret_cast<size_t *>(rhs);
        }

        void set_size(void *rhs, size_t size) {
            *reinterpret_cast<size_t *>(rhs) = size;
        }

        void add_size(void *rhs) {
            *reinterpret_cast<size_t *>(rhs) += 1;
        }

        void dec_size(void *rhs) {
            *reinterpret_cast<size_t *>(rhs) -= 1;
        }

        void reserve(char &type, size_t new_capacity) {
            if (type == 'e') {
                big_ = allocate_new_memory(0, new_capacity);
            } else if (type == 's') {
                big_ = copy(&small_, 1, new_capacity, true);
            } else {
                big_ = expand(big_, new_capacity);
            }
            type = 'b';
        }

        void add_usage(void *rhs) {
            *(reinterpret_cast<size_t *>(rhs) + 1) += 1;
        }

        void dec_usage(void *rhs) {
            auto cur = reinterpret_cast<size_t *>(rhs) + 1;
            *cur -= 1;
            if (*cur == 0) {
                delete_all(rhs);
            }
        }

        void set_usage(void *rhs) {
            *(reinterpret_cast<size_t *>(rhs) + 1) = 1;
        }

        size_t get_usage(void *rhs) {
            return *(reinterpret_cast<size_t *>(rhs) + 1);
        }

        size_t get_capacity(char type) const {
            if (type != 'b') {
                return 1;
            } else {
                return get_capacity(big_);
            }
        }

        size_t get_capacity(void *rhs) const {
            return *(reinterpret_cast<size_t *>(rhs) + 2);
        }

        void set_capacity(void *rhs, size_t capacity) {
            *(reinterpret_cast<size_t *>(rhs) + 2) = capacity;
        }

        void shrink_to_fit(void *rhs) {
            auto new_big = copy(big_, get_size(big_), get_size(big_));
            dec_usage(big_);
            big_ = new_big;
        }

        void clear(char &type) {
            if (type == 's') {
                small_.~T();
            } else if (type == 'b') {
                dec_usage(big_);
            }
            type = 'e';
        }

        T const &get_value(char type, size_t index) const {
            if (type == 's') {
                return small_;
            } else {
                return get_value(big_, index);
            }
        }

        T &get_value(char type, size_t index) {
            if (type == 's') {
                return small_;
            } else {
                make_unique(type);
                return get_value(big_, index);
            }
        }

        T const &get_value(void *rhs, size_t index) const {
            return *(begin(rhs) + index);
        }

        T &get_value(void *rhs, size_t index) {
            return *(begin(rhs) + index);
        }

        void set_value(void *rhs, size_t index, T const &val) {
            new(begin(rhs) + index) T(val);
        }

        iterator insert(char &type, size_t m, T const &val) {
            if (m == get_size(type)) {
                push_back(val, type);
            } else if (type == 'e') {
                new(&small_) T(val);
                type = 's';
            } else {
                if (type == 's' || get_size(big_) == get_capacity(big_) || !is_unique(type)) {
                    auto local_copy = std::make_unique<T>(val);
                    if (type == 's') {
                        big_ = copy(&small_, 1, 10, true);
                        type = 'b';
                    } else if (get_size(big_) == get_capacity(big_)) {
                        big_ = expand(big_);
                    } else {
                        make_unique(type);
                    }
                    real_insert(m, *local_copy.get());
                } else {
                    real_insert(m, val);
                }
            }
            return begin(type) + m;
        }

        iterator erase(char &type, size_t m, size_t l) {
            if (l == get_size(type)) {
                for (size_t i = 0; i < l - m; i++) {
                    pop_back(type);
                }
            } else if (type == 's') {
                if (m != l) {
                    small_.~T();
                    type = 'e';
                }
            } else if (m != l) {
                make_unique(type);
                auto cur = begin(big_) + m;
                size_t size = get_size(big_);
                for (size_t i = m; i + l - m < size; i++, cur++) {
                    *cur = *(cur + l - m);
                }
                for (size_t i = size - l + m; i < size; i++, cur++) {
                    cur->~T();
                }
                if (size == l - m) {
                    free(big_);
                    big_ = nullptr;
                    type = 'e';
                } else {
                    set_size(big_, size - l + m);
                }
            }
            return begin(type) + l - m;
        }

    private:
        T small_;
        void *big_;

        void real_insert(size_t m, T const &val) {
            size_t size = get_size(big_);
            set_value(big_, size, get_value(big_, size - 1));
            add_size(big_);
            auto cur = begin('b') + size - 1;
            for (size_t i = size - 1; i > m; i--, cur--) {
                *cur = *(cur - 1);
            }
            *cur = val;
        }
    } data_;
};

template<typename V>
bool operator==(vector<V> const &a, vector<V> const &b) {
    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

template<typename V>
bool operator!=(vector<V> const &a, vector<V> const &b) {
    return !(a == b);
}

template<typename V>
bool operator<(vector<V> const &a, vector<V> const &b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template<typename V>
bool operator>(vector<V> const &a, vector<V> const &b) {
    return b < a;
}

template<typename V>
bool operator<=(vector<V> const &a, vector<V> const &b) {
    return a == b || a < b;
}

template<typename V>
bool operator>=(vector<V> const &a, vector<V> const &b) {
    return a == b || b < a;
}

template<typename V>
void swap(vector<V> &a, vector<V> &b) {
    if (&a != &b) {
        a.data_.swap(a.type_, b.type_, b.data_);
    }
}

#endif //VECTOR_VECTOR_H