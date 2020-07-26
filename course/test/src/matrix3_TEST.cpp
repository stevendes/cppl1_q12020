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

GTEST_TEST(Matrix3Test, Matrix3FullTests) {
  const double kTolerance{1e-12};
  Matrix3 m1{1., 2., 3., 4., 5., 6., 7., 8., 9.};
  const Matrix3 m2{1., 2., 3., 4., 5., 6., 7., 8., 9.};
  const Matrix3 m3{1., 2., 3., 4., 5., 6., 7., 8., 9.};

  EXPECT_EQ(Matrix3::kIdentity, Matrix3({1., 0., 0., 0., 1., 0., 0., 0., 1.}));
  EXPECT_EQ(Matrix3::kOnes, Matrix3({1., 1., 1., 1., 1., 1., 1., 1., 1.}));
  EXPECT_EQ(Matrix3::kZero, Matrix3({0., 0., 0., 0., 0., 0., 0., 0., 0.}));

  EXPECT_EQ(m2 - m3, Matrix3({0., 0., 0., 0., 0., 0., 0., 0., 0.}));
  EXPECT_EQ(m2 + m3, Matrix3({2., 4., 6., 8., 10., 12., 14., 16., 18.}));
  EXPECT_EQ(m2 * m3, Matrix3({1., 4., 9., 16., 25., 36., 49., 64., 81.}));
  EXPECT_EQ(m2 / m3, Matrix3({1., 1., 1., 1., 1., 1., 1., 1., 1.}));
  EXPECT_EQ(m2 * 2, Matrix3({2., 4., 6., 8., 10., 12., 14., 16., 18.}));
  EXPECT_EQ(2 * m2, Matrix3({2., 4., 6., 8., 10., 12., 14., 16., 18.}));
  EXPECT_EQ(m2 * Vector3(1., 0., 0.), Vector3(1., 4., 7.));
  EXPECT_NEAR(m2.det(), 0., kTolerance);

  EXPECT_EQ(m1 += m3, Matrix3({2., 4., 6., 8., 10., 12., 14., 16., 18.}));
  EXPECT_EQ(m1 -= m3, Matrix3({1., 2., 3., 4., 5., 6., 7., 8., 9.}));
  EXPECT_EQ(m1 *= m3, Matrix3({1., 4., 9., 16., 25., 36., 49., 64., 81.}));
  EXPECT_EQ(m1 /= m3, Matrix3({1., 2., 3., 4., 5., 6., 7., 8., 9.}));
  EXPECT_EQ(m1 *= 2, Matrix3({2., 4., 6., 8., 10., 12., 14., 16., 18.}));
  EXPECT_EQ(m1 /= 2, Matrix3({1., 2., 3., 4., 5., 6., 7., 8., 9.}));

  m1 = Matrix3({1., 4., 9., 16., 25., 36., 49., 64., 81.});
  EXPECT_TRUE(m1 == m2 * m3);
  EXPECT_TRUE(m1 != m2);
  EXPECT_EQ(Matrix3::kIdentity, Matrix3::kIdentity);
  EXPECT_EQ(Matrix3::kOnes, Matrix3::kOnes);
  EXPECT_EQ(Matrix3::kZero, Matrix3::kZero);
  EXPECT_NE(Matrix3::kIdentity, Matrix3::kOnes);
  EXPECT_NE(Matrix3::kIdentity, Matrix3::kZero);
  EXPECT_NE(Matrix3::kOnes, Matrix3::kZero);

  std::stringstream ss;
  ss << m3;
  EXPECT_EQ(ss.str(), "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]");

  EXPECT_EQ(m2.row(0), Vector3(1., 2., 3.));
  EXPECT_EQ(m2.row(1), Vector3(4., 5., 6.));
  EXPECT_EQ(m2.row(2), Vector3(7., 8., 9.));

  EXPECT_EQ(m2.col(0), Vector3(1., 4., 7.));
  EXPECT_EQ(m2.col(1), Vector3(2., 5., 8.));
  EXPECT_EQ(m2.col(2), Vector3(3., 6., 9.));

  EXPECT_EQ(m2[0][0], 1);
  EXPECT_EQ(m2[0][1], 2);
  EXPECT_EQ(m2[0][2], 3);
  EXPECT_EQ(m2[1][0], 4);
  EXPECT_EQ(m2[1][1], 5);
  EXPECT_EQ(m2[1][2], 6);
  EXPECT_EQ(m2[2][0], 7);
  EXPECT_EQ(m2[2][1], 8);
  EXPECT_EQ(m2[2][2], 9);

  Matrix3 m4;
  EXPECT_EQ(m4, Matrix3::kZero);
  m4[0][0] = 1;
  m4[0][1] = 2;
  m4[0][2] = 3;
  m4[1][0] = 4;
  m4[1][1] = 5;
  m4[1][2] = 6;
  m4[2][0] = 7;
  m4[2][1] = 8;
  m4[2][2] = 9;
  EXPECT_EQ(m4, m2);
  m4[2][2] = 10;
  EXPECT_NEAR(m4.det(), -2.9999999999999996, kTolerance);

  EXPECT_ANY_THROW(m2.col(-1));
  EXPECT_ANY_THROW(m2.col(4));
  EXPECT_ANY_THROW(m2.col(1000));

  EXPECT_ANY_THROW(m2.row(-1));
  EXPECT_ANY_THROW(m2.row(4));
  EXPECT_ANY_THROW(m2.row(1000));

  EXPECT_ANY_THROW(m2[-1][0]);
  EXPECT_ANY_THROW(m2[0][-1]);
  EXPECT_ANY_THROW(m2[4][0]);
  EXPECT_ANY_THROW(m2[0][4]);
  EXPECT_ANY_THROW(m2[1234][0]);
  EXPECT_ANY_THROW(m2[0][1234]);

  EXPECT_ANY_THROW(m4[-1][0] = 0);
  EXPECT_ANY_THROW(m4[0][-1] = 0);
  EXPECT_ANY_THROW(m4[4][0] = 0);
  EXPECT_ANY_THROW(m4[0][4] = 0);
  EXPECT_ANY_THROW(m4[1234][0] = 0);
  EXPECT_ANY_THROW(m4[0][1234] = 0);

  Matrix3 m4_moved = std::move(m4);
  EXPECT_EQ(m4_moved[0][0], 1);
  EXPECT_EQ(m4_moved[0][1], 2);
  EXPECT_EQ(m4_moved[0][2], 3);
  EXPECT_EQ(m4_moved[1][0], 4);
  EXPECT_EQ(m4_moved[1][1], 5);
  EXPECT_EQ(m4_moved[1][2], 6);
  EXPECT_EQ(m4_moved[2][0], 7);
  EXPECT_EQ(m4_moved[2][1], 8);
  EXPECT_EQ(m4_moved[2][2], 10);
}

}  // namespace
}  // namespace test
}  // namespace math
}  // namespace ekumen

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
