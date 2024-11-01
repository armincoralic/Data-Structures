
#pragma once
#include <iostream>

class Point {
  public:
  // Default constructor
  Point();
  // Constructor with initial values for x and y
  Point(double x, double y);
  // Copy constructor
  Point(const Point& point);
  // Move constructor
  Point(Point&& point);
  // Assignment operator
  Point& operator=(const Point& point);
  // Move assignment operator
  Point& operator=(Point&& point);
  // Addition operator
  Point operator+(const Point& point) const;
  // Subtrxaction operator
  Point operator-(const Point& point) const;
  // Multiplication operator (scalar multiplication)
  Point operator*(double scalar) const;
  // Division operator (scalar division)
  Point operator/(double scalar) const;
  // Addition assignment operator
  Point& operator+=(const Point& point);
  // Subtraction assignment operator
  Point& operator-=(const Point& point);
  // Multiplication assignment operator (scalar multiplication)
  Point& operator*=(double scalar);
  // Division assignment operator (scalar division)
  Point& operator/=(double scalar);
  // Equality operator
  bool operator==(const Point& point) const;
  // Inequality operator
  bool operator!=(const Point& point) const;
  // Get x-coordinate
  double x() const;
  // Get y-coordinate
  double y() const;
  // Set x-coordinate
  void setX(double x);
  // Set y-coordinate
  void setY(double y);
  // Get the distance between this point and anpoint point
  // sqrt((point.x_ - x_)^2 + (point.y_ - y_)^2)
  double distance(const Point& point) const;

  private:
  double x_;
  double y_;
};

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Point& point);
std::istream& operator>>(std::istream& is, Point& point);
