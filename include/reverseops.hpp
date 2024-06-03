#ifndef __REVERSEOPS_H__
#define __REVERSEOPS_H__

#include "../include/rsymbol.hpp"

#include <cmath>
#include <type_traits>

using ad::RSym;

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto pow(const RSym<T> &base, const RSym<T> &exponent) -> RSym<T> {
  const T df_base =
      exponent.value() * std::pow(base.value(), exponent.value() - 1);
  const T df_exp =
      std::pow(base.value(), exponent.value()) * std::log(base.value());

  return {{{base, df_base}, {exponent, df_exp}},
          std::pow(base.value(), exponent.value())};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto pow(const RSym<T> &base, T exponent) -> RSym<T> {
  const T df_base = exponent * std::pow(base.value(), exponent - 1);

  return {{{base, df_base}}, std::pow(base.value(), exponent)};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto exp(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = std::exp(rhs.value());
  const T df_rhs = value;

  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto ln(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = std::log(rhs.value());
  const T df_rhs = 1.0 / rhs.value();

  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto sin(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = std::sin(rhs.value());
  const T df_rhs = std::cos(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto cos(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = std::cos(rhs.value());
  const T df_rhs = -std::sin(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto tan(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = std::tan(rhs.value());
  const T df_rhs = 1.0 / std::pow(std::cos(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto cot(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = 1.0 / std::tan(rhs.value());
  const T df_rhs = -1.0 / std::pow(std::sin(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto sec(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = 1.0 / std::cos(rhs.value());
  const T df_rhs = value * std::tan(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto csc(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = 1.0 / std::sin(rhs.value());
  const T df_rhs = value * (-1.0 / std::tan(rhs.value()));
  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto sinh(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = std::sinh(rhs.value());
  const T df_rhs = std::cosh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto cosh(const RSym<T> &rhs) noexcept -> RSym<T> {
  const T value = std::cosh(rhs.value());
  const T df_rhs = std::sinh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

// template <typename T,
//           typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
// constexpr auto tanh(const RSym<T> &rhs) noexcept -> RSym<T> {
//   const T value = std::tanh(rhs.value());
//   const T df_rhs = 1.0 / std::pow(std::cosh(rhs.value()), 2); // cont ..
//   return {{{rhs, df_rhs}}, value};
// }

// template <typename T,
//           typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
// constexpr auto coth(const RSym<T> &rhs) noexcept -> RSym<T> {
//   const T value = 1.0 / std::tanh(rhs.value());
//   const T df_rhs = -1.0 / std::pow(std::sinh(rhs.value()), 2);
//   return {{{rhs, df_rhs}}, value};
// }

// template <typename T,
//           typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
// constexpr auto sech(const RSym<T> &rhs) noexcept -> RSym<T> {
//   const T value = 1.0 / std::cosh(rhs.value());
//   const T df_rhs = -value * std::tanh(rhs.value());
//   return {{{rhs, df_rhs}}, value};
// }

// template <typename T,
//           typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
// constexpr auto csch(const RSym<T> &rhs) noexcept -> RSym<T> {
//   const T value = 1.0 / std::sinh(rhs.value());
//   const T df_rhs = value * (-1.0 / std::tanh(rhs.value()));
//   return {{{rhs, df_rhs}}, value};
// }

#endif // __REVERSEOPS_H__