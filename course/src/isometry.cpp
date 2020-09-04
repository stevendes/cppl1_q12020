/*
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 * Copyright 2020 Ekumen"
 */

#include <isometry/isometry.hpp>

namespace ekumen {
namespace math {

Vector3::Vector3(double x, double y, double z) {
  this->x_ = x;
  this->y_ = y;
  this->z_ = z;
}

Vector3::Vector3(std::initializer_list<double> list) {
  if (list.size() != 3) {
    throw std::out_of_range("Incorret size of list");
  }
  auto it = list.begin();
  this->x_ = *it;
  it++;
  this->y_ = *it;
  it++;
  this->z_ = *it;
}

Vector3::Vector3() {
  this->x_ = 0;
  this->y_ = 0;
  this->z_ = 0;
}

double Vector3::operator[](const int i) const {
  if ((i < 0) || (i > 2)) {
    throw std::out_of_range("Operator out of range");
  }
  if (i == 0) {
    return this->x_;
  } else if (i == 1) {
    return this->y_;
  } else {
    return this->z_;
  }
}

double& Vector3::operator[](const int i) {
  if ((i < 0) || (i > 2)) {
    throw std::out_of_range("Operator out of range");
  }
  if (i == 0) {
    return this->x_;
  } else if (i == 1) {
    return this->y_;
  } else {
    return this->z_;
  }
}

Vector3 Vector3::kUnitX{Vector3(1., 0., 0.)};

Vector3 Vector3::kUnitY{Vector3(0, 1, 0)};

Vector3 Vector3::kUnitZ{Vector3(0, 0, 1)};

Vector3 Vector3::kZero{Vector3(0, 0, 0)};


bool Vector3::operator==(const Vector3& r_vector) const {
  bool result = true;
  if (!((this->x_ == r_vector.x_) && (this->y_ == r_vector.y_) && (
    this->z_ == r_vector.z_))) {
    result = false;
  }

  return result;
}

bool Vector3::operator!=(const Vector3& r_vector) const {
  bool result = false;
  if ((this->x_ != r_vector.x_) || (this->y_ != r_vector.y_) || (
    this->z_ == r_vector.z_)) {
    result = true;
  }

  return result;
}

Vector3& Vector3::operator+=(const Vector3& r_vector) {
  this->x_ = this->x_ + r_vector.x_;
  this->y_ = this->y_ + r_vector.y_;
  this->z_ = this->z_ + r_vector.z_;

  return *this;
}

Vector3 Vector3::operator+(const Vector3& r_vector) const {
  double new_x, new_y, new_z;
  new_x = this->x_ + r_vector.x_;
  new_y = this->y_ + r_vector.y_;
  new_z = this->z_ + r_vector.z_;

  return Vector3(new_x, new_y, new_z);
}

Vector3 Vector3::operator-(const Vector3& r_vector) const {
  double new_x, new_y, new_z;
  new_x = this->x_ - r_vector.x_;
  new_y = this->y_ - r_vector.y_;
  new_z = this->z_ - r_vector.z_;

  return Vector3(new_x, new_y, new_z);
}

Vector3& Vector3::operator-=(const Vector3& r_vector) {
  this->x_ = this->x_ - r_vector.x_;
  this->y_ = this->y_ - r_vector.y_;
  this->z_ = this->z_ - r_vector.z_;

  return *this;
}

Vector3 Vector3::operator*(const double& int_value) const {
  double new_x, new_y, new_z;
  new_x = this->x_ * int_value;
  new_y = this->y_ * int_value;
  new_z = this->z_ * int_value;

  return Vector3(new_x, new_y, new_z);
}

Vector3& Vector3::operator*=(const double& int_value) {
  this->x_ = this->x_ * int_value;
  this->y_ = this->y_ * int_value;
  this->z_ = this->z_ * int_value;

  return *this;
}

Vector3 Vector3::operator*(const Vector3& r_vector) const {
  double new_x, new_y, new_z;
  new_x = this->x_ * r_vector.x_;
  new_y = this->y_ * r_vector.y_;
  new_z = this->z_ * r_vector.z_;

  return Vector3(new_x, new_y, new_z);
}

Vector3& Vector3::operator*=(const Vector3& r_vector) {
  this->x_ = this->x_ * r_vector.x_;
  this->y_ = this->y_ * r_vector.y_;
  this->z_ = this->z_ * r_vector.z_;

  return *this;
}

Vector3 Vector3::operator/ (const double& int_value) const {
  double new_x, new_y, new_z;
  new_x = this->x_ / int_value;
  new_y = this->y_ / int_value;
  new_z = this->z_ / int_value;

  return Vector3(new_x, new_y, new_z);
}

Vector3& Vector3::operator/=(const double& v) {
  this->x_ = this->x_ / v;
  this->y_ = this->y_ / v;
  this->z_ = this->z_ / v;

  return *this;
}

Vector3 Vector3::operator/(const Vector3& r_vector) const {
  double new_x, new_y, new_z;
  new_x = this->x_ / r_vector.x_;
  new_y = this->y_ / r_vector.y_;
  new_z = this->z_ / r_vector.z_;

  return Vector3(new_x, new_y, new_z);
}

Vector3& Vector3::operator/=(const Vector3& r_vector) {
  this->x_ = this->x_ / r_vector.x_;
  this->y_ = this->y_ / r_vector.y_;
  this->z_ = this->z_ / r_vector.z_;

  return *this;
}

double Vector3::dot(const Vector3& r_vector) const {
  double result;
  result = this->x_ * r_vector.x_ + this->y_ * r_vector.y_ +
  this->z_ * r_vector.z_;
  return result;
}

Vector3 Vector3::cross(const Vector3& r_vector) const {
  double new_x, new_y, new_z;
  new_x = this->y_ * r_vector.z_ - this->z_ * r_vector.y_;
  new_y = this->z_ * r_vector.x_ - this->x_ * r_vector.z_;
  new_z = this->x_ * r_vector.y_ - this->y_ * r_vector.x_;

  return Vector3(new_x, new_y, new_z);
}

double Vector3::norm() const {
  double aux_x, aux_y, aux_z, result;
  aux_x = pow(this->x_ , 2);
  aux_y = pow(this->y_ , 2);
  aux_z = pow(this->z_ , 2);
  result = sqrt(aux_x + aux_y + aux_z);
  return result;
}

Vector3 operator*(const int i, const Vector3& r_vector) {
  double new_x, new_y, new_z;
  new_x = i * r_vector.x();
  new_y = i * r_vector.y();
  new_z = i * r_vector.z();
  return Vector3(new_x, new_y, new_z);
}

std::ostream& operator<<(std::ostream& os, const Vector3& r_vector) {
    os << '[' << r_vector.x() << ',' << r_vector.y() <<
    ',' << r_vector.z() << ']';
    return os;
}


}  // namespace math
}  // namespace ekumen
