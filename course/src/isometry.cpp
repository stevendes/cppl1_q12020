/*
 * Copyright 2020, Ekumen
 * Isometry library
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 */

#include <cmath>
#include <cstdint>
#include <isometry/isometry.hpp>

namespace ekumen {
namespace math {

// Class constants
const Vector3 Vector3::kUnitX = Vector3(1., 0., 0.);
const Vector3 Vector3::kUnitY = Vector3(0., 1., 0.);
const Vector3 Vector3::kUnitZ = Vector3(0., 0., 1.);
const Vector3 Vector3::kZero = Vector3(0., 0., 0.);

Vector3::Vector3(std::initializer_list<double> elements) : v_(new Elements{}) {
  if (elements.size() != 3) {
    throw std::range_error(
        "Elements out of range, Vector3 only have three elements");
  }
  auto it = elements.begin();
  v_->x_ = *it++;
  v_->y_ = *it++;
  v_->z_ = *it++;
}

Vector3 Vector3::operator+(const Vector3& vector) const {
  return Vector3(x() + vector.x(), y() + vector.y(), z() + vector.z());
}

Vector3 Vector3::operator-(const Vector3& vector) const {
  return Vector3(x() - vector.x(), y() - vector.y(), z() - vector.z());
}

Vector3 Vector3::operator*(const double& value) const {
  return Vector3(x() * value, y() * value, z() * value);
}

Vector3 Vector3::operator*(const Vector3& vector) const {
  return Vector3(x() * vector.x(), y() * vector.y(), z() * vector.z());
}

Vector3 Vector3::operator/(const double& value) const {
  return Vector3(x() / value, y() / value, z() / value);
}

Vector3 Vector3::operator/(const Vector3& vector) const {
  return Vector3(x() / vector.x(), y() / vector.y(), z() / vector.z());
}

Vector3& Vector3::operator+=(const Vector3& vector) {
  *this = *this + vector;
  return *this;
}

Vector3& Vector3::operator-=(const Vector3& vector) {
  *this = *this - vector;
  return *this;
}

Vector3& Vector3::operator*=(const double& value) {
  *this = *this * value;
  return *this;
}

Vector3& Vector3::operator*=(const Vector3& vector) {
  *this = *this * vector;
  return *this;
}

Vector3& Vector3::operator/=(const Vector3& vector) {
  *this = *this / vector;
  return *this;
}

Vector3& Vector3::operator/=(const double& value) {
  *this = *this / value;
  return *this;
}

Vector3& Vector3::operator=(const Vector3& other) {
  if (&other != this) {
    delete v_;
    v_ = new Elements{*(other.v_)};
  }
  return *this;
}

Vector3& Vector3::operator=(Vector3&& other) noexcept {
  std::swap(v_, other.v_);
  return *this;
}

const double& Vector3::operator[](const int& index) const {
  switch (index) {
    case 0:
      return x();
    case 1:
      return y();
    case 2:
      return z();
    default:
      throw std::out_of_range(
          "index out of range, Vector3 only have three elements");
  }
}

double& Vector3::operator[](const int& index) {
  switch (index) {
    case 0:
      return v_->x_;
    case 1:
      return v_->y_;
    case 2:
      return v_->z_;
    default:
      throw std::out_of_range(
          "index out of range, Vector3 only have three elements");
  }
}

bool Vector3::operator==(const Vector3& vector) const {
  return almost_equal(x(), vector.x(), resolution) &&
         almost_equal(y(), vector.y(), resolution) &&
         almost_equal(z(), vector.z(), resolution);
}

bool ekumen::math::Vector3::operator!=(const Vector3& vector) const {
  return !(*this == vector);
}

double Vector3::norm() const { return std::sqrt(dot(*this)); }

double Vector3::dot(const Vector3& vector) const {
  return ((x() * vector.x()) + (y() * vector.y()) + (z() * vector.z()));
}

Vector3 Vector3::cross(const Vector3& vector) const {
  auto i = (y() * vector.z()) - (z() * vector.y());
  auto j = (z() * vector.x()) - (x() * vector.z());
  auto k = (x() * vector.y()) - (y() * vector.x());

  return Vector3(i, j, k);
}

Matrix3::Matrix3(const std::initializer_list<double>& values) {
  if (values.size() != 9) {
    throw std::out_of_range("Invalid initializer list size");
  }
  std::initializer_list<double>::iterator it = values.begin();
  Vector3 r1, r2, r3;
  r1[0] = *it++;
  r1[1] = *it++;
  r1[2] = *it++;

  r2[0] = *it++;
  r2[1] = *it++;
  r2[2] = *it++;

  r3[0] = *it++;
  r3[1] = *it++;
  r3[2] = *it++;
  m_ = Rows{r1, r2, r3};
}

const Vector3& Matrix3::row(uint32_t index) const {
  if (index > 2) {
    throw std::out_of_range("index out of range, Matrix3 only have three rows");
  }
  return (*this)[index];
}

const Vector3 Matrix3::col(uint32_t index) const {
  if (index > 2) {
    throw std::out_of_range("index out of range, Matrix3 only have three rows");
  }
  return Vector3(r1()[index], r2()[index], r3()[index]);
}

Vector3& Matrix3::operator[](const uint32_t index) {
  switch (index) {
    case 0:
      return r1();
    case 1:
      return r2();
    case 2:
      return r3();
    default:
      throw std::out_of_range("Error. Invalid row index for Matrix3");
  }
}

const Vector3& Matrix3::operator[](const uint32_t index) const {
  switch (index) {
    case 0:
      return r1();
    case 1:
      return r2();
    case 2:
      return r3();
    default:
      throw std::out_of_range("Error. Invalid row index for Matrix3");
  }
}

Matrix3 Matrix3::operator+(const Matrix3& matrix) const {
  Matrix3 aux(*this);
  aux += matrix;
  return aux;
}

Matrix3 Matrix3::operator-(const Matrix3& matrix) const {
  Matrix3 aux(*this);
  aux -= matrix;
  return aux;
}

Matrix3 Matrix3::operator*(const double& value) const {
  Matrix3 aux(*this);
  aux *= value;
  return aux;
}

Matrix3 Matrix3::operator*(const Matrix3& matrix) const {
  Matrix3 aux(*this);
  aux *= matrix;
  return aux;
}

Matrix3 Matrix3::operator/(const Matrix3& matrix) const {
  Matrix3 aux(*this);
  aux /= matrix;
  return aux;
}

Vector3 Matrix3::operator*(const Vector3& vector) const {
  Vector3 result;
  result.x() =
      r1().x() * vector.x() + r1().y() * vector.y() + r1().z() * vector.z();
  result.y() =
      r2().x() * vector.x() + r2().y() * vector.y() + r2().z() * vector.z();
  result.z() =
      r3().x() * vector.x() + r3().y() * vector.y() + r3().z() * vector.z();
  return result;
}

Matrix3 Matrix3::operator/(const double& value) const {
  Matrix3 aux(*this);
  aux.r1() /= value;
  aux.r2() /= value;
  aux.r2() /= value;
  return aux;
}

Matrix3& Matrix3::operator+=(const Matrix3& matrix) {
  r1() += matrix.r1();
  r2() += matrix.r2();
  r3() += matrix.r3();
  return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& matrix) {
  r1() -= matrix.r1();
  r2() -= matrix.r2();
  r3() -= matrix.r3();
  return *this;
}

Matrix3& Matrix3::operator*=(const double& value) {
  r1() *= value;
  r2() *= value;
  r3() *= value;
  return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& matrix) {
  r1() *= matrix.r1();
  r2() *= matrix.r2();
  r3() *= matrix.r3();
  return *this;
}

Matrix3& Matrix3::operator/=(const Matrix3& matrix) {
  r1() /= matrix.r1();
  r2() /= matrix.r2();
  r3() /= matrix.r3();
  return *this;
}

Matrix3& Matrix3::operator/=(const double& value) {
  r1() /= value;
  r2() /= value;
  r3() /= value;
  return *this;
}

bool Matrix3::operator==(const Matrix3& matrix) const {
  return (r1() == matrix.r1()) && (r2() == matrix.r2()) &&
         (r3() == matrix.r3());
}

bool Matrix3::operator!=(const Matrix3& matrix) const {
  return !(*this == matrix);
}

Matrix3 Matrix3::inverse() const {
  if (almost_equal(det(), 0., 4)) {
    throw std::domain_error("It can not get the inverse of the matrix");
  }
  Matrix3 aux;
  aux.r1().x() = r2().y() * r3().z() - r2().z() * r3().y();
  aux.r1().y() = r1().z() * r3().z() - r1().y() * r3().z();
  aux.r1().z() = r1().y() * r2().z() - r2().y() * r1().z();
  aux.r2().x() = r2().z() * r3().x() - r2().x() * r3().z();
  aux.r2().y() = r1().x() * r3().z() - r1().z() * r3().x();
  aux.r2().z() = r1().z() * r2().x() - r1().x() * r2().z();
  aux.r3().x() = r2().x() * r3().y() - r2().y() * r3().x();
  aux.r3().y() = r1().y() * r3().x() - r1().x() * r3().y();
  aux.r3().z() = r1().x() * r2().y() - r1().y() * r2().x();
  return aux / ((*this).det());
}

double Matrix3::det() const {
  double subdet1 = r2()[1] * r3()[2] - r2()[2] * r3()[1];
  double subdet2 = r2()[0] * r3()[2] - r2()[2] * r3()[0];
  double subdet3 = r2()[0] * r3()[1] - r2()[1] * r3()[0];
  return r1()[0] * subdet1 - r1()[1] * subdet2 + r1()[2] * subdet3;
}

const Matrix3 Matrix3::kIdentity =
    Matrix3(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));

const Matrix3 Matrix3::kZero =
    Matrix3(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0));

const Matrix3 Matrix3::kOnes =
    Matrix3(Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(1, 1, 1));

// Isometry

Isometry Isometry::compose(const Isometry& isometry) const {
  Isometry aux(*this);
  return Isometry(*this) = aux * isometry;
}

Isometry Isometry::inverse() const {
  auto vector_result = (rotation_.inverse() * translation_) * -1;
  return Isometry{vector_result, rotation_.inverse()};
}

Isometry Isometry::fromTranslation(const Vector3& vector) {
  return Isometry(vector, Matrix3::kIdentity);
}

Isometry Isometry::fromEulerAngles(const double yaw, const double pitch,
                                   const double roll) {
  Isometry result = Isometry(rotateAround(Vector3::kUnitX, yaw)) *
                    Isometry(rotateAround(Vector3::kUnitY, pitch)) *
                    Isometry(rotateAround(Vector3::kUnitZ, roll));
  return result;
}

Isometry Isometry::rotateAround(const Vector3& axis, const double angle) {
  Matrix3 result;
  auto cos = std::cos(angle);
  auto sin = std::sin(angle);
  result.r1().x() = cos + (axis.x() * axis.x()) * (1 - cos);
  result.r1().y() = axis.x() * axis.y() * (1 - cos) - axis.z() * sin;
  result.r1().z() = axis.x() * axis.z() * (1 - cos) + axis.y() * sin;

  result.r2().x() = axis.y() * axis.x() * (1 - cos) + axis.z() * sin;
  result.r2().y() = cos + (axis.y() * axis.y()) * (1 - cos);
  result.r2().z() = axis.y() * axis.z() * (1 - cos) - axis.x() * sin;

  result.r3().x() = axis.z() * axis.x() * (1 - cos) + axis.y() * sin;
  result.r3().y() = axis.z() * axis.y() * (1 - cos) + axis.x() * sin;
  result.r3().z() = cos + (axis.z() * axis.z()) * (1 - cos);
  return Isometry(Vector3(), result);
}

// // Operators
bool Isometry::operator==(const Isometry& isometry) const {
  if (rotation_ != isometry.rotation_) {
    return false;
  }
  if (translation_ != isometry.translation_) {
    return false;
  }
  return true;
}

Vector3 Isometry::operator*(const Vector3& vector) const {
  return (rotation_ * vector + translation_);
}

Isometry Isometry::operator*(const Isometry& isometry) const {
  Isometry aux(*this);
  aux *= isometry;
  return aux;
}

Isometry& Isometry::operator*=(const Isometry& isometry) {
  translation_ = rotation_ * isometry.translation() + translation_;
  rotation_ *= isometry.rotation();
  return *this;
}

}  // namespace math
}  // namespace ekumen
