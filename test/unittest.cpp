#include <gtest/gtest.h>

#include "../include/forwardops.hpp"
#include "../include/fsymbol.hpp"
#include "../include/rsymbol.hpp"

#include <cmath>
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

TEST(FSymbol, PowScalar) {
  ad::FSym<double> a{2.0, 1.0};
  ad::FSym<double> b{3.0, 0.0};

  auto ca = pow(a, 3.);
  auto cb = pow(b, 4.);

  EXPECT_DOUBLE_EQ(ca.value(), 8.0);
  EXPECT_DOUBLE_EQ(cb.value(), std::pow(3, 4));
  EXPECT_DOUBLE_EQ(ca.dot(), 3 * std::pow(2, 3 - 1));
  EXPECT_DOUBLE_EQ(cb.dot(), 4 * std::pow(3, 4 - 1));
}

TEST(RSymbol, AddScalar) {
  ad::RSym a{1.1};
  ad::RSym b{0.5};

  auto c = a + b;
  const auto df_c = ad::gradient(c);

  EXPECT_EQ(c.value(), 1.6);
  EXPECT_EQ(df_c.at(a), 1.0);
  EXPECT_EQ(df_c.at(b), 1.0);
}

TEST(RSymbol, SubScalar) {
  ad::RSym a{1.1};
  ad::RSym b{0.5};

  auto c = a - b;
  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), 0.6);
  EXPECT_DOUBLE_EQ(df_c.at(a), 1.0);
  EXPECT_DOUBLE_EQ(df_c.at(b), -1.0);
}

TEST(RSymbol, MulScalar) {
  ad::RSym a{1.1};
  ad::RSym b{0.5};

  auto c = a * b;
  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), 0.55);
  EXPECT_DOUBLE_EQ(df_c.at(a), 0.5);
  EXPECT_DOUBLE_EQ(df_c.at(b), 1.1);
}

TEST(RSymbol, DivScalar) {
  ad::RSym a{1.1};
  ad::RSym b{0.5};

  auto c = a / b;
  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), 2.2);
  EXPECT_DOUBLE_EQ(df_c.at(a), 1 / 0.5);
  EXPECT_DOUBLE_EQ(df_c.at(b), -1.1 / 0.5 / 0.5);
}