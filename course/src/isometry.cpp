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

Matrix3 matrix_multiplication(const Matrix3& matrix1, const Matrix3& matrix2) {
  Matrix3 aux;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int iter = 0; iter < 3; ++iter) {
        aux[i][j] += matrix1[iter][i] * matrix2[j][iter];
      }
    }
  }
  return aux;
}

Vector3 translation_vector_operation(const Matrix3& matrix,
                                     const Vector3& first_vector,
                                     const Vector3& second_vector) {
  Vector3 aux;
  aux = matrix * first_vector + second_vector;
  return aux;
}

float determinant2(std::vector<std::vector<float>> minor) {
  float det = minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];
  return det;
}

Matrix3 matrix_minor(const Matrix3& r_matrix) {
  Matrix3 aux;
  std::vector<std::vector<float>> minor;
  int minor_row, minor_col;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      for (int i = 0; i < 3; i++) {
        minor_row = i;
        if (i > row) {
          --minor_row;
        }
        for (int j = 0; j < 3; j++) {
          minor_col = j;
          if (j > col) {
            --minor_col;
          }
          if (i != row && j != col) {
            minor[minor_row][minor_col] = r_matrix[i][j];
          }
        }
      }
      aux[row][col] = determinant2(minor);
    }
  }
  return aux;
}

}  // namespace


Isometry Isometry::fromTranslation(const Vector3& r_vector) {
  Isometry aux;
  aux.rotation_matrix = Matrix3::kIdentity;
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
  Isometry aux{*this};
  double determinant;
  determinant = aux.rotation_matrix.det();
  if (determinant == 0) {
    throw std::out_of_range("Isometry doesn't have an inverse");
  }
  aux.rotation_matrix = matrix_minor(aux.rotation_matrix) *
                        (Matrix3{1., -1., 1., -1., 1., -1., 1., -1., 1});
  aux.translation_vector = aux.rotation_matrix * aux.translation_vector;
  return *this;
}

Matrix3 Isometry::rotation() const {
  Matrix3 aux{rotation_matrix};
  return aux;
}

Isometry Isometry::compose(const Isometry& r_isometry) const {
  Isometry aux = (*this) * r_isometry;
  return aux;
}

Isometry Isometry::rotateAround(const Vector3& r_vector, const float& angle) {
  Isometry aux;
  if (r_vector == Vector3::kUnitX) {
    Matrix3 aux_matrix{1.,          0., 0.,         0.,        std::cos(angle),
                       -std::sin(angle), 0., std::sin(angle), std::cos(angle)};
    aux.rotation_matrix = aux.rotation_matrix;
  } else if (r_vector == Vector3::kUnitY) {
    Matrix3 aux_matrix{std::cos(angle), 0.,      -std::sin(angle), 0.,     1.,
                       0,        std::sin(angle), 0,         std::cos(angle)};
    aux.rotation_matrix = aux.rotation_matrix;
  } else if (r_vector == Vector3::kUnitZ) {
    Matrix3 aux_matrix{std::cos(angle), -std::sin(angle), 0.,
                       std::sin(angle), std::cos(angle), 0.,
                      0., 0., 1.};
    aux.rotation_matrix = aux.rotation_matrix;
  } else {
    throw std::out_of_range("Vector is not an axis");
  }
  return aux;
}

Isometry Isometry::fromEulerAngles(const float& roll, const float& pitch,
                                   const float& yaw) {
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
                                             translation_vector, r_vector);
  return aux;
}

Isometry Isometry::operator*(const Isometry& r_isometry) const {
  Isometry aux;
  aux.rotation_matrix =
      matrix_multiplication(rotation_matrix, r_isometry.rotation_matrix);
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
     << "[R: " << r_isometry.rotation() << "]";
  return os;
}

}  // namespace math
}  // namespace ekumen
