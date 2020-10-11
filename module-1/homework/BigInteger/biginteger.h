#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <istream>

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

class BigInteger {
  int length;
  bool positive;
  std::vector<int> number;
public:
  BigInteger(std::string s);
  BigInteger();
  std::string toString();
  BigInteger(int x);
  BigInteger(std::vector<int> &a, bool sign);

  BigInteger operator- ();

  BigInteger& operator++();
  BigInteger& operator--();

  BigInteger operator++(int);
  BigInteger operator--(int);

  friend std::ostream& operator<<(std::ostream &os, const BigInteger& num) {
    if(!num.positive){
      os << "-";
    }
    for(int digit = 0; digit < num.length; ++digit){
      os << num.number[num.length - digit - 1];
    }
    return os;
  }
  friend std::istream& operator>>(std::istream &is, BigInteger& num) {
    std::string str;
    is >> str;
    num.number.clear();
    if(str[0] == '-'){
      num.positive = false;
      num.length = (int)str.size() - 1;
      for(int digit = 0; digit < num.length; digit++){
        num.number.push_back(str[num.length - digit] - '0');
      }
    }
    else{
      num.positive = true;
      num.length = (int)str.size();
      for(int digit = 0; digit < num.length; digit++){
        num.number.push_back(str[num.length - digit - 1] - '0');
      }
    }
    return is;
  }

  friend bool operator== (const BigInteger& left, const BigInteger& right);
  friend bool operator!= (const BigInteger& left, const BigInteger& right);
  friend bool operator< (const BigInteger& left, const BigInteger& right);
  friend bool operator> (const BigInteger& left, const BigInteger& right);
  friend bool operator<= (const BigInteger& left, const BigInteger& right);
  friend bool operator>= (const BigInteger& left, const BigInteger& right);

  operator bool();

  friend BigInteger operator+ (const BigInteger& l, const BigInteger& r);
  friend BigInteger operator- (const BigInteger& l, const BigInteger& r);
  friend BigInteger operator* (const BigInteger& left, const BigInteger& right);
  friend BigInteger operator/ (const BigInteger& dividend, const BigInteger& divisor);
  friend BigInteger operator% (const BigInteger& left, const BigInteger& right);

  BigInteger& operator+= (const BigInteger& num);
  BigInteger& operator-= (const BigInteger& num);
  BigInteger& operator*= (const BigInteger& num);
  BigInteger& operator/= (const BigInteger& num);
  BigInteger& operator%= (const BigInteger& num);

  static void extend(std::vector<int>&a, int length);
  static std::vector<int> NaiveMultiplication(std::vector<int>& left, std::vector<int>& right);
  static std::vector<int> KaratsubaMultiplication(std::vector<int>& x, std::vector<int>& y);

};

#endif BIGINTEGER_BIGINTEGER_H