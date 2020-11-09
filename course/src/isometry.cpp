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
  Vector3 aux;
  aux = matrix * first_vector + second_vector;
  return aux;
}

}  // namespace


Isometry Isometry::fromTranslation(const Vector3& r_vector) {
  Isometry aux;
  aux.translation_vector = r_vector;
  return aux;
}

Vector3 Isometry::translation() const {
  Vector3 aux{translation_vector};
  return aux;
}

Vector3 Isometry::transform(const Vector3& r_vector) const {
  Vector3 aux;
  aux = (*this) * r_vector;
  return aux;
}

Isometry Isometry::inverse() const {
  double deter = rotation_matrix.det();
  if (deter == 0) {
    throw std::invalid_argument("Isometry doesn't have an inverse");
  }
  Matrix3 aux;
  aux = aux.transpose();
  aux[0][0] = rotation_matrix[1][1] * rotation_matrix[2][2] -
      rotation_matrix[1][2] * rotation_matrix[2][1];
  aux[0][1] = rotation_matrix[1][0] * rotation_matrix[2][2] -
      rotation_matrix[1][2] * rotation_matrix[2][0];
  aux[0][2] = rotation_matrix[1][0] * rotation_matrix[2][1] -
      rotation_matrix[1][1] * rotation_matrix[2][0];
  aux[1][0] = rotation_matrix[0][1] * rotation_matrix[2][2] -
      rotation_matrix[0][2] * rotation_matrix[2][1];
  aux[1][1] = rotation_matrix[0][0] * rotation_matrix[2][2] -
      rotation_matrix[0][2] * rotation_matrix[2][0];
  aux[1][2] = rotation_matrix[0][0] * rotation_matrix[1][2] -
      rotation_matrix[0][2] * rotation_matrix[1][0];
  aux[2][0] = rotation_matrix[0][1] * rotation_matrix[1][2] -
      rotation_matrix[0][2] * rotation_matrix[1][1];
  aux[2][1] = rotation_matrix[0][0] * rotation_matrix[1][2] -
      rotation_matrix[0][2] * rotation_matrix[1][0];
  aux[2][2] = rotation_matrix[0][0] * rotation_matrix[1][1] -
      rotation_matrix[0][1] * rotation_matrix[1][0];
  aux = (aux * Matrix3{
    1., -1., 1., -1., 1., -1., 1., -1., 1.});

  Isometry result;
  aux /= deter;
  result.rotation_matrix = aux;
  result.translation_vector = (result.rotation_matrix *
      translation_vector) * -1;
  return result;
}

Matrix3 Isometry::rotation() const {
  Matrix3 aux{rotation_matrix};
  return aux;
}

Isometry Isometry::compose(const Isometry& r_isometry) const {
  Isometry aux = (*this) * r_isometry;
  return aux;
}

Isometry Isometry::rotateAround(const Vector3& r_vector, const double& angle) {
  Isometry aux;
  aux.rotation_matrix[0][0] = std::cos(angle) + pow(r_vector[0], 2)
  * (1 - std::cos(angle));
  aux.rotation_matrix[0][1] = r_vector[0] * r_vector[1] *
  (1 - std::cos(angle)) - r_vector[2] * std::sin(angle);
  aux.rotation_matrix[0][2] = r_vector[0] * r_vector[2] *
  (1 - std::cos(angle)) + r_vector[1] * std::sin(angle);
  aux.rotation_matrix[1][0] = r_vector[1] * r_vector[0] *
  (1 - std::cos(angle)) + r_vector[2] * std::sin(angle);
  aux.rotation_matrix[1][1] = std::cos(angle) + pow(r_vector[1], 2)
  * (1 - std::cos(angle));
  aux.rotation_matrix[1][2] = r_vector[1] * r_vector[2] *
  (1 - std::cos(angle)) - r_vector[0] * std::sin(angle);
  aux.rotation_matrix[2][0] = r_vector[2] * r_vector[0] *
  (1 - std::cos(angle)) - r_vector[1] * std::sin(angle);
  aux.rotation_matrix[2][1] = r_vector[2] * r_vector[1] *
  (1 - std::cos(angle)) + r_vector[0] * std::sin(angle);
  aux.rotation_matrix[2][2] = std::cos(angle) + pow(r_vector[2], 2)
  * (1 - std::cos(angle));
  return aux;
}

Isometry Isometry::fromEulerAngles(const double& roll, const double& pitch,
                                   const double& yaw) {
  Isometry aux = Isometry::rotateAround(Vector3::kUnitX, roll) *
                 Isometry::rotateAround(Vector3::kUnitY, pitch) *
                 Isometry::rotateAround(Vector3::kUnitZ, yaw);
  return aux;
}

bool Isometry::operator==(const Isometry& r_isometry) const {
  return translation_vector == r_isometry.translation_vector &&
  rotation_matrix == r_isometry.rotation_matrix;
}

bool Isometry::operator!=(const Isometry& r_isometry) const {
  return !(*this == r_isometry);
}

Vector3 Isometry::operator*(const Vector3& r_vector) const {
  Vector3 aux = translation_vector_operation(rotation_matrix,
                                             r_vector, translation_vector);
  return aux;
}

Isometry Isometry::operator*(const Isometry& r_isometry) const {
  Isometry aux;
  aux.rotation_matrix = rotation_matrix.product(r_isometry.rotation_matrix);
  aux.translation_vector = translation_vector_operation(
      rotation_matrix, translation_vector, r_isometry.translation_vector);
  return aux;
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
