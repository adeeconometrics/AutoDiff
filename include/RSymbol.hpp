/**
 * @file RSymbol.h
 * @author ddamiana
 * @brief contains methods for reverse_mode AD
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __RSYMBOL_H__
#define __RSYMBOL_H__

#include "Function.hpp"
#include "Utilities.hpp"

#include <cmath>
#include <concepts>
#include <map>
#include <type_traits>

namespace ad {
template <typename T>
requires OrderedRealVector<T> ||
    std::is_floating_point<T>::value class RSymbol {
private:
  std::map<RSymbol, T> m_local_gradient;
  T m_value{};

public:
  RSymbol(const std::map<RSymbol<T>, T> &_local_gradient, const T &_value)
      : m_local_gradient(_local_gradient), m_value(_value) {}

  RSymbol(const T &_val) : m_value(_val) {}

  auto value() const noexcept -> T { return m_value; }

  auto local_gradient() const noexcept -> std::map<RSymbol<T>, T> {
    return m_local_gradient;
  }

  auto operator<(const RSymbol<T> &rhs) const -> bool {
    return this->m_value < rhs.value();
  }

  auto operator>(const RSymbol<T> &rhs) const -> bool {
    return this->m_value > rhs.value();
  }

  auto operator==(const RSymbol<T> &rhs) const -> bool {
    return this->m_value == rhs.value();
  }

  auto operator!=(const RSymbol<T> &rhs) const -> bool {
    return this->m_value != rhs.value();
  }
};

// functions are problematic for vectorized input

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto operator+(const RSymbol<T> &lhs, const RSymbol<T> &rhs) -> RSymbol<T> {
  return {{{lhs, 1.0}, {rhs, 1.0}}, lhs.value() + rhs.value()};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto operator-(const RSymbol<T> &lhs, const RSymbol<T> &rhs) -> RSymbol<T> {
  {{{lhs, 1.0}, {rhs, -1.0}}, lhs.value() - rhs.value()};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto operator*(const RSymbol<T> &lhs, const RSymbol<T> &rhs) -> RSymbol<T> {
  {{{lhs, rhs.value()}, {rhs, lhs.value()}}, lhs.value() * rhs.value()};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto operator/(const RSymbol<T> &lhs, const RSymbol<T> &rhs) -> RSymbol<T> {
  const Symbol inverse{{{rhs, -1.0 / pow(rhs.value(), 2)}}, 1.0 / rhs.value()};
  return lhs * inverse;
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto pow(const RSymbol<T> &lhs, const RSymbol<T> &rhs) -> RSymbol<T> {
  const auto df_base =
      exponent.value() * pow(base.value(), exponent.value() - 1);
  const auto df_exp = pow(base.value(), exponent.value()) * log(base.value());

  return {{{base, df_base}, {exponent, df_exp}},
          pow(base.value(), exponent.value())};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto exp(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = exp(rhs.value());
  const auto df_rhs = value;

  return {{{rhs, df_rhs}}, value};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>;
auto ln(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = log(rhs.value());
  const auto df_rhs = 1.0 / rhs.value();

  return {{{rhs, df_rhs}}, value};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto sin(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = sin(rhs.value());
  const auto df_rhs = cos(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto cos(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = cos(rhs.value());
  const auto df_rhs = -1 * sin(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto tan(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = tan(rhs.value());
  const auto df_rhs = 1 / pow(cos(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto cot(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = 1 / tan(rhs.value());
  const auto df_rhs = -1 / pow(sin(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto sec(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = 1.0 / cos(rhs.value());
  const auto df_rhs = value * tan(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto csc(const RSymbol<T> &rhs) noexcept -> RSymbol<T> {
  const auto value = 1.0 / sin(rhs.value());
  const auto df_rhs = value * (-1.0 / tan(rhs.value()));
  return {{{rhs, df_rhs}}, value};
}

// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto sinh(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto cosh(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto tanh(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto coth(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto sech(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto csch(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;

// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto asin(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto acos(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto atan(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto acot(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto asec(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto acsc(const RSymbol<T>& rhs) noexcept -> RSymbol<T>;

// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto asinh(const RSymbol<T>&) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto acosh(const RSymbol<T>&) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto atanh(const RSymbol<T>&) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto acoth(const RSymbol<T>&) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto asech(const RSymbol<T>&) noexcept -> RSymbol<T>;
// template<typename T>
// requires OrderedRealVector <T> || std::is_floating_point_v<T>
// auto acsch(const RSymbol<T>&) noexcept -> RSymbol<T>;

template <typename T>
requires OrderedRealVector<T> || std::is_floating_point_v<T>
auto gradient(const RSymbol<T> &) -> std::map<RSymbol, T> {
  std::map<RSymbol, T> _gradients{};

  std::function<auto(const RSymbol &, double)->void> _compute_gradient =
      [&_compute_gradient, &_gradients](const RSymbol &variable,
                                        double path_value) {
        double value_of_path_to_child{};
        // std::cout << "outer: " << path_value << '\n';

        for (auto &[child, local_gradient] : variable.local_gradient()) {
          value_of_path_to_child = local_gradient * path_value;
          _gradients[child] += value_of_path_to_child;

          _compute_gradient(child, value_of_path_to_child);
        }
      };

  _compute_gradient(variable, 1);

  return _gradients;
}

} // namespace ad

#endif // __RSYMBOL_H__
