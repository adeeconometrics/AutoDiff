#include "../include/fsymbol.hpp"

#include <cmath>
#include <functional>

namespace ad {

FSym::FSym(double t_value, double t_dot) : m_value(t_value), m_dot(t_dot){};
FSym::FSym(double t_value) : m_value(t_value), m_dot(1.0f){};

auto FSym::value() const noexcept -> double { return m_value; }
auto FSym::dot() const noexcept -> double { return m_dot; }
auto FSym::df(int t_index) const noexcept -> double {
  return t_index == 0 ? m_dot : 0.0;
}

auto FSym::operator<(const FSym &other) const noexcept -> bool {
  return m_value < other.m_value;
}
auto FSym::operator>(const FSym &other) const noexcept -> bool {
  return m_value > other.m_value;
}
auto FSym::operator==(const FSym &other) const noexcept -> bool {
  return m_value == other.m_value;
}
auto FSym::operator!=(const FSym &other) const noexcept -> bool {
  return m_value != other.m_value;
}

auto operator+(const FSym &lhs, const FSym &rhs) -> FSym {
  return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()};
}

auto operator-(const FSym &lhs, const FSym &rhs) -> FSym {
  return {lhs.value() - rhs.value(), lhs.dot() - rhs.dot()};
}

auto operator*(const FSym &lhs, const FSym &rhs) -> FSym {
  return {lhs.value() * rhs.value(),
          lhs.dot() * rhs.value() + rhs.dot() * lhs.value()};
}

auto operator/(const FSym &lhs, const FSym &rhs) -> FSym {
  const double df = {(rhs.value() * lhs.dot() - lhs.value() * rhs.dot()) /
                     std::pow(rhs.value(), 2)};
  return {lhs.value() / rhs.value(), df};
}

} // namespace ad
