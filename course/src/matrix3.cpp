/*
 * Matrix library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 * Author: Steven Desvars, 2020
 * Copyright 2020 Ekumen"
 */

#include <isometry/matrix3.hpp>

namespace ekumen {
namespace math {

namespace {

std::string row_print(const Vector3& r_vector) {
  std::stringstream ss(std::ios_base::in | std::ios_base::out);
  ss << std::setprecision(9);
  ss << "[" << r_vector.x() << ", " << r_vector.y() << ", " << r_vector.z()
     << "]";
  std::string aux = ss.str();
  return aux;
}

}  // namespace

Matrix3::Matrix3(const std::initializer_list<double>& values) {
  if (values.size() != 9) {
    throw std::length_error("Incorrect size of list");
  }
  auto it = values.begin();
  for (int i = 0; i < 3; ++i) {
    row_0_[i] = *it;
    ++it;
  }
  for (int i = 0; i < 3; ++i) {
    row_1_[i] = *it;
    ++it;
  }
  for (int i = 0; i < 3; ++i) {
    row_2_[i] = *it;
    if (i != 2) {
      ++it;
    }
  }
}

Vector3 Matrix3::operator[](const int i) const {
  switch (i) {
    case 0:
      return row_0_;
    case 1:
      return row_1_;
    case 2:
      return row_2_;
    default:
      throw std::out_of_range("Operator out of range");
  }
}

Vector3& Matrix3::operator[](const int i) {
  switch (i) {
    case 0:
      return row_0_;
    case 1:
      return row_1_;
    case 2:
      return row_2_;
    default:
      throw std::out_of_range("Operator out of range");
  }
}

Matrix3 Matrix3::kIdentity{Matrix3{1, 0, 0, 0, 1, 0, 0, 0, 1}};
Matrix3 Matrix3::kOnes{Matrix3{1, 1, 1, 1, 1, 1, 1, 1, 1}};
Matrix3 Matrix3::kZero{Matrix3()};

bool Matrix3::operator==(const Matrix3& r_matrix) const {
  return row_0_ == r_matrix.row_0_ && row_1_ == r_matrix.row_1_ &&
         row_2_ == r_matrix.row_2_;
}

bool Matrix3::operator!=(const Matrix3& r_matrix) const {
  return !(*this == r_matrix);
}

double Matrix3::det() const {
  const double A = row_0_[0] * (row_1_[1] * row_2_[2] - row_1_[2] * row_2_[1]);
  const double B = row_0_[1] * (row_1_[0] * row_2_[2] - row_1_[2] * row_2_[0]);
  const double C = row_0_[2] * (row_1_[0] * row_2_[1] - row_1_[1] * row_2_[0]);
  return A - B + C;
}

Matrix3& Matrix3::operator+=(const Matrix3& r_matrix) {
  row_0_ = row_0_ + r_matrix[0];
  row_1_ = row_1_ + r_matrix[1];
  row_2_ = row_2_ + r_matrix[2];
  return *this;
}

Matrix3 Matrix3::operator+(const Matrix3& r_matrix) const {
  Matrix3 aux{*this};
  aux += r_matrix;
  return aux;
}

Matrix3& Matrix3::operator-=(const Matrix3& r_matrix) {
  row_0_ = row_0_ - r_matrix[0];
  row_1_ = row_1_ - r_matrix[1];
  row_2_ = row_2_ - r_matrix[2];
  return *this;
}

Matrix3 Matrix3::operator-(const Matrix3& r_matrix) const {
  Matrix3 aux{*this};
  aux -= r_matrix;
  return aux;
}

Matrix3& Matrix3::operator*=(const double& value) {
  row_0_ = row_0_ * value;
  row_1_ = row_1_ * value;
  row_2_ = row_2_ * value;
  return *this;
}

Matrix3 Matrix3::operator*(const double& value) const {
  Matrix3 aux{*this};
  aux *= value;
  return aux;
}

Matrix3& Matrix3::operator*=(const Matrix3& r_matrix) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      (*this)[i][j] = (*this)[i][j] * r_matrix[i][j];
    }
  }
  return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& r_matrix) const {
  Matrix3 aux{*this};
  aux *= r_matrix;
  return aux;
}

Vector3 Matrix3::operator*(const Vector3& r_vector) const {
  Vector3 aux;
  for (int i = 0; i < 3; ++i) {
    aux[i] = (*this)[i].dot(r_vector);
  }
  return aux;
}

Matrix3& Matrix3::operator/=(const Matrix3& r_matrix) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (r_matrix[i][j] == 0) {
        throw std::invalid_argument("Try to divide by 0");
      }
      (*this)[i][j] = (*this)[i][j] / r_matrix[i][j];
    }
  }
  return *this;
}

Matrix3 Matrix3::operator/(const Matrix3& r_matrix) const {
  Matrix3 aux{*this};
  aux /= r_matrix;
  return aux;
}

Matrix3& Matrix3::operator/=(const double& value) {
  if (value == 0) {
    throw std::invalid_argument("Try to divide by 0");
  }
  row_0_ = row_0_ / value;
  row_1_ = row_1_ / value;
  row_2_ = row_2_ / value;
  return *this;
}

Vector3 Matrix3::row(const int& value) const {
  Vector3 aux{(*this)[value]};
  return aux;
}

Vector3 Matrix3::col(const int& value) const {
  Vector3 aux;
  for (int i = 0; i < 3; ++i) {
    aux[i] = (*this)[i][value];
  }
  return aux;
}

Matrix3 operator*(const double value, const Matrix3& r_matrix) {
  return r_matrix * value;
}

std::ostream& operator<<(std::ostream& os, const Matrix3& r_matrix) {
  os << "[" << row_print(r_matrix.row(0)) << ", " << row_print(r_matrix.row(1))
     << ", " << row_print(r_matrix.row(2)) << "]";
  return os;
}

}  // namespace math
}  // namespace ekumen
