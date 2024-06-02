#include "../include/fsymbol.hpp"
#include "../include/rsymbol.hpp"

#include <gtest/gtest.h>

TEST(FSymbol, Addition) {
  ad::FSym<double> a{1.1, 1.0};
  ad::FSym<double> b{0.5, 1.0};

  auto c = a + b;

  EXPECT_DOUBLE_EQ(c.value(), 1.6);
  EXPECT_DOUBLE_EQ(c.dot(), 2.0);
}