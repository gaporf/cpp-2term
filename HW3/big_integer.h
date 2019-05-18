//
// Created by gaporf on 03.05.19.
//

#ifndef HW3_BIG_INTEGER_H
#define HW3_BIG_INTEGER_H

#include <vector/vector.h>
#include <cstdint>
#include <string>

struct big_integer {
    big_integer();

    big_integer(big_integer const &other);

    big_integer(int32_t a);

    explicit big_integer(std::string const &str);

    ~big_integer();

    big_integer &operator=(big_integer const &rhs);

    big_integer &operator+=(big_integer const &rhs);

    big_integer &operator-=(big_integer const &rhs);

    big_integer &operator*=(big_integer const &rhs);

    big_integer &operator/=(big_integer const &rhs);

    big_integer &operator%=(big_integer const &rhs);

    big_integer &operator&=(big_integer const &rhs);

    big_integer &operator|=(big_integer const &rhs);

    big_integer &operator^=(big_integer const &rhs);

    big_integer &operator<<=(int32_t rhs);

    big_integer &operator>>=(int32_t rhs);

    big_integer operator+() const;

    big_integer operator-() const;

    big_integer operator~() const;

    big_integer &operator++();

    big_integer operator++(int);

    big_integer &operator--();

    big_integer operator--(int);

    friend bool operator==(big_integer const &a, big_integer const &b);

    friend bool operator!=(big_integer const &a, big_integer const &b);

    friend bool operator<(big_integer const &a, big_integer const &b);

    friend bool operator>(big_integer const &a, big_integer const &b);

    friend bool operator<=(big_integer const &a, big_integer const &b);

    friend bool operator>=(big_integer const &a, big_integer const &b);

    friend std::string to_string(big_integer const &a);

private:
    vector _number;
    bool _sign;

    static void add_by_cnst(vector &a, uint64_t b, size_t pos = 0);

    static void add(vector &a, vector const &b, size_t pos = 0);

    bool sub(vector &a, vector const &b, size_t pos = 0);

    void mul(vector a, vector const &b, vector &c);

    vector mul_by_cnst(vector a, uint64_t const &b);

    void div_by_cnst(vector &a, size_t k);

    big_integer div(big_integer rhs, bool mode);

    bool bit_operation(vector &a, bool sign_a, vector b, bool sign_b, uint64_t f(uint64_t, uint64_t));

    static void inv(vector &a);

    bool less(big_integer const &rhs, size_t pos = 0) const;

    bool less(vector const &a, vector const &b, size_t pos = 0) const;
};

big_integer operator+(big_integer a, big_integer const &b);

big_integer operator-(big_integer a, big_integer const &b);

big_integer operator*(big_integer a, big_integer const &b);

big_integer operator/(big_integer a, big_integer const &b);

big_integer operator%(big_integer a, big_integer const &b);

big_integer operator&(big_integer a, big_integer const &b);

big_integer operator|(big_integer a, big_integer const &b);

big_integer operator^(big_integer a, big_integer const &b);

big_integer operator<<(big_integer a, int32_t rhs);

big_integer operator>>(big_integer a, int32_t rhs);

bool operator==(big_integer const &a, big_integer const &b);

bool operator!=(big_integer const &a, big_integer const &b);

bool operator<(big_integer const &a, big_integer const &b);

bool operator>(big_integer const &a, big_integer const &b);

bool operator<=(big_integer const &a, big_integer const &b);

bool operator>=(big_integer const &a, big_integer const &b);

std::string to_string(big_integer const &a);

#endif //HW3_BIG_INTEGER_H