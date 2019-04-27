//
// Created by gaporf on 19.04.19.
//

#include "big_integer.h"
#include <iostream>
#include <algorithm>

const __uint128_t BASE2 = static_cast<__uint128_t>(1) << 64;
const __uint128_t NORM = static_cast<__uint128_t>(1) << 63;
const __uint128_t BASES10[19] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000,
                                 10000000000, 100000000000, 1000000000000, 10000000000000,
                                 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000,
                                 1000000000000000000};
const __uint128_t BASE10 = BASES10[18];

big_integer::big_integer() : _number(), _sign(false) {}

big_integer::big_integer(big_integer const &other) = default;

big_integer::big_integer(int32_t a) {
    if (a < 0) {
        _sign = true;
        _number.push_back(-static_cast<int64_t>(a));
    } else {
        _sign = false;
        if (a > 0) {
            _number.push_back(a);
        }
    }
}

big_integer::big_integer(std::string const &str) {
    size_t i;
    if (str[0] == '-') {
        _sign = true;
        i = 1;
    } else {
        _sign = false;
        i = 0;
    }
    while (i < str.length() && str[i] == '0') {
        i++;
    }
    if (i == str.length()) {
        _sign = false;
    } else {
        for (; i < str.length(); i += 18) {
            __uint128_t res = 0;
            for (size_t j = i; j < str.length() && j < i + 18; j++) {
                res = 10 * res + (str[j] - '0');
            }
            _number = _mul_by_cnst(_number, BASES10[std::min(static_cast<size_t>(18), str.length() - i)]);
            _add_by_cnst(_number, res);
        }
    }
}

big_integer::~big_integer() = default;

big_integer &big_integer::operator=(big_integer const &rhs) = default;

big_integer &big_integer::operator+=(big_integer const &rhs) {
    if (_sign == rhs._sign) {
        _add(_number, rhs._number);
        return *this;
    } else {
        return *this -= (-rhs);
    }
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    if (_sign == rhs._sign) {
        _sign = _sign != _sub(_number, rhs._number) && !_number.empty();
        return *this;
    } else {
        return *this += (-rhs);
    }
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    _sign ^= rhs._sign;
    _mul(_number, rhs._number, _number);
    return *this;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    *this = _div(rhs, false);
    return *this;
}


big_integer &big_integer::operator%=(big_integer const &rhs) {
    *this = _div(rhs, true);
    return *this;
}

big_integer &big_integer::operator&=(big_integer const &rhs) {
    if (rhs._number.empty()) {
        *this = 0;
    } else if (!_number.empty()) {
        _sign = _bit_operation(_number, _sign, rhs._number, rhs._sign,
                               [](uint64_t a, uint64_t b) {
                                   return a & b;
                               }
        );
    }
    return *this;
}

big_integer &big_integer::operator|=(big_integer const &rhs) {
    if (_number.empty()) {
        *this = rhs;
    } else if (!rhs._number.empty()) {
        _sign = _bit_operation(_number, _sign, rhs._number, rhs._sign,
                               [](uint64_t a, uint64_t b) {
                                   return a | b;
                               }
        );
    }
    return *this;
}

big_integer &big_integer::operator^=(big_integer const &rhs) {
    if (_number.empty()) {
        *this = rhs;
    } else if (!rhs._number.empty()) {
        _sign = _bit_operation(_number, _sign, rhs._number, rhs._sign,
                               [](uint64_t a, uint64_t b) {
                                   return a ^ b;
                               }
        );
    }
    return *this;
}

big_integer &big_integer::operator<<=(int32_t rhs) {
    while (rhs > 0) {
        int32_t d = std::min(30, rhs);
        rhs -= d;
        uint64_t r = 1;
        while (d--) {
            r *= 2;
        }
        _number = _mul_by_cnst(_number, r);
    }
    return *this;
}

big_integer &big_integer::operator>>=(int32_t rhs) {
    while (rhs > 0) {
        char r = _number[0] % 2;
        _div_by_cnst(_number, 1);
        if (_sign && r > 0) {
            _add_by_cnst(_number, r);
        }
        --rhs;
    }
    return *this;
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    big_integer r = *this;
    r._sign ^= !_number.empty();
    return r;
}

big_integer big_integer::operator~() const {
    return -*this - 1;
}

big_integer &big_integer::operator++() {
    return *this += 1;
}

big_integer big_integer::operator++(int) {
    big_integer r = *this;
    *this += 1;
    return r;
}

big_integer &big_integer::operator--() {
    return *this -= 1;
}

big_integer big_integer::operator--(int) {
    big_integer r = *this;
    *this -= 1;
    return r;
}

big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const &b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const &b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const &b) {
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const &b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const &b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const &b) {
    return a ^= b;
}

big_integer operator<<(big_integer a, int32_t rhs) {
    return a <<= rhs;
}

big_integer operator>>(big_integer a, int32_t rhs) {
    return a >>= rhs;
}

bool operator==(big_integer const &a, big_integer const &b) {
    return a._sign == b._sign && a._number == b._number;
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a == b);
}

bool operator<(big_integer const &a, big_integer const &b) {
    if (!a._sign && !b._sign) {
        return a._less(b);
    } else if (a._sign && b._sign) {
        return b._less(a);
    } else {
        return a._sign;
    }
}

bool operator>(big_integer const &a, big_integer const &b) {
    return b < a;
}

bool operator<=(big_integer const &a, big_integer const &b) {
    return a == b || a < b;
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return b <= a;
}

std::string to_string(__uint128_t num) {
    if (num == 0) {
        return "0";
    }
    std::string ans;
    while (num > 0) {
        ans += static_cast<char>('0' + num % 10);
        num /= 10;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

std::string to_string(big_integer const &a) {
    if (a._number.empty()) {
        return "0";
    }
    std::string ans;
    std::vector<uint64_t> number = a._number;
    std::reverse(number.begin(), number.end());
    while (!number.empty()) {
        __uint128_t cur = 0;
        size_t i = 0;
        std::vector<uint64_t> new_number;
        while (cur < BASE10 && i < number.size()) {
            cur = BASE2 * cur + number[i];
            i++;
        }
        std::string add;
        if (cur >= BASE10) {
            new_number.push_back(cur / BASE10);
            cur %= BASE10;
            while (i < number.size()) {
                cur = BASE2 * cur + number[i];
                new_number.push_back(cur / BASE10);
                cur %= BASE10;
                i++;
            }
            for (size_t j = 1; j < 18; j++) {
                if (cur < BASES10[j]) {
                    ans.append(18 - j, '0');
                    break;
                }
            }
        }
        add += to_string(cur);
        std::reverse(add.begin(), add.end());
        ans += add;
        number = new_number;
    }
    if (a._sign) {
        ans += "-";
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

void big_integer::_add_by_cnst(std::vector<uint64_t> &a, uint64_t b, size_t pos) {
    if (b == 0) {
        return;
    }
    a.resize(std::max(a.size(), pos + 1), 0);
    if (static_cast<__uint128_t>(a[pos]) + b >= BASE2) {
        a[pos] += b;
        pos++;
        while (pos < a.size() && a[pos] == BASE2 - 1) {
            a[pos] = 0;
            pos++;
        }
        if (pos < a.size()) {
            a[pos]++;
        } else {
            a.push_back(1);
        }
    } else {
        a[pos] += b;
    }
}

void big_integer::_add(std::vector<uint64_t> &a, std::vector<uint64_t> const &b, size_t pos) {
    uint64_t carry = 0;
    a.resize(std::max(b.size() + pos, a.size()), 0);
    for (size_t i = pos; i - pos != b.size(); i++) {
        uint64_t res = a[i] + b[i - pos] + carry;
        carry = (BASE2 - a[i] < b[i - pos] + carry);
        a[i] = res;
    }
    if (carry == 1) {
        size_t i = b.size() + pos;
        while (i < a.size() && a[i] == BASE2 - 1) {
            a[i] = 0;
        }
        if (i < a.size()) {
            a[i]++;
        } else {
            a.push_back(1);
        }
    }
}

bool big_integer::_sub(std::vector<uint64_t> &a, std::vector<uint64_t> const &b, size_t pos) {
    uint64_t borrow = 0;
    a.resize(std::max(a.size(), b.size() + pos));
    for (size_t i = pos; i < std::max(a.size(), b.size() + pos); i++) {
        uint64_t res = a[i] - (i < b.size() + pos ? b[i - pos] : 0) - borrow;
        borrow = (a[i] - borrow < (i < b.size() + pos ? b[i - pos] : 0));
        a[i] = res;
    }
    if (borrow == 1) {
        size_t i = 0;
        while (i < a.size() && a[i] == 0) {
            i++;
        }
        if (i < a.size()) {
            a[i] = -a[i];
        }
        i++;
        while (i < a.size()) {
            a[i] = ~a[i];
            i++;
        }
    }
    while (!a.empty() && a.back() == 0) {
        a.pop_back();
    }
    return borrow == 1;
}


void big_integer::_mul(std::vector<uint64_t> a, std::vector<uint64_t> const &b, std::vector<uint64_t> &c) {
    if (a.empty() || b.empty()) {
        return;
    }
    c.assign(a.size() + b.size(), 0);
    for (size_t i = 0; i < b.size(); i++) {
        uint64_t carry = 0;
        std::vector<uint64_t> add(a.size() + 1);
        for (size_t j = 0; j < a.size(); j++) {
            __uint128_t res = static_cast<__uint128_t>(b[i]) * a[j] + carry;
            add[j] = res;
            carry = res / BASE2;
        }
        add.back() = carry;
        _add(c, add, i);
    }
    while (!c.empty() && c.back() == 0) {
        c.pop_back();
    }
}

std::vector<uint64_t> big_integer::_mul_by_cnst(std::vector<uint64_t> a, uint64_t const &b) {
    if (b == 0) {
        return std::vector<uint64_t>();
    } else {
        __uint128_t carry = 0;
        for (size_t i = 0; i < a.size(); i++) {
            __uint128_t res = carry + static_cast<__uint128_t>(a[i]) * b;
            a[i] = res;
            carry = res / BASE2;
        }
        if (carry > 0) {
            a.push_back(carry);
        }
        return a;
    }
}

void big_integer::_div_by_cnst(std::vector<uint64_t> &a, size_t k) {
    __uint128_t cur = 0;
    size_t i = a.size(),
        j = a.size();
    uint64_t g = (static_cast<uint64_t>(1) << k);
    while (i > 0 && cur < g) {
        cur = BASE2 * cur + a[--i];
    }
    if (cur >= g) {
        a[--j] = cur >> k;
        cur &= g - 1;
        while (i > 0) {
            cur = BASE2 * cur + a[--i];
            a[--j] = cur >> k;
            cur &= g - 1;
        }
    }
    a.erase(a.begin(), a.begin() + j);
}

big_integer big_integer::_div(big_integer rhs, bool mode) {
    bool new_sign;
    if (!mode) {
        new_sign = _sign ^ rhs._sign;
    } else {
        new_sign = _sign;
    }
    _sign = false;
    uint64_t r = 1;
    size_t k = 0;
    while (rhs._number.back() * r < NORM / 2) {
        r *= 2;
        k++;
    }
    rhs._number = _mul_by_cnst(rhs._number, r);
    while (rhs._number.back() < NORM) {
        rhs._number = _mul_by_cnst(rhs._number, 2);
        r *= 2;
        k++;
    }
    if (r != 1) {
        _number = _mul_by_cnst(_number, r);
    }
    size_t n = rhs._number.size(),
            m = _number.size() - n;
    std::vector<uint64_t> q(m + 1);
    if (!_less(rhs, m)) {
        q[m] = 1;
        _sub(_number, rhs._number, m);
    } else {
        q[m] = 0;
    }
    for (size_t j = m; j > 0;) {
        j--;
        q[j] = ((n + j < _number.size() ? _number[n + j] : 0) * BASE2 +
                (n + j - 1 < _number.size() ? _number[n + j - 1] : 0)) / rhs._number[n - 1];
        _sign ^= _sub(_number, _mul_by_cnst(rhs._number, q[j]), j);
        while (_sign) {
            q[j]--;
            _sign ^= _sub(_number, rhs._number, j);
            if (_number.empty()) {
                _sign = false;
            }
        }
    }
    if (!mode) {
        _number = q;
        while (!_number.empty() && _number.back() == 0) {
            _number.pop_back();
        }
    } else {
        _div_by_cnst(_number, k);
    }
    _sign = new_sign & !_number.empty();
    return *this;
}

bool big_integer::_bit_operation(std::vector<uint64_t> &a, bool sign_a, std::vector<uint64_t> b, bool sign_b,
                                 uint64_t f(uint64_t, uint64_t)) {
    while (a.size() < b.size()) {
        a.push_back(0);
    }
    while (b.size() < a.size()) {
        b.push_back(0);
    }
    if (sign_a) {
        _inv(a);
        _add_by_cnst(a, 1);
    }
    if (sign_b) {
        _inv(b);
        _add_by_cnst(b, 1);
    }
    for (size_t i = 0; i < a.size(); i++) {
        a[i] = f(a[i], b[i]);
    }
    bool res = f(sign_a, sign_b);
    if (res) {
        _sub(a, std::vector<uint64_t>(1, 1));
        _inv(a);
    }
    while (!a.empty() && a.back() == 0) {
        a.pop_back();
    }
    return res;
}

void big_integer::_inv(std::vector<uint64_t> &a) {
    for (size_t i = 0; i != a.size(); i++) {
        a[i] = ~a[i];
    }
}

bool big_integer::_less(big_integer const &rhs, size_t pos) const {
    return _less(_number, rhs._number, pos);
}

bool big_integer::_less(std::vector<uint64_t> const &a, std::vector<uint64_t> const &b, size_t pos) const {
    if (a.size() < b.size() + pos) {
        return true;
    } else if (a.size() == b.size() + pos) {
        for (size_t i = a.size(); i > pos; i--) {
            if (a[i - 1] < b[i - pos - 1]) {
                return true;
            } else if (a[i - 1] > b[i - pos - 1]) {
                return false;
            }
        }
    }
    return false;
}