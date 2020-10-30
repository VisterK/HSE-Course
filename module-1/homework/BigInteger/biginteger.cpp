#include <iostream>
#include "biginteger.h"

BigInteger::BigInteger(std::string s) {
    for (int digit = 0; digit < (int)s.size(); digit++) {
        number.push_back(s[s.size() - digit - 1] - '0');
    }
}

BigInteger::BigInteger() {
    this->positive = true;
    std::vector<int> num(1, 0);
    this->number = num;
}

BigInteger::BigInteger(std::vector<int> &a, bool sign) {
    for (int digit = 0; digit < (int) a.size(); ++digit) {
        this->number.push_back(a[digit]);
    }
    this->positive = sign;
}

BigInteger::BigInteger(int x) {
    if (x < 0) {
        positive = false;
        x = -x;
    } else {
        positive = true;
    }
    if (x == 0) {
        number.push_back(0);
        positive = true;
    }
    while (x > 0) {
        number.push_back(x % 10);
        x /= 10;
    }
}

std::string BigInteger::toString() {
    std::string str;
    if (!(this->positive)) {
        str.push_back('-');
    }
    for (int digit = this->number.size() - 1; digit >= 0; digit--) {
        str.push_back((char) (this->number[digit] + '0'));
    }
    return str;
}

BigInteger BigInteger::operator-() {
    this->positive = !this->positive;
    return *this;
}

BigInteger &BigInteger::operator++() {
    BigInteger tmp = 1;
    *this += tmp;
    return *this;
}

BigInteger &BigInteger::operator--() {
    BigInteger tmp = 1;
    *this -= tmp;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    ++(*this);
    return temp;
}

BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    --(*this);
    return temp;
}

std::ostream &operator<<(std::ostream &os, const BigInteger &num) {
    if (!num.positive) {
        os << "-";
    }
    for (int digit = 0; digit < num.number.size(); ++digit) {
        os << num.number[num.number.size() - digit - 1];
    }
    return os;
}

std::istream &operator>>(std::istream &is, BigInteger &num) {
    std::string str;
    is >> str;
    num.number.clear();
    if (str[0] == '-') {
        num.positive = false;
        for (int digit = 0; digit < str.size(); digit++) {
            num.number.push_back(str[str.size() - digit] - '0');
        }
    }
    else {
        num.positive = true;
        for (int digit = 0; digit < str.size(); digit++) {
            num.number.push_back(str[str.size() - digit - 1] - '0');
        }
    }
    return is;
}

bool operator==(const BigInteger &left, const BigInteger &right) {
    if (left.positive == right.positive && left.number.size() == right.number.size()) {
        for (int digit = 0; digit < left.number.size(); ++digit) {
            if (left.number[digit] != right.number[digit])
                return false;
        }
    }
    else {
        return false;
    }
    return true;
}

bool operator!=(const BigInteger &left, const BigInteger &right) {
    return (!(left == right));
}

bool operator>(const BigInteger &left, const BigInteger &right) {
    if (left == right)
        return false;
    if (left.positive && !right.positive)
        return true;
    if (!left.positive && right.positive)
        return false;
    if (left.positive && right.positive) {
        if (left.number.size() > right.number.size())
            return true;
        if (left.number.size() < right.number.size())
            return false;
        for (int digit = (int) left.number.size() - 1; digit >= 0; digit--) {
            if (left.number[digit] > right.number[digit])
                return true;
            if (left.number[digit] < right.number[digit])
                return false;
        }
    }
    if (left.number.size() < right.number.size())
        return true;
    if (left.number.size() > right.number.size())
        return false;
    for (int digit = (int) left.number.size() - 1; digit >= 0; digit--) {
        if (left.number[digit] < right.number[digit])
            return true;
        if (left.number[digit] > right.number[digit])
            return false;
    }
    return false;


}

bool operator<(const BigInteger &left, const BigInteger &right) {
    return (!(left > right || left == right));
}

bool operator<=(const BigInteger &left, const BigInteger &right) {
    return ((left < right) || (left == right));
}

bool operator>=(const BigInteger &left, const BigInteger &right) {
    return ((left > right) || (left == right));
}

BigInteger::operator bool() const {
    if (this->number[0] == 0) {
        return false;
    }
    else
        return true;
}

BigInteger operator+(const BigInteger &l, const BigInteger &r) {
    BigInteger left = l;
    BigInteger right = r;
    if (!left.positive) {
        if (!right.positive)
            return -(-left + (-right));
        else
            return right - (-left);
    }
    else if (!right.positive)
        return left - (-right);
    int carry = 0;
    for (int digit = 0; digit < std::max(left.number.size(), right.number.size()) || carry != 0; digit++) {
        if (digit == left.number.size()) {
            left.number.push_back(0);
        }
        left.number[digit] += carry + (digit < right.number.size() ? right.number[digit] : 0);
        if (left.number[digit] >= 10) {
            carry = 1;
        } else
            carry = 0;
        if (carry == 1) {
            left.number[digit] -= 10;
        }
    }
    return left;
}

BigInteger operator-(const BigInteger &l, const BigInteger &r) {
    BigInteger left = l;
    BigInteger right = r;
    if (!right.positive)
        return left + (-right);
    else if (!left.positive)
        return -(-left + right);
    else if (left < right)
        return -(right - left);
    int carry = 0;
    for (int digit = 0; digit < right.number.size() || carry; digit++) {
        left.number[digit] -= carry + (digit < right.number.size() ? right.number[digit] : 0);
        carry = (left.number[digit] < 0);
        if (carry == 1) {
            left.number[digit] += 10;
        }
    }
    while (left.number.back() == 0 && left.number.size() > 1) {
        left.number.pop_back();
    }
    if (left.number[0] == 0)
        left.positive = true;
    return left;
}

BigInteger operator*(const BigInteger &left, const BigInteger &right) {
    int max_size = (left.number.size() >= right.number.size() ? left.number.size() : right.number.size());
    std::vector<int> a = left.number;
    std::vector<int> b = right.number;
    BigInteger::extend(a, max_size);
    BigInteger::extend(b, max_size);
    std::vector<int> res = BigInteger::KaratsubaMultiplication(a, b);
    res.push_back(0);
    for (int i = 0; i < res.size() - 1; ++i) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    res.back() %= 10;
    while (res.size() > 1 && res.back() == 0)
        res.pop_back();
    BigInteger answer(res, left.positive == right.positive);
    return answer;
}

BigInteger operator/(const BigInteger &dividend, const BigInteger &divisor) {
    std::vector<int> answer(dividend.number.size());
    bool sign = (dividend.positive == divisor.positive);
    if (dividend < divisor)
        return (0);
    BigInteger result(answer,true);
    for (int digit = (int) dividend.number.size() - 1; digit >= 0; --digit) {
        result.number[digit] = 9;
        while (result * divisor > dividend  && result.number[digit] > 0) {
            result.number[digit]--;
        }
    }
    while (result.number.back() == 0 && !result.number.empty()) {
        result.number.pop_back();
    }
    result.positive = sign;
    return (result);
}

BigInteger operator%(const BigInteger &left, const BigInteger &right) {
    BigInteger quotient = left / right;
    BigInteger answer = left - right * quotient;
    return answer;

}

BigInteger &BigInteger::operator+=(const BigInteger &num) {
    *this = *this + num;
    return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger &num) {
    *this = *this - num;
    return *this;
}

BigInteger &BigInteger::operator*=(const BigInteger &num) {
    *this = *this * num;
    return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger &num) {
    *this = *this / num;
    return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &num) {
    *this = *this % num;
    return *this;
}


void BigInteger::extend(std::vector<int> &a, int length) {
    while (length & (length - 1))
        length++;
    a.resize(length);
}

std::vector<int> BigInteger::NaiveMultiplication(std::vector<int> &left, std::vector<int> &right) {
    int lenght = (left.size() >= right.size() ? left.size() : right.size());
    lenght += lenght % 2;
    while (left.size() < lenght)
        left.push_back(0);
    while (right.size() < lenght) {
        right.push_back(0);
    }
    std::vector<int> result(2 * lenght);

    for (int i = 0; i < lenght; ++i) {
        for (int j = 0; j < lenght; ++j) {
            result[i + j] += left[i] * right[j];
        }
    }
    return result;
}

std::vector<int> BigInteger::KaratsubaMultiplication(std::vector<int> &left, std::vector<int> &right) {
    int lenght = (left.size() >= right.size() ? left.size() : right.size());
    lenght += lenght % 2;
    while (left.size() < lenght)
        left.push_back(0);
    while (right.size() < lenght) {
        right.push_back(0);
    }
    std::vector<int> result(2 * lenght);
    if (lenght <= 2) {
        return NaiveMultiplication(left, right);
    }
    int middle = lenght / 2;

    std::vector<int> left_r{left.begin(), left.begin() + middle};
    std::vector<int> left_l{left.begin() + middle, left.end()};
    std::vector<int> right_r{right.begin(), right.begin() + middle};
    std::vector<int> right_l{right.begin() + middle, right.end()};

    std::vector<int> intermediate_first = KaratsubaMultiplication(left_l, right_l);
    std::vector<int> intermediate_second = KaratsubaMultiplication(left_r, right_r);

    std::vector<int> left_lr(middle);
    std::vector<int> right_rl(middle);

    for (int i = 0; i < middle; ++i) {
        left_lr[i] = left_l[i] + left_r[i];
        right_rl[i] = right_l[i] + right_r[i];
    }

    std::vector<int> intermediate_third = KaratsubaMultiplication(left_lr, right_rl);

    for (int i = 0; i < lenght; ++i) {
        intermediate_third[i] -= intermediate_second[i] + intermediate_first[i];
    }

    for (int i = 0; i < lenght; ++i) {
        result[i] = intermediate_second[i];
    }

    for (int i = lenght; i < 2 * lenght; ++i) {
        result[i] = intermediate_first[i - lenght];
    }

    for (int i = middle; i < lenght + middle; ++i) {
        result[i] += intermediate_third[i - middle];
    }
    return result;
}
