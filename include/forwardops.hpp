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

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto tan(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::tan(rhs.value());
  const T df = (1.0f / std::pow(std::cos(rhs.value()), 2)) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto cot(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = 1.0f / std::tan(rhs.value());
  const T df = -(1.0f / std::pow(std::sin(rhs.value()), 2)) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto sec(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = 1.0f / std::cos(rhs.value());
  const T df = std::tan(rhs.value()) * value * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto csc(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = 1.0f / std::sin(rhs.value());
  const T df = -value * (1.0f / std::tan(rhs.value())) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto sinh(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::sinh(rhs.value());
  const T df = std::cosh(rhs.value()) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto cosh(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::cosh(rhs.value());
  const T df = std::sinh(rhs.value()) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto tanh(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::tanh(rhs.value());
  const T df = std::pow(1.0f / std::cosh(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto coth(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = 1.0f / std::tanh(rhs.value());
  const T df = -std::pow(1.0f / std::sinh(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto sech(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = 1.0f / std::cosh(rhs.value());
  const T df = -std::tanh(rhs.value()) / std::cosh(rhs.value()) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto csch(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = 1.0f / std::sinh(rhs.value());
  const T df = -value * (1.0f / std::tanh(rhs.value())) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto asin(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::asin(rhs.value());
  const T df = 1.0f / std::sqrt(1.0f - std::pow(rhs.value(), 2)) * rhs.dot();
  return {value, df};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
constexpr auto acos(const FSym<T> &rhs) noexcept -> FSym<T> {
  const T value = std::acos(rhs.value());
  const T df = -1.0f / std::sqrt(1.0f - std::pow(rhs.value(), 2)) * rhs.dot();
  return {value, df};
}

#endif // __FORWARDOPS_H__