#pragma once

#include <iostream>

class LongNumber {
  public:
  // Postaviti number_ na vrijednost 0
  LongNumber();
  LongNumber(const LongNumber&);
  LongNumber(LongNumber&&);
  LongNumber(const long long&);
  LongNumber(long long&&);
  LongNumber& operator=(const LongNumber&);
  LongNumber& operator=(LongNumber&&);
  LongNumber operator+(const LongNumber&) const;
  LongNumber operator-(const LongNumber&) const;
  LongNumber operator*(const LongNumber&) const;
  LongNumber operator/(const LongNumber&) const;
  LongNumber& operator+=(const LongNumber&);
  LongNumber& operator-=(const LongNumber&);
  LongNumber& operator*=(const LongNumber&);
  LongNumber& operator/=(const LongNumber&);
  LongNumber& operator=(const long long&);
  LongNumber& operator=(long long&&);
  LongNumber operator+(const long long&) const;
  LongNumber operator-(const long long&) const;
  LongNumber operator*(const long long&) const;
  LongNumber operator/(const long long&) const;
  LongNumber& operator+=(const long long&);
  LongNumber& operator-=(const long long&);
  LongNumber& operator*=(const long long&);
  LongNumber& operator/=(const long long&);
  bool operator==(const LongNumber&) const;
  bool operator!=(const LongNumber&) const;
  bool operator>(const LongNumber&) const;
  bool operator<(const LongNumber&) const;
  bool operator>=(const LongNumber&) const;
  bool operator<=(const LongNumber&) const;
  bool operator==(const long long&) const;
  bool operator!=(const long long&) const;
  bool operator>(const long long&) const;
  bool operator<(const long long&) const;
  bool operator>=(const long long&) const;
  bool operator<=(const long long&) const;
  LongNumber operator^(int) const;
  // Primjer pozivanja operator bool():
  // LongNumber num;
  // if(num) // Poziva se operator bool()
  //  cout << "Valid" << std::endl;;
  operator bool() const;
  LongNumber& operator++();
  LongNumber operator++(int);
  LongNumber& operator--();
  LongNumber operator--(int);

  LongNumber abs() const;
  bool isOdd() const;
  bool isEven() const;
  bool isPositive() const;
  bool isNegative() const;
  const long long& value() const;
  long long& num();
  
  ~LongNumber();

  private:
  long long number_;
};

std::ostream& operator<<(std::ostream&, const LongNumber&);
std::istream& operator>>(std::istream&, LongNumber&);
