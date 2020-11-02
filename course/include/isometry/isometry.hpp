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
  Isometry() : rotation_matrix{Matrix3::kIdentity} {};

  Isometry(const Vector3& r_vector, const Matrix3& r_matrix)
      : translation_vector{r_vector}, rotation_matrix{r_matrix}{};

  static Isometry fromTranslation(const Vector3& r_vector);

  static Isometry fromEulerAngles(const float& roll, const float& pitch,
                                  const float& yaw);

  Vector3 translation() const;

  Vector3 transform(const Vector3& r_vector) const;

  Isometry inverse() const;

  Matrix3 rotation() const;

  static Isometry rotateAround(const Vector3& r_vector, const float& angle);

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
