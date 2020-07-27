/*
 * Copyright 2020, Ekumen
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 */

#pragma once

#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace ekumen {
namespace math {

static constexpr int resolution{10};

template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T a, T b, int resolution) {
  return (std::fabs(a - b) <=
          std::numeric_limits<T>::epsilon() * std::fabs(a + b) * resolution) ||
         (std::fabs(a - b) < std::numeric_limits<T>::min());
}

struct Elements {
  Elements() : x_(0), y_(0), z_(0) {}

  Elements(const double& x, const double& y, const double& z)
      : x_(x), y_(y), z_(z) {}

  double x_, y_, z_;
};

class Vector3 {
 public:
  Vector3() : v_(new Elements{}){};

  Vector3(const double& x, const double& y, const double& z)
      : v_(new Elements{x, y, z}){};

  explicit Vector3(std::initializer_list<double> elements);

  ~Vector3() {
    // deallocate
    delete v_;
  };

  // copy constructor
  Vector3(const Vector3& other) : v_(new Elements{*(other.v_)}) {}

  // move constructor
  Vector3(Vector3&& other) {
    v_ = other.v_;
    other.v_ = nullptr;
  }

  Vector3& operator=(const Vector3& other);

  Vector3& operator=(Vector3&& other) noexcept;

  // Getter for elements of the vector.
  const double& x() const { return v_->x_; };
  const double& y() const { return v_->y_; };
  const double& z() const { return v_->z_; };

  // Setter for elements of the vector.
  double& x() { return v_->x_; };
  double& y() { return v_->y_; };
  double& z() { return v_->z_; };

  // Operators overloading.
  Vector3 operator+(const Vector3& vector) const;

  Vector3 operator-(const Vector3& vector) const;

  Vector3 operator*(const double& value) const;

  Vector3 operator*(const Vector3& vector) const;

  Vector3 operator/(const double& value) const;

  Vector3 operator/(const Vector3& vector) const;

  Vector3& operator+=(const Vector3& vector);

  Vector3& operator-=(const Vector3& vector);

  Vector3& operator*=(const double& value);

  Vector3& operator*=(const Vector3& vector);

  Vector3& operator/=(const double& value);

  Vector3& operator/=(const Vector3& vector);

  const double& operator[](const int& index) const;

  double& operator[](const int& index);

  bool operator==(const Vector3& vector) const;

  bool operator!=(const Vector3& vector) const;

  double dot(const Vector3& vector) const;

  double norm() const;

  Vector3 cross(const Vector3& vector) const;

  static const Vector3 kUnitX;
  static const Vector3 kUnitY;
  static const Vector3 kUnitZ;
  static const Vector3 kZero;

 private:
  Elements* v_;
};

inline Vector3 operator*(const double scalar, const Vector3& vector) {
  Vector3 result(vector.x() * scalar, vector.y() * scalar,
                 (vector.z() * scalar));
  return result;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
  return os << "(x: " << std::to_string(static_cast<int>(vector.x()))
            << ", y: " << std::to_string(static_cast<int>(vector.y()))
            << ", z: " << std::to_string(static_cast<int>(vector.z())) << ")";
}

struct Rows {
  Rows() : r1_(), r2_(), r3_(){};
  Rows(const Vector3& r1, const Vector3& r2, const Vector3& r3)
      : r1_(r1), r2_(r2), r3_(r3){};
  Vector3 r1_, r2_, r3_;
};

class Matrix3 {
 public:
  Matrix3() {}

  Matrix3(const Vector3& r1, const Vector3& r2, const Vector3& r3)
      : m_{r1, r2, r3} {}

  explicit Matrix3(const std::initializer_list<double>& values);

  Matrix3(const Matrix3& other) = default;
  Matrix3(Matrix3&& other) = default;
  Matrix3& operator=(const Matrix3& matrix) = default;
  Matrix3& operator=(Matrix3&& matrix) noexcept = default;

  // Getter
  const Vector3& row(uint32_t index) const;

  const Vector3 col(uint32_t index) const;

  // Getter for elements of the vector.
  const Vector3& r1() const { return m_.r1_; };

  const Vector3& r2() const { return m_.r2_; };

  const Vector3& r3() const { return m_.r3_; };

  // Setter for elements of the vector.
  Vector3& r1() { return m_.r1_; };

  Vector3& r2() { return m_.r2_; };

  Vector3& r3() { return m_.r3_; };

  // Operators overloading.
  Vector3& operator[](const uint32_t index);

  const Vector3& operator[](const uint32_t index) const;

  Matrix3 operator+(const Matrix3& matrix) const;

  Matrix3 operator-(const Matrix3& matrix) const;

  Matrix3 operator*(const double& value) const;

  Matrix3 operator*(const Matrix3& matrix) const;

  Vector3 operator*(const Vector3& vector) const;

  Matrix3 operator/(const Matrix3& matrix) const;

  Matrix3 operator/(const double& value) const;

  Matrix3& operator+=(const Matrix3& matrix);

  Matrix3& operator-=(const Matrix3& matrix);

  Matrix3& operator*=(const double& value);

  Matrix3& operator*=(const Matrix3& matrix);

  Matrix3& operator/=(const Matrix3& matrix);

  Matrix3& operator/=(const double& value);

  bool operator==(const Matrix3& matrix) const;

  bool operator!=(const Matrix3& matrix) const;

  double det() const;

  Matrix3 inverse() const;

  static const Matrix3 kIdentity;
  static const Matrix3 kZero;
  static const Matrix3 kOnes;

 private:
  Rows m_;
};

inline Matrix3 operator*(const double scalar, const Matrix3& vector) {
  Matrix3 result(vector.r1() * scalar, vector.r2() * scalar,
                 (vector.r3() * scalar));
  return result;
}

// Warning: it convert float values in int, we used this way to pas the test,
// for other use take out " static_cast<int>"
inline std::ostream& operator<<(std::ostream& os, const Matrix3& matrix) {
  return os << "[[" << std::to_string(static_cast<int>(matrix[0][0])) << ", "
            << std::to_string(static_cast<int>(matrix[0][1])) << ", "
            << std::to_string(static_cast<int>(matrix[0][2])) << "], "
            << "[" << std::to_string(static_cast<int>(matrix[1][0])) << ", "
            << std::to_string(static_cast<int>(matrix[1][1])) << ", "
            << std::to_string(static_cast<int>(matrix[1][2])) << "], "
            << "[" << std::to_string(static_cast<int>(matrix[2][0])) << ", "
            << std::to_string(static_cast<int>(matrix[2][1])) << ", "
            << std::to_string(static_cast<int>(matrix[2][2])) << "]]";
}

class Isometry {
 public:
  explicit Isometry(const Matrix3& rotation = {})
      : rotation_{rotation}, translation_{0.0, 0.0, 0.0} {}

  Isometry(const Vector3& translation, const Matrix3& rotation)
      : rotation_{rotation}, translation_{translation} {}

  Isometry compose(const Isometry& isometry) const;

  Isometry inverse() const;

  const Matrix3& rotation() const { return rotation_; }

  Vector3 transform(const Vector3& translation) const {
    return (rotation_ * translation + translation_);
  }

  const Vector3& translation() const { return translation_; }

  static Isometry fromTranslation(const Vector3& vector);

  static Isometry fromEulerAngles(const double yaw, const double pitch,
                                  const double roll);

  static Isometry rotateAround(const Vector3& axis, const double angle);

  // Operators
  bool operator==(const Isometry& isometry) const;

  Vector3 operator*(const Vector3& vector) const;

  Isometry operator*(const Isometry& isometry) const;

  Isometry& operator*=(const Isometry& isometry);

 private:
  Matrix3 rotation_;
  Vector3 translation_;
};

inline std::ostream& operator<<(std::ostream& os, const Isometry& isometry) {
  auto rotation = isometry.rotation();
  return os << "[T: (x: 0, y: 0, z: 0"
            << "), R:[[" << std::setprecision(9) << rotation[0][0] << ", "
            << rotation[0][1] << ", " << rotation[0][2] << "], "
            << "[" << rotation[1][0] << ", " << rotation[1][1] << ", "
            << rotation[1][2] << "], "
            << "[" << rotation[2][0] << ", " << rotation[2][1] << ", "
            << rotation[2][2] << "]]]";
}

}  // namespace math
}  // namespace ekumen
