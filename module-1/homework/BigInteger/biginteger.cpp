#include <iostream>
#include "biginteger.h"

BigInteger::BigInteger(std::string s) {
    length = s.size();
    for (int digit = 0; digit < length; digit++) {
        number.push_back(s[length - digit - 1] - '0');
    }
}

BigInteger::BigInteger() {
    this->positive = true;
    this->length = 1;
    std::vector<int> num(1, 0);
    this->number = num;
}

BigInteger::BigInteger(std::vector<int> &a, bool sign) {
    for (int digit = 0; digit < (int) a.size(); ++digit) {
        this->number.push_back(a[digit]);
    }
    this->length = (int) a.size();
    this->positive = sign;
};

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
    length = number.size();
}

std::string BigInteger::toString() {
    std::string str;
    if (!(this->positive)) {
        str.push_back('-');
    }
    for (int digit = this->length - 1; digit >= 0; digit--) {
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
    for (int digit = 0; digit < num.length; ++digit) {
        os << num.number[num.length - digit - 1];
    }
    return os;
}

std::istream &operator>>(std::istream &is, BigInteger &num) {
    std::string str;
    is >> str;
    num.number.clear();
    if (str[0] == '-') {
        num.positive = false;
        num.length = (int) str.size() - 1;
        for (int digit = 0; digit < num.length; digit++) {
            num.number.push_back(str[num.length - digit] - '0');
        }
    } else {
        num.positive = true;
        num.length = (int) str.size();
        for (int digit = 0; digit < num.length; digit++) {
            num.number.push_back(str[num.length - digit - 1] - '0');
        }
    }
    return is;
}

bool operator==(const BigInteger &left, const BigInteger &right) {
    if (left.positive == right.positive && left.length == right.length) {
        for (int digit = 0; digit < left.length; ++digit) {
            if (left.number[digit] != right.number[digit])
                return false;
        }
    } else {
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

BigInteger::operator bool() {
    if (this->length == 1 && this->number[0] == 0) {
        return false;
    } else
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
    } else if (!right.positive)
        return left - (-right);
    int carry = 0;
    for (int digit = 0; digit < std::max(left.length, right.length) || carry != 0; digit++) {
        if (digit == left.length) {
            left.number.push_back(0);
            left.length++;
        }
        left.number[digit] += carry + (digit < right.length ? right.number[digit] : 0);
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
    for (int digit = 0; digit < right.length || carry; digit++) {
        left.number[digit] -= carry + (digit < right.length ? right.number[digit] : 0);
        carry = (left.number[digit] < 0);
        if (carry == 1) {
            left.number[digit] += 10;
        }
    }
    left.length = left.number.size();
    while (left.number.back() == 0 && left.number.size() > 1) {
        left.number.pop_back();
    }
    left.length = left.number.size();
    if (left.number[0] == 0)
        left.positive = true;
    return left;
}

BigInteger operator*(const BigInteger &left, const BigInteger &right) {
    int max_size = (left.length >= right.length ? left.length : right.length);
    std::vector<int> a = left.number;
    std::vector<int> b = right.number;
    BigInteger::extend(a, max_size);
    BigInteger::extend(b, max_size);
    std::vector<int> res = BigInteger::KaratsubaMultiplication(a, b);
    for (int i = 0; i < res.size() - 1; ++i) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    res.push_back(res.back() / 10);
    while (res.size() > 1 && res.back() == 0)
        res.pop_back();
    BigInteger answer(res, left.positive == right.positive);
    return answer;
};

BigInteger operator/(const BigInteger &dividend, const BigInteger &divisor) {
    std::vector<int> answer(dividend.number.size());
    bool sign = (dividend.positive == divisor.positive);
    BigInteger dividend_ = dividend;
    BigInteger divisor_ = divisor;
    dividend_.positive = true;
    divisor_.positive = true;
    if (dividend_ < divisor_)
        return (BigInteger(0));
    for (int digit = (int) dividend.number.size() - 1; digit >= 0; --digit) {
        answer[digit] = 9;
        while (BigInteger(answer, true) * divisor_ > dividend_ && answer[digit] > 0) {
            answer[digit]--;
        }
    }
    while (answer.back() == 0 && !answer.empty()) {
        answer.pop_back();
    }
    return (BigInteger(answer, sign));
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
    int len = (left.size() >= right.size() ? left.size() : right.size());
    len += len % 2;
    while (left.size() < len)
        left.push_back(0);
    while (right.size() < len) {
        right.push_back(0);
    }
    std::vector<int> res(2 * len);

    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            res[i + j] += left[i] * right[j];
        }
    }
    return res;
}

std::vector<int> BigInteger::KaratsubaMultiplication(std::vector<int> &left, std::vector<int> &right) {
    int len = (left.size() >= right.size() ? left.size() : right.size());
    len += len % 2;
    while (left.size() < len)
        left.push_back(0);
    while (right.size() < len) {
        right.push_back(0);
    }
    std::vector<int> result(2 * len);
    if (len <= 2) {
        return NaiveMultiplication(left, right);
    }
    int k = len / 2;

    std::vector<int> left_r{left.begin(), left.begin() + k};
    std::vector<int> left_l{left.begin() + k, left.end()};
    std::vector<int> right_r{right.begin(), right.begin() + k};
    std::vector<int> right_l{right.begin() + k, right.end()};

    std::vector<int> P1 = KaratsubaMultiplication(left_l, right_l);
    std::vector<int> P2 = KaratsubaMultiplication(left_r, right_r);

    std::vector<int> left_lr(k);
    std::vector<int> right_rl(k);

    for (int i = 0; i < k; ++i) {
        left_lr[i] = left_l[i] + left_r[i];
        right_rl[i] = right_l[i] + right_r[i];
    }

    std::vector<int> P3 = KaratsubaMultiplication(left_lr, right_rl);

    for (int i = 0; i < len; ++i) {
        P3[i] -= P2[i] + P1[i];
    }

    for (int i = 0; i < len; ++i) {
        result[i] = P2[i];
    }

    for (int i = len; i < 2 * len; ++i) {
        result[i] = P1[i - len];
    }

    for (int i = k; i < len + k; ++i) {
        result[i] += P3[i - k];
    }
    return result;
}
