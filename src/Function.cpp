#include "Function.h"

#include <type_traits>
#include <algorithm>
#include <concepts>
#include <cmath>

namespace ad{

template <typename T>
requires AbstractNumericVector<T>
auto operator+(const T &t1, const T &t1) -> T { 
    T result; 
    std::transform(t1.cbegin(), t1.cend(), t2.cbegin(),
        std::back_inserter(result), std::plus<>()
    );
    return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto operator-(const T &t1, const T &t1) -> T{
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
auto operator+(const T &t, U u) -> T{
    T result;
    std::for_each(t.cbegin(), t.cend(),
        [&result](auto i) -> void {result.push_back(i + u); }
    );
    return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator-(const T &t, U u) -> T{
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(i - u); });
  return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator*(const T &t, U u) -> T{
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(i * u); });
  return result;
}

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator/(const T &t, U u) -> T{
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(i / u); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto sin(const T &t) -> T{
    T result;
    std::for_each(t.cbegin(), t.cend(),
        [&result](auto i) -> void {result.push_back(std::sin(i));}
    );
    return result; 
}

template <typename T>
requires AbstractNumericVector<T>
auto cos(const T &t) -> T{
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::cos(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto tan(const T &t) -> T{
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(std::tan(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto cot(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(1/std::tan(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto sec(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(1/std::cos(i)); });
  return result;
}

template <typename T>
requires AbstractNumericVector<T>
auto csc(const T &t) -> T {
  T result;
  std::for_each(t.cbegin(), t.cend(),
                [&result](auto i) -> void { result.push_back(1/std::sin(i)); });
  return result;
}

} // namespace ad

