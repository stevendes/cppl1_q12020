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

Matrix3::Matrix3(const std::initializer_list<double>& list) {
  if (list.size() != 9) {
    throw std::out_of_range("Incorrect size of list");
  }
  auto it = list.begin();
  for (int i = 0; i < 3; ++i) {
    row_1_[i] = *it;
    ++it;
  }
  for (int i = 0; i < 3; ++i) {
    row_2_[i] = *it;
    ++it;
  }
  for (int i = 0; i < 3; ++i) {
    row_3_[i] = *it;
    if (i != 2) {
      ++it;
    }
  }
}

Vector3 Matrix3::operator[](const int i) const {
  switch (i) {
    case 0:
      return row_1_;
    case 1:
      return row_2_;
    case 2:
      return row_3_;
    default:
      throw std::out_of_range("Operator out of range");
  }
}

Vector3& Matrix3::operator[](const int i) {
  switch (i) {
    case 0:
      return row_1_;
    case 1:
      return row_2_;
    case 2:
      return row_3_;
    default:
      throw std::out_of_range("Operator out of range");
  }
}

Matrix3 Matrix3::kIdentity{Matrix3{1, 0, 0, 0, 1, 0, 0, 0, 1}};
Matrix3 Matrix3::kOnes{Matrix3{1, 1, 1, 1, 1, 1, 1, 1, 1}};
Matrix3 Matrix3::kZero{Matrix3()};

bool Matrix3::operator==(const Matrix3& r_matrix) const {
  return row_1_ == r_matrix.row_1_ && row_2_ == r_matrix.row_2_ &&
         row_3_ == r_matrix.row_3_;
}

bool Matrix3::operator!=(const Matrix3& r_matrix) const {
  return !(*this == r_matrix);
}

double Matrix3::det() const {
  double first_value, second_value, third_value;
  first_value = (*this)[0][0] *
                ((*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1]);
  second_value = (*this)[0][1] * ((*this)[1][0] * (*this)[2][2] -
                                  (*this)[1][2] * (*this)[2][0]);
  third_value = (*this)[0][2] *
                ((*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0]);
  return first_value - second_value + third_value;
}

Matrix3& Matrix3::operator+=(const Matrix3& r_matrix) {
  row_1_ = row_1_ + r_matrix[0];
  row_2_ = row_2_ + r_matrix[1];
  row_3_ = row_3_ + r_matrix[2];
  return *this;
}

Matrix3 Matrix3::operator+(const Matrix3& r_matrix) const {
  Matrix3 aux{*this};
  aux += r_matrix;
  return aux;
}

Matrix3& Matrix3::operator-=(const Matrix3& r_matrix) {
  row_1_ = row_1_ - r_matrix[0];
  row_2_ = row_2_ - r_matrix[1];
  row_3_ = row_3_ - r_matrix[2];
  return *this;
}

Matrix3 Matrix3::operator-(const Matrix3& r_matrix) const {
  Matrix3 aux{*this};
  aux -= r_matrix;
  return aux;
}

Matrix3& Matrix3::operator*=(const double& value) {
  row_1_ = row_1_ * value;
  row_2_ = row_2_ * value;
  row_3_ = row_3_ * value;
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
  row_1_ = row_1_ / value;
  row_2_ = row_2_ / value;
  row_3_ = row_3_ / value;
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

std::string Matrix3::row_print(const Vector3& r_vector) const {
  std::string aux;
  aux = "[" + std::to_string(static_cast<int>(r_vector.x())) + ", " +
        std::to_string(static_cast<int>(r_vector.y())) + ", " +
        std::to_string(static_cast<int>(r_vector.z())) + "]";
  return aux;
}

std::ostream& operator<<(std::ostream& os, const Matrix3& r_matrix) {
  os << "[" << r_matrix.row_print(r_matrix.row(0)) << ", "
     << r_matrix.row_print(r_matrix.row(1)) << ", "
     << r_matrix.row_print(r_matrix.row(2)) << "]";
  return os;
}

}  // namespace math
}  // namespace ekumen
