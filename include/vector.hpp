#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>

using std::vector;

namespace ad {

template <typename T>
constexpr auto operator==(const vector<T> &lhs, const vector<T> &rhs) -> bool {
  if (lhs.size() != rhs.size())
    return false;
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T>
constexpr auto operator!=(const vector<T> &lhs, const vector<T> &rhs) -> bool {
  return !(lhs == rhs);
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator+(const vector<T> &lhs, const vector<T> &rhs)
    -> vector<T> {

  assert(lhs.size() == rhs.size());

  vector<T> result;
  result.reserve(lhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](T a, T b) -> T { return a + b; });
  return result;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator-(const vector<T> &lhs, const vector<T> &rhs)
    -> vector<T> {
  assert(lhs.size() == rhs.size());

  vector<T> result;
  result.reserve(lhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](T a, T b) -> T { return a - b; });
  return result;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator*(const vector<T> &lhs, const vector<T> &rhs)
    -> vector<T> {
  assert(lhs.size() == rhs.size());

  vector<T> result;
  result.reserve(lhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](T a, T b) -> T { return a * b; });
  return result;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator/(const vector<T> &lhs, const vector<T> &rhs)
    -> vector<T> {
  assert(lhs.size() == rhs.size());

  vector<T> result;
  result.reserve(lhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](T a, T b) -> T { return a / b; });
  return result;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator+=(vector<T> &lhs, const vector<T> &rhs) -> vector<T> & {
  assert(lhs.size() == rhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(lhs), [](T _lhs, T _rhs) { return _lhs += _rhs; });
  return lhs;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator-=(vector<T> &lhs, const vector<T> &rhs) -> vector<T> & {
  assert(lhs.size() == rhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(lhs), [](T _lhs, T _rhs) { return _lhs -= _rhs; });
  return lhs;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator*=(vector<T> &lhs, const vector<T> &rhs) -> vector<T> & {
  assert(lhs.size() == rhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(lhs), [](T _lhs, T _rhs) { return _lhs *= _rhs; });
  return lhs;
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator/=(vector<T> &lhs, const vector<T> &rhs) -> vector<T> & {
  assert(lhs.size() == rhs.size());

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(lhs), [](T _lhs, T _rhs) { return _lhs /= _rhs; });
  return lhs;
}

} // namespace ad

#endif // __VECTOR_H__