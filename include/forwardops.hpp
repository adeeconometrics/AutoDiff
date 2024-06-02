#ifndef __FORWARDOPS_H__
#define __FORWARDOPS_H__

#include "../include/fsymbol.hpp"

#include <cmath>
#include <type_traits>

using ad::FSym;

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto pow(const FSym<T> &base, const FSym<T> &exp) -> FSym<T> {
  const T df_base =
      std::log(base.value()) * std::pow(base.value(), exp.value()) * exp.dot();
  return {std::pow(base.value(), exp.value()), df_base};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto pow(const FSym<T> &base, T exp) -> FSym<T> {
  const T df_base = exp * std::pow(base.value(), exp - 1);
  return {std::pow(base.value(), exp), df_base};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto exp(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::exp(rhs.value());
  const T df = value * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto ln(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::log(rhs.value());
  const T df = (1.0f / rhs.value()) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto sin(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::sin(rhs.value());
  const T df = std::cos(rhs.value()) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto cos(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::cos(rhs.value());
  const T df = -std::sin(rhs.value()) * rhs.dot();
  return {value, df};
}

#endif // __FORWARDOPS_H__