#include <gtest/gtest.h>

#include "../include/fsymbol.hpp"
#include "../include/rsymbol.hpp"

/**
 * @brief Include testing for partial derivatives of FSym
 *
 */

TEST(FSymbol, AddScalar) {
  ad::FSym<double> a{1.1, 1.0};
  ad::FSym<double> b{0.5, 1.0};

  auto c = a + b;

  EXPECT_DOUBLE_EQ(c.value(), 1.6);
  EXPECT_DOUBLE_EQ(c.dot(), 2.0);
}

TEST(FSymbol, SubScalar) {
  ad::FSym<double> a{1.1, 1.0};
  ad::FSym<double> b{0.5, 1.0};

  auto c = a - b;

  EXPECT_DOUBLE_EQ(c.value(), 0.6);
  EXPECT_DOUBLE_EQ(c.dot(), 0.0);
}

TEST(FSymbol, MulScalar) {
  ad::FSym<double> a{1.1, 1.0};
  ad::FSym<double> b{0.5, 0.0};

  auto c = a * b;

  EXPECT_DOUBLE_EQ(c.value(), 0.55);
  EXPECT_DOUBLE_EQ(c.dot(), .5);
}

TEST(FSymbol, DivScalar) {
  ad::FSym<double> a{1.1, 1.0};
  ad::FSym<double> b{0.5, 0.0};

  auto c = a / b;

  EXPECT_DOUBLE_EQ(c.value(), 2.2);
  EXPECT_DOUBLE_EQ(c.dot(), 1 / 0.5);
}