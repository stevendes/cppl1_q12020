/*
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace ekumen {

namespace math {

template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp) {
  return std::fabs(x - y) <=
             std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp ||
         std::fabs(x - y) < std::numeric_limits<T>::min();
}

class Vector3 {
 public:
  Vector3(const double x,const double y,const double z) : x_{x}, y_{y}, z_{z} {};
  Vector3(const std::initializer_list<double>& list);
  Vector3() : x_{0}, y_{0}, z_{0} {};

  double operator[](const int i) const;
  double& operator[](const int i);

  double x() const { return x_; }
  double& x() { return x_; }
  double y() const { return y_; }
  double& y() { return y_; }
  double z() const { return z_; }
  double& z() { return z_; }

  double dot(const Vector3& r_vector) const;
  double norm() const;
  Vector3 cross(const Vector3& r_vector) const;

  bool operator==(const Vector3& r_vector) const;
  bool operator!=(const Vector3& r_vector) const;
  Vector3& operator-=(const Vector3& r_vector);
  Vector3 operator-(const Vector3& r_vector) const;
  Vector3& operator+=(const Vector3& r_vector);
  Vector3 operator+(const Vector3& r_vector) const;
  Vector3& operator*=(const double& number);
  Vector3 operator*(const double& number) const;
  Vector3& operator*(const Vector3& r_vector);
  Vector3 operator*(const Vector3& r_vector) const;
  Vector3& operator*=(const Vector3& r_vector);
  Vector3 operator/(const double& number) const;
  Vector3& operator/=(const double& v);
  Vector3 operator/(const Vector3& r_vector) const;
  Vector3& operator/=(const Vector3& r_vector);

  static Vector3 kUnitX;
  static Vector3 kUnitY;
  static Vector3 kUnitZ;
  static Vector3 kZero;

 private:
  double x_;
  double y_;
  double z_;
};

Vector3 operator*(const double value, const Vector3& r_vector);

std::ostream& operator<<(std::ostream& os, const Vector3& r_vector);

}  // namespace math

}  // namespace ekumen
