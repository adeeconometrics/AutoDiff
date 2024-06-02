#ifndef __FSYMBOL_H__
#define __FSYMBOL_H__

#include <cmath>
#include <type_traits>

namespace ad {

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
struct FSym {
public:
  FSym(T t_value, T t_dot) : m_value(t_value), m_dot(t_dot) {}
  FSym(T t_value) : m_value(t_value), m_dot(T{}) {}

  auto value() const noexcept -> T { return m_value; }
  auto dot() const noexcept -> T { return m_dot; }
  auto df(int t_index) const noexcept -> T {
    return t_index == 0 ? m_dot : T{};
  }

  auto operator<(const FSym &other) const noexcept -> bool {
    return m_value < other.m_value;
  }

  auto operator>(const FSym &other) const noexcept -> bool {
    return m_value > other.m_value;
  }
  auto operator==(const FSym &other) const noexcept -> bool {
    return m_value == other.m_value;
  }

  auto operator!=(const FSym &other) const noexcept -> bool {
    return m_value != other.m_value;
  }

private:
  T m_value;
  T m_dot;
};

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator+(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator-(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  return {lhs.value() - rhs.value(), lhs.dot() - rhs.dot()};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator*(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  return {lhs.value() * rhs.value(),
          lhs.dot() * rhs.value() + rhs.dot() * lhs.value()};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator/(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  const T df = {(rhs.value() * lhs.dot() - lhs.value() * rhs.dot()) /
                std::pow(rhs.value(), 2)};
  return {lhs.value() / rhs.value(), df};
}

}; // namespace ad

#endif // __FSYMBOL_H__
