// Vas kod ovdje
#include<iostream>
#include<cmath>
#include "Point.hpp"

// Default constructor
Point::Point():x_{0}, y_{0}{};
// Constructor with initial values for x and y
Point::Point(double x, double y):x_{x}, y_{y}{};
// Copy constructor
Point::Point(const Point& point){
  x_=point.x_;
  y_=point.y_;
};
// Move constructor
Point::Point(Point&& point){
  x_=std::move(point.x_);
  y_=std::move(point.y_);
  point.x_=0;
  point.y_=0;
};
// Assignment operator
Point& Point::operator=(const Point& point){
  if(this!=&point){
    x_=point.x_;
    y_=point.y_;
  }
  return *this;
};
// Move assignment operator
Point& Point::operator=(Point&& point){
  if(this!=&point){
    y_=std::move(point.y_);
    x_=std::move(point.x_);
  }
  point.x_=0;
  point.y_=0;
  return *this;
};
  // Addition operator
Point Point::operator+(const Point& point) const{
  Point rez;
  rez.x_=x_+point.x_;
  rez.y_=y_+point.y_;
  return rez;
};
    // Subtrxaction operator
Point Point::operator-(const Point& point) const{
  Point rez;
  rez.x_=x_-point.x_;
  rez.y_=y_-point.y_;
  return rez;

};
// Multiplication operator (scalar multiplication)
Point Point::operator*(double scalar) const{
  Point rez;
  rez.x_=x_*scalar;
  rez.y_=y_*scalar;
  return rez;

};
// Division operator (scalar division)
Point Point::operator/(double scalar) const{
  if(scalar==0){
    throw std::invalid_argument("zabrana dijeljenja s nulom");
  }
  Point rez;
  rez.x_=x_/scalar;
  rez.y_=y_/scalar;
  return rez;

};
  // Addition assignment operator
Point& Point::operator+=(const Point& point){
  x_+=point.x_;
  y_+=point.y_;
  return *this;
};
  // Subtraction assignment operator
Point& Point::operator-=(const Point& point){
  x_-=point.x_;
  y_-=point.y_;
  return *this;
  };
  // Multiplication assignment operator (scalar multiplication)
Point& Point::operator*=(double scalar){
  x_*=scalar;
  y_*=scalar;
  return *this;
};
  // Division assignment operator (scalar division)
Point& Point::operator/=(double scalar){
  if(scalar==0){
    throw std::invalid_argument("nevalidan unos skalara");
  }
  x_/=scalar;
  y_/=scalar;
  return *this;
};
  // Equality operator
bool Point::operator==(const Point& point) const{
  if(x_==point.x_ && y_==point.y_){return true;}
  return false;
};
  // Inequality operator
bool Point::operator!=(const Point& point) const{
  return (x_ != point.x_ || y_ != point.y_);
};
  // Get x-coordinate
  double Point::x() const{
    return x_;
  };
  // Get y-coordinate
  double Point::y() const{
    return y_;
  };
  // Set x-coordinate
  void Point::setX(double x){
    x_=x;
  }; 
  // Set y-coordinate
  void Point::setY(double y){
    y_=y;
  };
  // Get the distance between this point and anpoint point
  // sqrt((point.x_ - x_)^2 + (point.y_ - y_)^2)
  double Point::distance(const Point& point) const{
    int dx=point.x_-x_;
    int dy=point.y_-y_;
    return sqrt(dx*dx + dy*dy);
  };
std::ostream& operator<<(std::ostream& os, const Point& point){
  os<<point.x()<<", "<<point.y();
  return os;
};
std::istream& operator>>(std::istream& is, Point& point){
  double x, y;
  is>>x>>y;
  point.setX(x);
  point.setY(y);
  return is;
};
