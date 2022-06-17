/**
 * @file Function.h
 * @author ddamiana
 * @brief contains base functions for scalar and vector-valued functions
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "Utils.h"

#include <algorithm>
#include <cmath>
#include <concepts>
#include <type_traits>

/**
 * todo
 * - proper return type for trig operation; it should handle type promotion for
 * integral types or only allow is_floating_point
 * - decide is inline function definitions are better
 * - assert for equal size on element-wise operations
 */

namespace ad {

template <typename T>
requires AbstractNumericVector<T>
auto operator+(const T &t1, const T &t1) -> T {
  T result;
  std::transform(t1.cbegin(), t1.cend(), t2.cbegin(),
                 std::back_inserter(result), std::plus<>());
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto operator-(const T &t1, const T &t1) -> T {
  T result;
  std::transform(t1.cbegin(), t1.cend(), t2.cbegin(),
                 std::back_inserter(result), std::minus<>());
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto operator*(const T &t1, const T &t1) -> T {
  T result;
  std::transform(t1.cbegin(), t1.cend(), t2.cbegin(),
                 std::back_inserter(result), std::multiplies<>());
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto operator/(const T &t1, const T &t1) -> T {
  T result;
  std::transform(t1.cbegin(), t1.cend(), t2.cbegin(),
                 std::back_inserter(result), std::divides<>());
  return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator+(const T &t, U u) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(i + u); });
  return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator-(const T &t, U u) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(i - u); });
  return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator*(const T &t, U u) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(i * u); });
  return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator/(const T &t, U u) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(i / u); });
  return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator+(U u, const T &t) -> T { return t + u; }

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator-(U u, const T &t) -> T { return t - u; }

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator*(U u, const T &t) -> T { return t * u; }

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator/(U u, const T &t) -> T { return t / u; }

template <typename T>
requires AbstractNumericVector<T>
auto abs(const T &rhs) -> T {
  T result;
  std::for_each(rhs.cbegin(), rhs.cend(), [&result](const auto i) -> void {
    result.push_back(std::abs(i));
  });
  return result;
}

// consider adding element-wise pow*
template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto pow(const T &base, U exp) -> T {
  T result;
  std::for_each(base.cbegin(), base.cend(), [&exp, &result](auto i) -> void {
    result.push_back(std::pow(i, exp));
  });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto sqrt(const T &rhs) -> T {
  T result;
  std::for_each(rhs.cbegin(), rhs.cend(), [&result](const auto i) -> void {
    result.push_back(std::sqrt(i));
  });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto ln(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::log(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto exp(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::exp(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto sin(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::sin(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto cos(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::cos(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto tan(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::tan(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto cot(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
    result.push_back(1 / std::tan(i));
  });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto sec(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
    result.push_back(1 / std::cos(i));
  });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto csc(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
    result.push_back(1 / std::sin(i));
  });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto sinh(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::sinh(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto cosh(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::cosh(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto tanh(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::tanh(i)); });
  return result;
}

// template <typename T>
// requires AbstractNumericVector<T>
// auto coth(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::tanh(i));
//   });
//   return result;
// }

// template <typename T>
// requires AbstractNumericVector<T>
// auto sech(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::cosh(i));
//   });
//   return result;
// }

// template <typename T>
// requires AbstractNumericVector<T>
// auto csch(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::sinh(i));
//   });
//   return result;
// }

template <typename T>
requires AbstractNumericVector<T>
auto asin(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::asin(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto acos(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::acos(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto atan(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::atan(i)); });
  return result;
}

// template <typename T>
// requires AbstractNumericVector<T>
// auto acot(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::atan(i));
//   });
//   return result;
// }

// template <typename T>
// requires AbstractNumericVector<T>
// auto asec(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::acos(i));
//   });
//   return result;
// }

// template <typename T>
// requires AbstractNumericVector<T>
// auto acsc(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::asin(i));
//   });
//   return result;
// }

template <typename T>
requires AbstractNumericVector<T>
auto asinh(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::asinh(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto acosh(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::acosh(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto atanh(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::atanh(i)); });
  return result;
}

// template <typename T>
// requires AbstractNumericVector<T>
// auto acoth(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::atanh(i));
//   });
//   return result;
// }

// template <typename T>
// requires AbstractNumericVector<T>
// auto asech(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::acosh(i));
//   });
//   return result;
// }

// template <typename T>
// requires AbstractNumericVector<T>
// auto acsch(const T &t) -> T {
//   T result;
//   std::for_each(t.cbegin(), t.cend(), [&result](auto i) -> void {
//     result.push_back(1.0 / std::asinh(i));
//   });
//   return result;
// }

} // namespace ad

#endif // __FUNCTION_H__
