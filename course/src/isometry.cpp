/*
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 * Copyright 2020 Ekumen"
 */

#include <isometry/isometry.hpp>

namespace ekumen {
namespace math {

namespace {

Vector3 translation_vector_operation(const Matrix3& matrix,
                                     const Vector3& first_vector,
                                     const Vector3& second_vector) {
  return matrix * first_vector + second_vector;
}

}  // namespace


Isometry Isometry::fromTranslation(const Vector3& r_vector) {
  return Isometry{r_vector, Matrix3::kIdentity};
}

Vector3 Isometry::translation() const {
  return translation_vector_;
}

Vector3 Isometry::transform(const Vector3& r_vector) const {
  return (*this) * r_vector;
}

Isometry Isometry::inverse() const {
  const double det = rotation_matrix_.det();
  if (det == 0) {
    throw std::invalid_argument("Isometry doesn't have an inverse");
  }
  const Matrix3 transpose_matrix{rotation_matrix_.transpose()};
  const double c_00 = transpose_matrix[1][1] * transpose_matrix[2][2] -
      transpose_matrix[1][2] * transpose_matrix[2][1];
  const double c_01 = transpose_matrix[1][0] * transpose_matrix[2][2] -
      transpose_matrix[1][2] * transpose_matrix[2][0];
  const double c_02 = transpose_matrix[1][0] * transpose_matrix[2][1] -
      transpose_matrix[1][1] * transpose_matrix[2][0];
  const double c_10 = transpose_matrix[0][1] * transpose_matrix[2][2] -
      transpose_matrix[0][2] * transpose_matrix[2][1];
  const double c_11 = transpose_matrix[0][0] * transpose_matrix[2][2] -
      transpose_matrix[0][2] * transpose_matrix[2][0];
  const double c_12 = transpose_matrix[0][0] * transpose_matrix[1][2] -
      transpose_matrix[0][2] * transpose_matrix[1][0];
  const double c_20 = transpose_matrix[0][1] * transpose_matrix[1][2] -
      transpose_matrix[0][2] * transpose_matrix[1][1];
  const double c_21 = transpose_matrix[0][0] * transpose_matrix[1][2] -
      transpose_matrix[0][2] * transpose_matrix[1][0];
  const double c_22 = transpose_matrix[0][0] * transpose_matrix[1][1] -
      transpose_matrix[0][1] * transpose_matrix[1][0];

  Matrix3 aux{c_00, -c_01, c_02, -c_10, c_11, -c_12, c_20, -c_21, c_22};
  aux /= det;
  return Isometry{aux * translation_vector_ * -1, aux};
}

Matrix3 Isometry::rotation() const {
  return rotation_matrix_;
}

Isometry Isometry::compose(const Isometry& r_isometry) const {
  return *this * r_isometry;
}

Isometry Isometry::rotateAround(const Vector3& r_vector, const double& angle) {
  Isometry aux;
  aux.rotation_matrix_[0][0] = std::cos(angle) + pow(r_vector[0], 2)
  * (1 - std::cos(angle));
  aux.rotation_matrix_[0][1] = r_vector[0] * r_vector[1] *
  (1 - std::cos(angle)) - r_vector[2] * std::sin(angle);
  aux.rotation_matrix_[0][2] = r_vector[0] * r_vector[2] *
  (1 - std::cos(angle)) + r_vector[1] * std::sin(angle);
  aux.rotation_matrix_[1][0] = r_vector[1] * r_vector[0] *
  (1 - std::cos(angle)) + r_vector[2] * std::sin(angle);
  aux.rotation_matrix_[1][1] = std::cos(angle) + pow(r_vector[1], 2)
  * (1 - std::cos(angle));
  aux.rotation_matrix_[1][2] = r_vector[1] * r_vector[2] *
  (1 - std::cos(angle)) - r_vector[0] * std::sin(angle);
  aux.rotation_matrix_[2][0] = r_vector[2] * r_vector[0] *
  (1 - std::cos(angle)) - r_vector[1] * std::sin(angle);
  aux.rotation_matrix_[2][1] = r_vector[2] * r_vector[1] *
  (1 - std::cos(angle)) + r_vector[0] * std::sin(angle);
  aux.rotation_matrix_[2][2] = std::cos(angle) + pow(r_vector[2], 2)
  * (1 - std::cos(angle));
  return aux;
}

Isometry Isometry::fromEulerAngles(const double& roll, const double& pitch,
                                   const double& yaw) {
  return Isometry::rotateAround(Vector3::kUnitX, roll) *
                 Isometry::rotateAround(Vector3::kUnitY, pitch) *
                 Isometry::rotateAround(Vector3::kUnitZ, yaw);
}

bool Isometry::operator==(const Isometry& r_isometry) const {
  return translation_vector_ == r_isometry.translation_vector_ &&
  rotation_matrix_ == r_isometry.rotation_matrix_;
}

bool Isometry::operator!=(const Isometry& r_isometry) const {
  return !(*this == r_isometry);
}

Vector3 Isometry::operator*(const Vector3& r_vector) const {
  return translation_vector_operation(rotation_matrix_,
                                             r_vector, translation_vector_);
}

Isometry Isometry::operator*(const Isometry& r_isometry) const {
  return Isometry{translation_vector_operation(
    rotation_matrix_, translation_vector_, r_isometry.translation_vector_),
    rotation_matrix_.product(r_isometry.rotation_matrix_)};
}

Isometry& Isometry::operator*=(const Isometry& r_isometry) {
  *this = (*this) * r_isometry;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Isometry& r_isometry) {
  os << "[T: " << r_isometry.translation() << ", "
     << "R:" << r_isometry.rotation() << "]";
  return os;
}

}  // namespace math
}  // namespace ekumen
