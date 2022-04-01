#ifndef INTEGERSTRING_HPP_
#define INTEGERSTRING_HPP_

#include <algorithm>
#include <string>

namespace integerstring {

bool lt(const std::string a, const std::string& b) {
    if (a.size() == b.size())
        return a.compare(b) < 0;
    else
        return a.size() < b.size();
}

bool le(const std::string a, const std::string& b) {
    if (a.size() == b.size())
        return a.compare(b) <= 0;
    else
        return a.size() < b.size();
}

bool gt(const std::string a, const std::string& b) {
    if (a.size() == b.size())
        return a.compare(b) > 0;
    else
        return a.size() > b.size();
}

bool ge(const std::string a, const std::string& b) {
    if (a.size() == b.size())
        return a.compare(b) >= 0;
    else
        return a.size() > b.size();
}

bool eq(const std::string a, const std::string& b) { return a.compare(b) == 0; }

void add_inplace(std::string& a, const std::string& b) {
    int carry = 0;
    size_t add_len = std::min(b.size(), a.size());
    if (b.size() > a.size()) a.insert(0, b.substr(0, b.size() - a.size()));
    size_t idx = a.size() - 1;
    size_t idx_o = b.size() - 1;
    for (size_t i = 0; i < add_len; i++) {
        int sum = b[idx_o--] - '0' + a[idx] - '0' + carry;
        a[idx--] = sum % 10 + '0';
        carry = sum / 10;
    }
    for (size_t i = add_len; i < a.size(); i++) {
        int sum = a[idx] - '0' + carry;
        a[idx--] = sum % 10 + '0';
        carry = sum / 10;
    }
    if (carry > 0) {
        a.insert(0, "0");
        a[0] = carry + '0';
    }
}

std::string add(const std::string& a, const std::string& b) {
    std::string r = a;
    add_inplace(r, b);
    return r;
}

void sub_inplace(std::string& a, const std::string& b) {
    int carry = 0;
    size_t idx = a.size() - 1;
    size_t idx_o = b.size() - 1;
    for (size_t i = 0; i < b.size(); i++) {
        int diff = a[idx] - b[idx_o--] - carry;
        carry = 0;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        }
        a[idx--] = diff + '0';
    }
    for (size_t i = b.size(); i < a.size(); i++) {
        int diff = a[idx] - carry - '0';
        if (diff < 0) {
            diff += 10;
            carry = 1;
            a[idx--] = diff + '0';
        } else {
            a[idx--] = diff + '0';
            carry = 0;
            break;
        }
    }
    if (carry > 0) a[0] -= carry;
    a.erase(a.begin(), std::find_if_not(a.begin(), a.end(), [](char c) { return c == '0'; }));
    if (a.empty()) a = "0";
}

std::string sub(const std::string& a, const std::string& b) {
    std::string result = a;
    sub_inplace(result, b);
    return result;
}

std::string mul_1digit(const std::string& a, char digit) {
    std::string result;
    int carry = 0;
    result = a;
    for (size_t i = a.size(); i > 0; i--) {
        int mul = (a[i - 1] - '0') * (digit - '0') + carry;
        result[i - 1] = mul % 10 + '0';
        carry = mul / 10;
    }
    if (carry > 0) result.insert(0, 1, carry + '0');
    return result;
}

std::string mul(const std::string& a, const std::string& b) {
    std::string r;
    if (a.size() == 0 || b.size() == 0) return r;
    std::string partial;
    std::string tenth;
    for (size_t i = 0; i < b.size(); i++) {
        std::string result_1d = mul_1digit(a, b[b.size() - i - 1]);
        if (i > 0) {
            tenth += "0";
            result_1d.insert(result_1d.size(), tenth);
        }
        r = add(partial, result_1d);
        if (i != b.size() - 1) partial = r;
    }
    return r;
}

void mul10(std::string& a) { a.resize(a.size() + 1, '0'); }

void div10(std::string& a) { a.resize(a.size() - 1); }

std::string pow10(size_t n) {
    std::string s(n + 1, '0');
    s[0] = '1';
    return s;
}

std::string div(const std::string& a, const std::string& b, std::string& r) {
    // cf http://compoasso.free.fr/primelistweb/page/prime/euclide.php
    // Deuxieme implementation
    std::string q = "0";
    std::string a0 = a;
    std::string n("1");
    std::string aux("0");
    r = a;
    while (ge(r, b)) {
        while (le(mul(b, n), a0)) mul10(n);
        div10(n);
        aux = mul(b, n);
        while (ge(r, aux)) {
            sub_inplace(r, aux);
            add_inplace(q, n);
        }
        a0 = r;
        n = "1";
    }
    return q;
}

}  // namespace integerstring

#if 0
class IntegerString {
 public:
    explicit IntegerString(const std::string& s = "") : s_(s) {}
    explicit IntegerString(std::string& s) : s_(s) {}
    const std::string& str() { return s_; }

    std::ostream& operator<<(std::ostream& o) { return o << s_; }

    IntegerString& operator=(const std::string& other) {
        s_ = other;
        return *this;
    }
    IntegerString& operator=(const IntegerString& other) {
        s_ = other.s_;
        return *this;
    }

    IntegerString& operator+=(const IntegerString& other) { return *this += other.s_; }
    IntegerString& operator+=(const std::string& other) {
        integerstring::add_inplace(s_, other);
        return *this;
    }

    IntegerString& operator-=(const IntegerString& other) { return *this -= other.s_; }
    IntegerString& operator-=(const std::string& other) {
        integerstring::sub_inplace(s_, other);
        return *this;
    }

    static std::string sub(const std::string& a, const std::string& b) {
        std::string r = a;
        integerstring::sub_inplace(r, b);
        return r;
    }

    IntegerString& operator*=(std::string& other) {
        std::string result;
        s_ = integerstring::mul(s_, other);
        return *this;
    }
    IntegerString& operator*=(IntegerString& other) { return *this *= other.s_; }

    IntegerString operator*(std::string& other) {
        IntegerString result;
        result.s_ = integerstring::mul(s_, other);
        return result;
    }
    IntegerString operator*(IntegerString& other) { return (*this) * other.s_; }

    bool operator==(const std::string& other) { return integerstring::eq(this->s_, other); }
    bool operator==(const IntegerString& other) { return this->s_ == other.s_; }
    bool operator<=(const std::string& other) { return integerstring::le(this->s_, other); }
    bool operator<=(const IntegerString& other) { return *this <= other.s_; }
    bool operator<(const std::string& other) { return integerstring::lt(this->s_, other); }
    bool operator<(const IntegerString& other) { return *this < other.s_; }
    bool operator>=(const std::string& other) { return integerstring::ge(this->s_, other); }
    bool operator>=(const IntegerString& other) { return *this >= other.s_; }
    bool operator>(const std::string& other) { return integerstring::gt(this->s_, other); }
    bool operator>(const IntegerString& other) { return *this > other.s_; }

    IntegerString operator/(IntegerString& other) {
        IntegerString q, r;
        div(*this, other, q, r);
        return q;
    }

 private:
    std::string s_;
};
#endif

#endif  // INTEGERSTRING_HPP_
