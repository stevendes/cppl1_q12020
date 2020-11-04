/*
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 */

#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <isometry/matrix3.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace ekumen {

namespace math {

class Isometry {
 public:
  /// Constructs an Isometry with default values.
  Isometry() : rotation_matrix{Matrix3::kIdentity} {};

  /// Constructs an Isometry.
  /// @param r_vector Initial value of the translation vector.
  /// @param r_matrix Initial value of the rotation matrix.
  Isometry(const Vector3& r_vector, const Matrix3& r_matrix)
      : translation_vector{r_vector}, rotation_matrix{r_matrix}{};

  /// Gets the Isometry matrix from a vector
  /// @param r_vector Value of the translation vector.
  static Isometry fromTranslation(const Vector3& r_vector);

  /// Gets the Isometry matrix from Euler angles
  /// @param roll Value of the roll angle.
  /// @param pitch Value of the pitch angle.
  /// @param yaw Value of the yaw angle.
  static Isometry fromEulerAngles(const double& roll, const double& pitch,
                                  const double& yaw);

  Vector3 translation() const;

  Vector3 transform(const Vector3& r_vector) const;

  Isometry inverse() const;

  Matrix3 rotation() const;

  /// Gets the Isometry matrix from rotation a certain angle around a given direction unitary-vector
  /// @param r_vector Unitary Vector to rotate around.
  /// @param angle Value of the angle of rotation.
  static Isometry rotateAround(const Vector3& r_vector, const double& angle);

  /// Gets the Isometry matrix of the result of a composed movement with a given Isometry Matrix
  /// @param r_isometry Isometry matrix of the given movement.
  Isometry compose(const Isometry& r_isometry) const;

  bool operator==(const Isometry& r_isometry) const;
  bool operator!=(const Isometry& r_isometry) const;

  Vector3 operator*(const Vector3& r_vector) const;

  Isometry operator*(const Isometry& r_isometry) const;

  Isometry& operator*=(const Isometry& r_isometry);

 private:
  Vector3 translation_vector; 
  Matrix3 rotation_matrix;
};

std::ostream& operator<<(std::ostream& os, const Isometry& r_isometry);

}  // namespace math

}  // namespace ekumen
