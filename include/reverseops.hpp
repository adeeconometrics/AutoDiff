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

// template <typename T,
//           typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
// constexpr auto ln(const RSym<T> &rhs) noexcept -> RSym<T> {
//   const T value = std::log(rhs.value());
//   const T df_rhs = 1.0 / rhs.value();

//   return {{{rhs, df_rhs}}, value};
// }

#endif // __REVERSEOPS_H__