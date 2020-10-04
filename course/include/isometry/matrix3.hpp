/*
 * Vector library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 * Author: Steven Desvars, 2020
 */

#pragma once

#include <isometry/vector3.hpp>
#include <sstream>

namespace ekumen {

namespace math {

class Matrix3 {
 public:
  /// Constructs a Matrix3.
  /// @param row_1_ Values of the first row of the Matrix.
  /// @param row_2_ Values of the first row of the Matrix.
  /// @param row_3_ Values of the first row of the Matrix.
  Matrix3(const std::initializer_list<double>& list);
  Matrix3() : row_1_{0, 0, 0}, row_2_{0, 0, 0}, row_3_{0, 0, 0} {};

  Vector3 operator[](const int i) const;
  Vector3& operator[](const int i);

  static Matrix3 kIdentity;
  static Matrix3 kOnes;
  static Matrix3 kZero;

  bool operator==(const Matrix3& r_matrix) const;
  bool operator!=(const Matrix3& r_matrix) const;

  /// Outputs a specific row of the Matrix.
  /// @param value The number of the row you want to reach.
  Vector3 row(const int& value) const;

  /// Outputs a specific column of the Matrix.
  /// @param value The number of the column you want to reach.
  Vector3 col(const int& value) const;

  /// Outputs the determinant of the Matrix.
  double det() const;

  Matrix3& operator+=(const Matrix3& r_matrix);
  Matrix3 operator+(const Matrix3& r_matrix) const;
  Matrix3& operator-=(const Matrix3& r_matrix);
  Matrix3 operator-(const Matrix3& r_matrix) const;
  Matrix3& operator*=(const Matrix3& r_matrix);
  Matrix3 operator*(const Matrix3& r_matrix) const;
  Vector3 operator*(const Vector3& r_vector) const;
  Matrix3& operator*=(const double& value);
  Matrix3 operator*(const double& value) const;
  Matrix3& operator/=(const Matrix3& r_matrix);
  Matrix3 operator/(const Matrix3& r_matrix) const;
  Matrix3& operator/=(const double& value);

  /// Auxiliar method that receives a vector an outputs a formated string.
  std::string row_print(const Vector3& r_vector) const;

 private:
  Vector3 row_1_;
  Vector3 row_2_;
  Vector3 row_3_;
};

Matrix3 operator*(const double value, const Matrix3& r_matrix);

std::ostream& operator<<(std::ostream& os, const Matrix3& r_matrix);

}  // namespace math

}  // namespace ekumen
