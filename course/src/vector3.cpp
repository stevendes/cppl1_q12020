/*
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 * Author: Steven Desvars, 2020
 * Copyright 2020 Ekumen"
 */

#include <isometry/vector3.hpp>

namespace ekumen {
namespace math {

/// Constructs a Vector3 from a list.
/// @param x Value in the x-direction vector.
/// @param y Value in the y-direction vector.
/// @param z Value in the z-direction vector.
Vector3::Vector3(const std::initializer_list<double>& list) {
  if (list.size() != 3) {
    throw std::out_of_range("Incorrect size of list");
  }
  auto it = list.begin();
  x_ = *it;
  ++it;
  y_ = *it;
  ++it;
  z_ = *it;
}

double Vector3::operator[](const int i) const {
  if ((i < 0) || (i > 2)) {
    throw std::out_of_range("Operator out of range");
  }
  switch (i) {
    case 0:
      return x_;
    case 1:
      return y_;
    case 2:
      return z_;
    default:
      throw std::out_of_range("Operator out of range");
  }
}

double& Vector3::operator[](const int i) {
  if ((i < 0) || (i > 2)) {
    throw std::out_of_range("Operator out of range");
  }
  if (i == 0) {
    return x_;
  } else if (i == 1) {
    return y_;
  } else {
    return z_;
  }
}

Vector3 Vector3::kUnitX{Vector3(1., 0., 0.)};

Vector3 Vector3::kUnitY{Vector3(0, 1, 0)};

Vector3 Vector3::kUnitZ{Vector3(0, 0, 1)};

Vector3 Vector3::kZero{Vector3(0, 0, 0)};

bool Vector3::operator==(const Vector3& r_vector) const {
  return almost_equal(x_, r_vector.x_, 2) && almost_equal(y_, r_vector.y_, 2) &&
         almost_equal(z_, r_vector.z_, 2);
}

bool Vector3::operator!=(const Vector3& r_vector) const {
  return !(*this == r_vector);
}

Vector3& Vector3::operator+=(const Vector3& r_vector) {
  x_ = x_ + r_vector.x_;
  y_ = y_ + r_vector.y_;
  z_ = z_ + r_vector.z_;

  return *this;
}

Vector3 Vector3::operator+(const Vector3& r_vector) const {
  Vector3 aux{*this};
  aux += r_vector;
  return aux;
}

Vector3& Vector3::operator-=(const Vector3& r_vector) {
  x_ = x_ - r_vector.x_;
  y_ = y_ - r_vector.y_;
  z_ = z_ - r_vector.z_;

  return *this;
}

Vector3 Vector3::operator-(const Vector3& r_vector) const {
  Vector3 aux{*this};
  aux -= r_vector;
  return aux;
}

Vector3& Vector3::operator*=(const Vector3& r_vector) {
  x_ = x_ * r_vector.x_;
  y_ = y_ * r_vector.y_;
  z_ = z_ * r_vector.z_;

  return *this;
}

Vector3& Vector3::operator*=(const double& number) {
  x_ = x_ * number;
  y_ = y_ * number;
  z_ = z_ * number;

  return *this;
}

Vector3 Vector3::operator*(const double& number) const {
  Vector3 aux{*this};
  aux *= number;
  return aux;
}

Vector3 Vector3::operator*(const Vector3& r_vector) const {
  Vector3 aux{*this};
  aux *= r_vector;
  return aux;
}

Vector3& Vector3::operator/=(const Vector3& r_vector) {
  x_ = x_ / r_vector.x_;
  y_ = y_ / r_vector.y_;
  z_ = z_ / r_vector.z_;

  return *this;
}

Vector3& Vector3::operator/=(const double& v) {
  x_ = x_ / v;
  y_ = y_ / v;
  z_ = z_ / v;

  return *this;
}

Vector3 Vector3::operator/(const double& number) const {
  Vector3 aux{*this};
  aux *= number;
  return aux;
}

Vector3 Vector3::operator/(const Vector3& r_vector) const {
  Vector3 aux{*this};
  aux /= r_vector;
  return aux;
}
/// Scalar product
/// @param r_vector another Vector3 object
/// @returns This vector dot product r_vector.
double Vector3::dot(const Vector3& r_vector) const {
  return x_ * r_vector.x_ + y_ * r_vector.y_ + z_ * r_vector.z_;
}

/// Cross product
/// @param r_vector another Vector3 object
/// @returns A new Vector3 result of cross product between this and r_vector.
Vector3 Vector3::cross(const Vector3& r_vector) const {
  const double new_x = y_ * r_vector.z_ - z_ * r_vector.y_;
  const double new_y = z_ * r_vector.x_ - x_ * r_vector.z_;
  const double new_z = x_ * r_vector.y_ - y_ * r_vector.x_;

  return {new_x, new_y, new_z};
}

/// Norm
/// @returns A scalar result of the norm of this.
double Vector3::norm() const { return dot(*this); }

Vector3 operator*(const double value, const Vector3& r_vector) {
  return r_vector * value;
}

std::ostream& operator<<(std::ostream& os, const Vector3& r_vector) {
  os << '[' << r_vector.x() << ',' << r_vector.y() << ',' << r_vector.z()
     << ']';
  return os;
}

}  // namespace math
}  // namespace ekumen
