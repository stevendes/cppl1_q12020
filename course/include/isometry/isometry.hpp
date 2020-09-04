/*
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 */

#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace ekumen {

namespace math {

class Vector3 {
 public:
  Vector3(const double x, const double y, const double z);
  Vector3(std::initializer_list<double> list);
  Vector3();
  ~Vector3() { };

  double operator[](const int i) const;
  double& operator[](const int i);

  double x() const { return this->x_; }
  double& x() { return this->x_; }  
  double y() const {return this->y_; }
  double& y() {return this->y_; }  
  double z() const {return this->z_; }
  double& z() {return this->z_; }  
 
  double dot(const Vector3& r_vector) const;
  double norm() const;
  Vector3 cross(const Vector3& r_vector) const;

  bool operator==(const Vector3& r_vector) const;
  bool operator!=(const Vector3& r_vector) const;
  Vector3& operator-=(const Vector3& r_vector);
  Vector3 operator-(const Vector3& r_vector) const;
  Vector3& operator+=(const Vector3& r_vector);
  Vector3 operator+(const Vector3& r_vector) const;
  Vector3& operator*=(const double& int_value);
  Vector3 operator*(const double& int_value) const;
  Vector3& operator*(const Vector3& r_vector);
  Vector3 operator*(const Vector3& r_vector) const;
  Vector3& operator*=(const Vector3& r_vector);
  Vector3 operator/(const double& int_value) const;
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

Vector3 operator*(const int i, const Vector3& r_vector);

std::ostream& operator<<(std::ostream& os, const Vector3& r_vector);

}  // namespace math

}  // namespace ekumen
