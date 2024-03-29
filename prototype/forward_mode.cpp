#include "forward_mode.h"

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

namespace ad {

Sym::Sym(double _val, double _dot) : m_val(_val), m_dot(_dot) {}

Sym::Sym(double _val) : m_val(_val) {}

auto Sym::value() const noexcept -> double { return m_val; }
auto Sym::dot() const noexcept -> double { return m_dot; }

auto operator+(const Sym &lhs, const Sym &rhs) -> Sym {
  return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()};
}

auto operator-(const Sym &lhs, const Sym &rhs) -> Sym {
  return {lhs.value() - rhs.value(), lhs.dot() - rhs.dot()};
}

auto operator*(const Sym &lhs, const Sym &rhs) -> Sym {
  return {lhs.value() * rhs.value(),
          lhs.dot() * rhs.value() + rhs.dot() * lhs.value()};
}

auto operator/(const Sym &lhs, const Sym &rhs) -> Sym {
  const double df = (lhs.dot() * rhs.value() - lhs.value() * rhs.dot()) /
                    std::pow(rhs.value(), 2);
  return {lhs.value() / rhs.value(), df};
}
// has problems to address df.dexp and df.dbase case
auto pow(const Sym &base, const Sym &exp) -> Sym {
  const double df_base =
      std::log(base.value()) * std::pow(base.value(), exp.value()) * exp.dot();
  return {std::pow(base.value(), exp.value()), df_base};
}

auto pow(const Sym &base, double exp) -> Sym {
  const double df_base = base.dot() * std::pow(base.value(), exp - 1);
  return {std::pow(base.value(), exp), df_base};
}

auto exp(const Sym &rhs) noexcept -> Sym {
  const double value = std::exp(rhs.value());
  const double df = value * rhs.dot();
  return {value, df};
}

auto ln(const Sym &rhs) noexcept -> Sym {
  const double value = std::log(rhs.value());
  const double df = (1.0f / rhs.value()) * rhs.dot();
  return {value, df};
}

auto sin(const Sym &rhs) noexcept -> Sym {
  const double value = std::sin(rhs.value());
  const double df = std::cos(rhs.value()) * rhs.dot();
  return {value, df};
}

auto cos(const Sym &rhs) noexcept -> Sym {
  const double value = std::cos(rhs.value());
  const double df = -std::sin(rhs.value()) * rhs.dot();
  return {value, df};
}

auto tan(const Sym &rhs) noexcept -> Sym {
  const double value = std::tan(rhs.value());
  const double df = std::pow(1.0f / std::cos(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto cot(const Sym &rhs) noexcept -> Sym {
  const double value = 1.0f / std::tan(rhs.value());
  const double df = -std::pow(1.0f / std::sin(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto sec(const Sym &rhs) noexcept -> Sym {
  const double value = 1.0f / std::cos(rhs.value());
  const double df = value * std::tan(rhs.value()) * rhs.dot();
  return {value, df};
}

auto csc(const Sym &rhs) noexcept -> Sym {
  const double value = 1.0f / std::sin(rhs.value());
  const double df = -value * (1.0f / std::tan(rhs.value())) * rhs.dot();
  return {value, df};
}

auto sinh(const Sym &rhs) noexcept -> Sym {
  const double value = std::sinh(rhs.value());
  const double df = std::cosh(rhs.value()) * rhs.dot();
  return {value, df};
}

auto cosh(const Sym &rhs) noexcept -> Sym {
  const double value = std::cosh(rhs.value());
  const double df = -std::sinh(rhs.value()) * rhs.dot();
  return {value, df};
}

auto tanh(const Sym &rhs) noexcept -> Sym {
  const double value = std::tanh(rhs.value());
  const double df = std::pow(1.0f / std::cosh(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto coth(const Sym &rhs) noexcept -> Sym {
  const double value = 1.0f / std::tanh(rhs.value());
  const double df = -std::pow(1.0f / std::sinh(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto sech(const Sym &rhs) noexcept -> Sym {
  const double value = 1.0f / std::cosh(rhs.value());
  const double df = value * std::tanh(rhs.value()) * rhs.dot();
  return {value, df};
}

auto csch(const Sym &rhs) noexcept -> Sym {
  const double value = 1.0f / std::sinh(rhs.value());
  const double df = -value * (1.0f / std::tanh(rhs.value())) * rhs.dot();
  return {value, df};
}

auto make_jvp() -> std::vector<double>;

}; // namespace ad

/**
 * todo:
 * - higher-order diff in forward mode autodiff
 * - resolve issues with derivative wrt b
 * */

// auto main(void) -> int {
//   auto a = ad::Sym{1.5, 0}; // 0 -- wrt b
//   auto b = ad::Sym{0.5, 1}; // 0 -- wrt a

//   auto f = [](const ad::Sym &a, const ad::Sym &b) -> ad::Sym {
//     return ad::sin(a * b) / ad::cos(b) * ad::pow(a, b);
//   };

//   auto f1 = f(a, b);  // first-order diff wrt b
//   auto f2 = f(f1, b); // second-order diff wrt a

//   std::cout << std::setprecision(15) << f1.dot() << '\n';
//   // std::cout << std::setprecision(15) << f1.value() << '\n';
//   // std::cout << std::setprecision(15) << f2.value() << '\n';
//   std::cout << std::setprecision(15) << f2.dot() << '\n';
// }
