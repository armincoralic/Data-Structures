// Vasa implementacija ovdje
#include<iostream>
#include "LongNumber.hpp"
using namespace std;
LongNumber::LongNumber():number_(0){}
LongNumber::LongNumber(const LongNumber& num) : number_{num.number_} {}
LongNumber::LongNumber(LongNumber&& num){
  number_ = std::move(num.number_);
}

LongNumber::LongNumber(const long long& num){
  number_=num;
}

LongNumber::LongNumber(long long&& num){
number_=std::move(num);
}

LongNumber& LongNumber::operator=(const LongNumber& num){
  if(this!=&num)
  {
    number_=num.number_;
  }
  return *this;
}

LongNumber& LongNumber::operator=(LongNumber&& num)
{
  number_=num.number_;
  num.number_=0;
  return *this;
}



LongNumber LongNumber::operator+(const LongNumber& num) const
{
  return LongNumber(number_+num.number_);
}

LongNumber LongNumber::operator-(const LongNumber& num) const
{
  return LongNumber(number_-num.number_);
}

LongNumber LongNumber::operator*(const LongNumber& num) const
{
  return LongNumber(number_*num.number_);
}

LongNumber LongNumber::operator/(const LongNumber& num) const
{
  return LongNumber(number_*num.number_);
}

LongNumber& LongNumber::operator+=(const LongNumber& num){
  number_+=num.number_;
  return *this;
}

LongNumber& LongNumber::operator-=(const LongNumber& num){
  number_-=num.number_;
  return *this;
}

LongNumber& LongNumber::operator*=(const LongNumber& num){
  number_*=num.number_;
  return *this;
}

LongNumber& LongNumber::operator/=(const LongNumber& num){
  number_/=num.number_;
  return *this;
}

LongNumber& LongNumber::operator=(const long long& num) {
  number_=num;
  return *this;
}

LongNumber& LongNumber::operator=(long long&& num)
{
  number_=move(num);
  return *this;
}
LongNumber LongNumber::operator+(const long long& num) const
{
  return LongNumber(number_+num);
}

LongNumber LongNumber::operator-(const long long& num) const
{
  return LongNumber(number_-num);
}
LongNumber LongNumber::operator*(const long long& num) const
{
  return LongNumber(number_*num);
}
LongNumber LongNumber::operator/(const long long& num) const
{
  return LongNumber(number_/num);
}

LongNumber& LongNumber::operator+=(const long long& num){
  number_+=num;
  return *this;
}

LongNumber& LongNumber::operator-=(const long long& num){
  number_-=num;
  return *this;
}

LongNumber& LongNumber::operator/=(const long long& num){
  number_/=num;
  return *this;
}


LongNumber& LongNumber::operator*=(const long long& num){
  number_*=num;
  return *this;
}

bool LongNumber::operator==(const LongNumber& num) const
{
  // if(number_==num.number_)
  // {
  //   return true;
  // }
  // return false;

  return number_ == num.number_;
}

bool LongNumber::operator!=(const LongNumber& num) const
{
  // if(number_!=num.number_)
  // {
  //   return true;
  // }
  // return false;
  return number_ != num.number_;
}

bool LongNumber::operator>(const LongNumber& num) const
{
  // if(number_<num.number_)
  // {
  //   return true;
  // }
  // return false;
  return number_ > num.number_;
}

bool LongNumber::operator<(const LongNumber& num) const
{
  // if(number_>num.number_)
  // {
  //   return true;
  // }
  // return false;
  return number_ < num.number_;
}

bool LongNumber::operator>=(const LongNumber& num) const
{
  // if(number_<=num.number_)
  // {
  //   return true;
  // }
  // return false;
  return number_ >= num.number_;
}

bool LongNumber::operator<=(const LongNumber& num) const
{
  // if(number_>=num.number_)
  // {
  //   return true;
  // }
  // return false;
  return number_ <= num.number_;
}

bool LongNumber::operator==(const long long& num) const
{
  if(number_==num)
  {
    return true;
  }
  return false;
}

bool LongNumber::operator!=(const long long& num) const
{
  if(number_!=num)
  {
    return true;
  }
  return false;
}

bool LongNumber::operator>(const long long& num) const
{
  if(number_<num)
  {
    return true;
  }
  return false;
}

bool LongNumber::operator<(const long long& num) const
{
  if(number_<num)
  {
    return true;
  }
  return false;
}

bool LongNumber::operator>=(const long long& num) const
{
  if(number_<=num)
  {
    return true;
  }
  return false;
}

bool LongNumber::operator<=(const long long& num) const
{
  if(number_>=num)
  {
    return true;
  }
  return false;
}


LongNumber LongNumber::operator^(int num) const {
  if(num == 0 && number_ == 0) throw std::invalid_argument{"0^0 is undefined!"};
  if(num == 0) return 1;

  long long res = number_;
  for(int i = 1; i < num; ++i)
    res *= number_;

  return res;
}

LongNumber::operator bool() const
{
  return number_!=0;
}

LongNumber& LongNumber::operator++(){
  number_=number_+1;
  return *this;
}

LongNumber LongNumber::operator++(int)
{
  LongNumber temp(*this);
  ++number_;
  return temp;
}
LongNumber& LongNumber::operator--(){
  number_=number_-1;
  return *this;
}
LongNumber LongNumber::operator--(int){
  LongNumber temp(*this);
  --number_;
  return temp;
}

LongNumber LongNumber::abs() const{
  return std::abs(number_);
}

bool LongNumber::isOdd() const {
  return (number_%2)!=0;
}

bool LongNumber::isEven() const{
  return (number_%2)==0;
}

bool LongNumber::isPositive() const{
  return number_>0;
}

bool LongNumber::isNegative() const{
  return number_<0;
}

const long long& LongNumber::value() const{
return number_;
}

long long& LongNumber::num(){
return number_;
}

std::ostream& operator<<(std::ostream& o, const LongNumber& num){
  return o<<num;
};

std::istream& operator>>(std::istream& i, LongNumber& num){
  long long value;
  i>>value;
  num=LongNumber(value);
  return i;
};

LongNumber::~LongNumber(){number_=0;};
