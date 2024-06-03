#include <gtest/gtest.h>

#include "../include/forwardops.hpp"
#include "../include/fsymbol.hpp"
#include "../include/reverseops.hpp"
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

TEST(FSymbol, ExpScalar) {
  ad::FSym<double> a{1.0, 1.0}; // should include multivariate tests

  auto c = exp(a);

  EXPECT_DOUBLE_EQ(c.value(), std::exp(1.0));
  EXPECT_DOUBLE_EQ(c.dot(), std::exp(1.0));
}

TEST(FSymbol, LnScalar) {
  ad::FSym<double> a{3.0, 1.0}; // should include multivariate tests

  auto c = ln(a);

  EXPECT_DOUBLE_EQ(c.value(), std::log(3.0));
  EXPECT_DOUBLE_EQ(c.dot(), 1.0 / 3.0);
}

TEST(FSymbol, SinScalar) {
  ad::FSym<double> a{M_PI / 2, 1.0}; // should include multivariate tests

  auto c = sin(a);

  EXPECT_DOUBLE_EQ(c.value(), std::sin(M_PI / 2));
  EXPECT_DOUBLE_EQ(c.dot(), std::cos(M_PI / 2));
}

TEST(FSymbol, CosScalar) {
  ad::FSym<double> a{M_PI / 2, 1.0}; // should include multivariate tests

  auto c = cos(a);

  EXPECT_DOUBLE_EQ(c.value(), std::cos(M_PI / 2));
  EXPECT_DOUBLE_EQ(c.dot(), -std::sin(M_PI / 2));
}

TEST(FSymbol, TanScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = tan(a);

  EXPECT_DOUBLE_EQ(c.value(), std::tan(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), 1.0 / std::pow(std::cos(M_PI / 4), 2));
}

TEST(FSymbol, CotScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = cot(a);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::tan(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), -1.0 / std::pow(std::sin(M_PI / 4), 2));
}

TEST(FSymbol, SecScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = sec(a);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::cos(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), std::tan(M_PI / 4) / std::cos(M_PI / 4));
}

TEST(FSymbol, CscScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = csc(a);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::sin(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(),
                   -std::cos(M_PI / 4) / std::pow(std::sin(M_PI / 4), 2));
}

TEST(FSymbol, SinhScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = sinh(a);

  EXPECT_DOUBLE_EQ(c.value(), std::sinh(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), std::cosh(M_PI / 4));
}

TEST(FSymbol, CoshScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = cosh(a);

  EXPECT_DOUBLE_EQ(c.value(), std::cosh(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), std::sinh(M_PI / 4));
}

TEST(FSymbol, TanhScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = tanh(a);

  EXPECT_DOUBLE_EQ(c.value(), std::tanh(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), 1.0 / std::pow(std::cosh(M_PI / 4), 2));
}

TEST(FSymbol, CothScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = coth(a);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::tanh(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), -1.0 / std::pow(std::sinh(M_PI / 4), 2));
}

TEST(FSymbol, SechScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = sech(a);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::cosh(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), -std::tanh(M_PI / 4) / std::cosh(M_PI / 4));
}

TEST(FSymbol, CschScalar) {
  ad::FSym<double> a{M_PI / 4, 1.0}; // should include multivariate tests

  auto c = csch(a);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::sinh(M_PI / 4));
  EXPECT_DOUBLE_EQ(c.dot(), -1.0 / std::tanh(M_PI / 4) / std::sinh(M_PI / 4));
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

TEST(RSymbol, PowScalar) {
  ad::RSym a{2.0};
  ad::RSym b{3.0};

  auto ca = pow(a, 3.);
  auto cb = pow(b, 4.);

  const auto df_ca = ad::gradient(ca);
  const auto df_cb = ad::gradient(cb);

  EXPECT_DOUBLE_EQ(ca.value(), 8.0);
  EXPECT_DOUBLE_EQ(cb.value(), std::pow(3, 4));
  EXPECT_DOUBLE_EQ(df_ca.at(a), 3 * std::pow(2, 3 - 1));
  EXPECT_DOUBLE_EQ(df_cb.at(b), 4 * std::pow(3, 4 - 1));
}

TEST(RSymbol, PowSymbol) {
  ad::RSym a{2.0};
  ad::RSym b{3.0};

  auto ca = pow(a, b);
  auto cb = pow(b, a);

  const auto df_ca = ad::gradient(ca);
  const auto df_cb = ad::gradient(cb);

  EXPECT_DOUBLE_EQ(ca.value(), std::pow(2, 3));
  EXPECT_DOUBLE_EQ(cb.value(), std::pow(3, 2));

  EXPECT_DOUBLE_EQ(df_ca.at(a), 3 * std::pow(2, 3 - 1));
  EXPECT_DOUBLE_EQ(df_ca.at(b), std::pow(2, 3) * std::log(2));

  EXPECT_DOUBLE_EQ(df_cb.at(a), std::pow(3, 2) * std::log(3));
  EXPECT_DOUBLE_EQ(df_cb.at(b), 2 * std::pow(3, 2 - 1));
}

TEST(RSymbol, ExpScalar) {
  ad::RSym a{M_PI}; // should include multivariate tests

  auto c = exp(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::exp(M_PI));
  EXPECT_DOUBLE_EQ(df_c.at(a), std::exp(M_PI));
}

TEST(RSymbol, LnScalar) {
  ad::RSym a{3.0}; // should include multivariate tests

  auto c = ln(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::log(3.0));
  EXPECT_DOUBLE_EQ(df_c.at(a), 1.0 / 3.0);
}

TEST(RSymbol, SinScalar) {
  ad::RSym a{M_PI / 2}; // should include multivariate tests

  auto c = sin(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::sin(M_PI / 2));
  EXPECT_DOUBLE_EQ(df_c.at(a), std::cos(M_PI / 2));
}

TEST(RSymbol, CosScalar) {
  ad::RSym a{M_PI / 2}; // should include multivariate tests

  auto c = cos(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::cos(M_PI / 2));
  EXPECT_DOUBLE_EQ(df_c.at(a), -std::sin(M_PI / 2));
}

TEST(RSymbol, TanScalar) {
  ad::RSym a{M_PI / 4}; // should include multivariate tests

  auto c = tan(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::tan(M_PI / 4));
  EXPECT_DOUBLE_EQ(df_c.at(a), 1.0 / std::pow(std::cos(M_PI / 4), 2));
}

TEST(RSymbol, CotScalar) {
  ad::RSym a{M_PI / 4}; // should include multivariate tests

  auto c = cot(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::tan(M_PI / 4));
  EXPECT_DOUBLE_EQ(df_c.at(a), -1.0 / std::pow(std::sin(M_PI / 4), 2));
}

TEST(RSymbol, SecScalar) {
  ad::RSym a{M_PI / 4}; // should include multivariate tests

  auto c = sec(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::cos(M_PI / 4));
  EXPECT_DOUBLE_EQ(df_c.at(a), std::tan(M_PI / 4) / std::cos(M_PI / 4));
}

TEST(RSymbol, CscScalar) {
  ad::RSym a{M_PI / 4}; // should include multivariate tests

  auto c = csc(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), 1.0 / std::sin(M_PI / 4));
  EXPECT_DOUBLE_EQ(df_c.at(a),
                   -std::cos(M_PI / 4) / std::pow(std::sin(M_PI / 4), 2));
}

TEST(RSymbol, SinhScalar) {
  ad::RSym a{M_PI / 4}; // should include multivariate tests

  auto c = sinh(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::sinh(M_PI / 4));
  EXPECT_DOUBLE_EQ(df_c.at(a), std::cosh(M_PI / 4));
}

TEST(RSymbol, CoshScalar) {
  ad::RSym a{M_PI / 4}; // should include multivariate tests

  auto c = cosh(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::cosh(M_PI / 4));
  EXPECT_DOUBLE_EQ(df_c.at(a), std::sinh(M_PI / 4));
}

TEST(RSymbol, TanhScalar) {
  ad::RSym a{M_PI / 4}; // should include multivariate tests

  auto c = tanh(a);

  const auto df_c = ad::gradient(c);

  EXPECT_DOUBLE_EQ(c.value(), std::tanh(M_PI / 4));
  EXPECT_DOUBLE_EQ(df_c.at(a), 1.0 / std::pow(std::cosh(M_PI / 4), 2));
}