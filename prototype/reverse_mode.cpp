#include "reverse_mode.h"

#include <cmath>
#include <functional>
#include <map>

namespace ad {

Symbol::Symbol(const std::map<Symbol, double> &_local_gradient, double _value)
    : m_local_gradient(_local_gradient), m_value(_value) {}

Symbol::Symbol(double _value) : m_value(_value) {}

auto Symbol::value() const noexcept -> double { return m_value; }

auto Symbol::local_gradient() const noexcept -> std::map<Symbol, double> {
  return m_local_gradient;
}

auto Symbol::operator<(const Symbol &rhs) const -> bool {
  return m_value < rhs.m_value;
}

auto Symbol::operator>(const Symbol &rhs) const -> bool {
  return m_value > rhs.m_value;
}

auto Symbol::operator==(const Symbol &rhs) const -> bool {
  return m_value == rhs.m_value;
}

auto Symbol::operator!=(const Symbol &rhs) const -> bool {
  return m_value != rhs.m_value;
}

auto operator+(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {{{lhs, 1.0}, {rhs, 1.0}}, lhs.value() + rhs.value()};
}

auto operator-(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {{{lhs, 1.0}, {rhs, -1.0}}, lhs.value() - rhs.value()};
}

auto operator*(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {{{lhs, rhs.value()}, {rhs, lhs.value()}}, lhs.value() * rhs.value()};
}

auto operator/(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  const Symbol inverse{{{rhs, -1.0 / std::pow(rhs.value(), 2)}},
                       1.0 / rhs.value()};
  return lhs * inverse;
}

auto pow(const Symbol &base, const Symbol &exponent) -> Symbol {
  const double df_base =
      exponent.value() * std::pow(base.value(), exponent.value() - 1);
  const double df_exp =
      std::pow(base.value(), exponent.value()) * std::log(base.value());

  return {{{base, df_base}, {exponent, df_exp}},
          std::pow(base.value(), exponent.value())};
}

auto exp(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::exp(rhs.value());
  const double df_rhs = value;

  return {{{rhs, df_rhs}}, value};
}

auto ln(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::log(rhs.value());
  const double df_rhs = 1.0 / rhs.value();

  return {{{rhs, df_rhs}}, value};
}

// auto log(const Symbol &argument, const Symbol &base) -> Symbol {
//   double x{std::log(argument.value())}, y{std::log(base.value())};
//   const double value = x/y;
//   // double df_argument = 1.0/ y * ;
//   double df_base;
// }

auto sin(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::sin(rhs.value());
  const double df_rhs = std::cos(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto cos(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::cos(rhs.value());
  const double df_rhs = -std::sin(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto tan(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::tan(rhs.value());
  const double df_rhs = 1.0 / std::pow(std::cos(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

auto cot(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::tan(rhs.value());
  const double df_rhs = -1.0 / std::pow(std::sin(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

auto sec(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::cos(rhs.value());
  const double df_rhs = value * std::tan(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto csc(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::sin(rhs.value());
  const double df_rhs = value * (-1.0 / std::tan(rhs.value()));
  return {{{rhs, df_rhs}}, value};
}

auto sinh(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::sinh(rhs.value());
  const double df_rhs = std::cosh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto cosh(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::cosh(rhs.value());
  const double df_rhs = std::sinh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto tanh(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::tanh(rhs.value());
  const double df_rhs = 1.0 / std::pow(std::cosh(rhs.value()), 2); // cont ..
  return {{{rhs, df_rhs}}, value};
}

auto coth(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::tanh(rhs.value());
  const double df_rhs = -1.0 / std::pow(std::sinh(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

auto sech(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::cosh(rhs.value());
  const double df_rhs = -value * std::tanh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto csch(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::sinh(rhs.value());
  const double df_rhs = value * (-1.0 / std::tanh(rhs.value()));
  return {{{rhs, df_rhs}}, value};
}

auto asin(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::asin(rhs.value());
  const double df_rhs = 1.0 / std::sqrt(1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto acos(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::acos(rhs.value());
  const double df_rhs = -1.0 / std::sqrt(1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto atan(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::atan(rhs.value());
  const double df_rhs = 1.0 / (1 + std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto acot(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::atan(rhs.value());
  const double df_rhs = -1.0 / (1 + std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto asec(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::acos(rhs.value());
  const double df_rhs = 1.0 / (std::pow(rhs.value(), 2) *
                               std::sqrt(1 - 1.0 / std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto acsc(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::asin(rhs.value());
  const double df_rhs = 1.0 / (std::pow(rhs.value(), 2) *
                               std::sqrt(1 - 1.0 / std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto asinh(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::asinh(rhs.value());
  const double df_rhs = 1.0 / std::sqrt(std::pow(rhs.value(), 2) + 1);
  return {{{rhs, df_rhs}}, value};
}

auto acosh(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::acosh(rhs.value());
  const double df_rhs = -1.0 / std::sqrt(std::pow(rhs.value(), 2) - 1);
  return {{{rhs, df_rhs}}, value};
}

auto atanh(const Symbol &rhs) noexcept -> Symbol {
  const double value = std::atanh(rhs.value());
  const double df_rhs = 1.0 / (1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto acoth(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::atanh(rhs.value());
  const double df_rhs = -1.0 / (1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto asech(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::acosh(rhs.value());
  const double df_rhs =
      -1.0 / (rhs.value() * std::sqrt(1 - std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto acsch(const Symbol &rhs) noexcept -> Symbol {
  const double value = 1.0 / std::asinh(rhs.value());
  const double df_rhs =
      -1.0 / (std::abs(rhs.value()) * std::sqrt(1 + std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto gradient(const Symbol &variable) -> std::map<Symbol, double> {
  std::map<Symbol, double> _gradients{};

  std::function<auto(const Symbol &, double)->void> _compute_gradient =
      [&_compute_gradient, &_gradients](const Symbol &variable,
                                        double path_value) {
        double value_of_path_to_child{};
        // std::cout << "outer: " << path_value << '\n';

        for (auto &[child, local_gradient] : variable.local_gradient()) {
          value_of_path_to_child = path_value * local_gradient;
          _gradients[child] += value_of_path_to_child;

          _compute_gradient(child, value_of_path_to_child);
        }
      };

  _compute_gradient(variable, 1);

  return _gradients;
}

} // namespace ad
