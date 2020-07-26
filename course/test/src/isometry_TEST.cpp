/* Copyright 2020, Ekumen
 * Isometry library tests
 * Author: Agustin Alba Chicar, 2019
 * Author: Gerardo Puga, 2020
 * Author: Jose Tomas Lorente, 2020
 *
 * This file describes a challenge of a C++ L1 Padawan. The goal
 * of this unit test is to suggest an API and the abstractions
 * needed to implement an isometry.
 */

#include <cmath>
#include <sstream>
#include <string>

#include <isometry/isometry.hpp>
#include "gtest/gtest.h"

namespace ekumen {
namespace math {
namespace test {
namespace {

testing::AssertionResult areAlmostEqual(const Isometry &obj1,
                                        const Isometry &obj2,
                                        const double tolerance) {
  if (std::abs(obj1.translation()[0] - obj2.translation()[0]) > tolerance ||
      std::abs(obj1.translation()[1] - obj2.translation()[1]) > tolerance ||
      std::abs(obj1.translation()[2] - obj2.translation()[2]) > tolerance ||
      std::abs(obj1.rotation()[0][0] - obj2.rotation()[0][0]) > tolerance ||
      std::abs(obj1.rotation()[0][1] - obj2.rotation()[0][1]) > tolerance ||
      std::abs(obj1.rotation()[0][2] - obj2.rotation()[0][2]) > tolerance ||
      std::abs(obj1.rotation()[1][0] - obj2.rotation()[1][0]) > tolerance ||
      std::abs(obj1.rotation()[1][1] - obj2.rotation()[1][1]) > tolerance ||
      std::abs(obj1.rotation()[1][2] - obj2.rotation()[1][2]) > tolerance ||
      std::abs(obj1.rotation()[2][0] - obj2.rotation()[2][0]) > tolerance ||
      std::abs(obj1.rotation()[2][1] - obj2.rotation()[2][1]) > tolerance ||
      std::abs(obj1.rotation()[2][2] - obj2.rotation()[2][2]) > tolerance) {
    return testing::AssertionFailure() << "The isometries are not almost equal";
  }
  return testing::AssertionSuccess();
}

testing::AssertionResult areAlmostEqual(const Matrix3 &obj1,
                                        const Matrix3 &obj2,
                                        const double tolerance) {
  if (std::abs(obj1[0][0] - obj2[0][0]) > tolerance ||
      std::abs(obj1[0][1] - obj2[0][1]) > tolerance ||
      std::abs(obj1[0][2] - obj2[0][2]) > tolerance ||
      std::abs(obj1[1][0] - obj2[1][0]) > tolerance ||
      std::abs(obj1[1][1] - obj2[1][1]) > tolerance ||
      std::abs(obj1[1][2] - obj2[1][2]) > tolerance ||
      std::abs(obj1[2][0] - obj2[2][0]) > tolerance ||
      std::abs(obj1[2][1] - obj2[2][1]) > tolerance ||
      std::abs(obj1[2][2] - obj2[2][2]) > tolerance) {
    return testing::AssertionFailure() << "The isometries are not almost equal";
  }
  return testing::AssertionSuccess();
}

GTEST_TEST(IsometryTest, IsometryFullTests) {
  const double kTolerance{1e-12};
  const Isometry t1 = Isometry::fromTranslation(Vector3{1., 2., 3.});
  const Isometry t2{Vector3{1., 2., 3.}, Matrix3::kIdentity};

  EXPECT_EQ(t1, t2);

  // This is not mathematically correct but it could be a nice to have.
  EXPECT_EQ(t1 * Vector3(1., 1., 1.), Vector3(2., 3., 4.));
  EXPECT_EQ(t1.transform(Vector3(std::initializer_list<double>({1., 1., 1.}))),
            Vector3(2., 3., 4.));
  EXPECT_EQ(t1.inverse() * Vector3(2., 3., 4.), Vector3(1., 1., 1.));
  EXPECT_EQ(t1 * t2 * Vector3(1., 1., 1.), Vector3(3., 5., 7.));
  EXPECT_EQ(t1.compose(t2) * Vector3(1., 1., 1.), Vector3(3., 5., 7.));

  // Composes rotations.
  const Isometry t3{Isometry::rotateAround(Vector3::kUnitX, M_PI / 2.)};
  const Isometry t4{Isometry::rotateAround(Vector3::kUnitY, M_PI / 4.)};
  const Isometry t5{Isometry::rotateAround(Vector3::kUnitZ, M_PI / 8.)};
  const Isometry t6{Isometry::fromEulerAngles(M_PI / 2., M_PI / 4., M_PI / 8.)};
  EXPECT_TRUE(areAlmostEqual(t6, t3 * t4 * t5, kTolerance));

  EXPECT_EQ(t3.translation(), Vector3::kZero);
  const double pi_8{M_PI / 8.};
  const double cpi_8{std::cos(pi_8)};  // 0.923879532
  const double spi_8{std::sin(pi_8)};  // 0.382683432
  EXPECT_TRUE(areAlmostEqual(
      t5.rotation(), Matrix3{cpi_8, -spi_8, 0., spi_8, cpi_8, 0., 0., 0., 1.},
      kTolerance));

  std::stringstream ss;
  ss << t5;
  std::string answer = "[T: (x: 0, y: 0, z: 0), ";
  answer += "R:[[0.923879533, -0.382683432, 0],";
  answer += " [0.382683432, 0.923879533, 0], [0, 0, 1]]]";
  EXPECT_EQ(ss.str(), answer);

  Isometry t7;
  EXPECT_EQ(t7.rotation()[2][2], 0);
  EXPECT_EQ(t7.translation()[2], 0);

  Isometry t8 = Isometry();
  EXPECT_EQ(t8.rotation()[2][2], 0);
  EXPECT_EQ(t8.translation()[2], 0);

  Isometry t9 = Isometry::fromTranslation(Vector3{1., 2., 3.});
  const Isometry t10{Vector3{2., 4., 6.}, Matrix3::kIdentity};
  EXPECT_EQ(t9 *= t2, t10);
  EXPECT_EQ(t9 * Vector3(1., 1., 1.), Vector3(3., 5., 7.));
}

}  // namespace
}  // namespace test
}  // namespace math
}  // namespace ekumen

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
