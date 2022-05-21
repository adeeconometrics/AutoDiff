#ifndef __SYMBOL_H__
#define __SYMBOL_H__

/**
 * @file Symbol.h
 * @author ddamiana
 * @brief contains declarations for forward-pass autodiff
 * @version 0.1
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <type_traits>

namespace ad {
  class Symbol {
  private:
    float val{};
    float grad{};

  public:
    Symbol(float _value, float _grad) : val(_val), grad(_grad) {}

    Symbol() = default;
    ~Symbol() = default;

    auto operator+(const Symbol &other) -> Symbol;
    auto operator-(const Symbol &other) -> Symbol;
    auto operator*(const Symbol &other) -> Symbol;
    auto operator/(const Symbol &other) -> Symbol;

    auto operator+=(const Symbol &other) -> Symbol;
    auto operator-=(const Symbol &other) -> Symbol;
    auto operator*=(const Symbol &other) -> Symbol;
    auto operator/=(const Symbol &other) -> Symbol;
  }

  template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
                                                  std::is_same_v<T, Symbol>>>
  auto pow(const Symbol &lhs, const T &rhs) -> Symbol;

  template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
                                                  std::is_same_v<T, Symbol>>>
  auto exp(const T& rhs) -> Symbol;

  template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
                                                  std::is_same_v<T, Symbol>>>
  auto log10(const T &rhs) -> Symbol;

  template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
                                                  std::is_same_v<T, Symbol>>>
  auto log2(const T &rhs) -> Symbol;

  template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
                                                  std::is_same_v<T, Symbol>>>
  auto ln(const T &rhs) -> Symbol;

  auto sin(const Symbol &rhs)->Symbol;
  auto cos(const Symbol &rhs)->Symbol;
  auto tan(const Symbol &rhs)->Symbol;
  auto sinh(const Symbol &rhs)->Symbol;
  auto cosh(const Symbol &rhs)->Symbol;
  auto tanh(const Symbol &rhs)->Symbol;

}

#endif // __SYMBOL_H__