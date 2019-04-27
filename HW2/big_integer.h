//
// Created by gaporf on 19.04.19.
//

#ifndef HW2_BIG_INTEGER_H
#define HW2_BIG_INTEGER_H

#include <vector>
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
    std::vector<uint64_t> _number;
    bool _sign;

    static void _add_by_cnst(std::vector<uint64_t> &a, uint64_t b, size_t pos = 0);

    static void _add(std::vector<uint64_t> &a, std::vector<uint64_t> const &b, size_t pos = 0);

    bool _sub(std::vector<uint64_t> &a, std::vector<uint64_t> const &b, size_t pos = 0);

    void _mul(std::vector<uint64_t> a, std::vector<uint64_t> const &b, std::vector<uint64_t> &c);

    std::vector<uint64_t> _mul_by_cnst(std::vector<uint64_t> a, uint64_t const &b);

    void _div_by_cnst(std::vector<uint64_t> &a, size_t k);

    big_integer _div(big_integer rhs, bool mode);

    bool _bit_operation(std::vector<uint64_t> &a, bool sign_a, std::vector<uint64_t> b, bool sign_b, uint64_t f(uint64_t, uint64_t));

    static void _inv(std::vector<uint64_t> &a);

    bool _less(big_integer const &rhs, size_t pos = 0) const;

    bool _less(std::vector<uint64_t> const &a, std::vector<uint64_t> const &b, size_t pos = 0) const;
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

#endif //HW2_BIG_INTEGER_H