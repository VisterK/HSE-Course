#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

class BigInteger {
public:
    BigInteger(std::string s);
    BigInteger();
    std::string toString();
    BigInteger(int x);

    BigInteger operator-();

    BigInteger& operator++();
    BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    friend std::istream& operator>>(std::istream&, BigInteger&);

    friend bool operator==(const BigInteger &left, const BigInteger &right);
    friend bool operator!=(const BigInteger &left, const BigInteger &right);
    friend bool operator<(const BigInteger &left, const BigInteger &right);
    friend bool operator>(const BigInteger &left, const BigInteger &right);
    friend bool operator<=(const BigInteger &left, const BigInteger &right);
    friend bool operator>=(const BigInteger &left, const BigInteger &right);

    operator bool() const;
    operator std::string() const;

    friend BigInteger operator+(const BigInteger &l, const BigInteger &r);
    friend BigInteger operator-(const BigInteger &l, const BigInteger &r);
    friend BigInteger operator*(const BigInteger &left, const BigInteger &right);
    friend BigInteger operator/(const BigInteger &dividend, const BigInteger &divisor);
    friend BigInteger operator%(const BigInteger &left, const BigInteger &right);

    BigInteger& operator+=(const BigInteger &num);
    BigInteger& operator-=(const BigInteger &num);
    BigInteger& operator*=(const BigInteger &num);
    BigInteger& operator/=(const BigInteger &num);
    BigInteger& operator%=(const BigInteger &num);

    static void extend(std::vector<int> &a, int length);
    static std::vector<int> NaiveMultiplication(std::vector<int> &left, std::vector<int> &right);
    static std::vector<int> KaratsubaMultiplication(std::vector<int> &left, std::vector<int> &y);

private:
    bool positive;
    std::vector<int> number;

    BigInteger(std::vector<int> &a, bool sign);

};


#endif