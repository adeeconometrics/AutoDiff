#include "../include/rsymbol.hpp"

#include <cmath>
#include <functional>
#include <map>
#include <type_traits>

namespace ad {

RSym::RSym(const std::map<RSym, double> &t_loc_grad, double t_value)
    : m_local_grad(t_loc_grad), m_value(t_value) {}

RSym::RSym(double t_value) : m_value(t_value) {}

auto RSym::value() const noexcept -> double { return m_value; }

auto RSym::local_gradient() const noexcept -> std::map<RSym, double> {
  return m_local_grad;
}

auto RSym::operator<(const RSym &other) const noexcept -> bool {
  return m_value < other.m_value;
}

auto RSym::operator>(const RSym &other) const noexcept -> bool {
  return m_value > other.m_value;
}
auto RSym::operator==(const RSym &other) const noexcept -> bool {
  return m_value == other.m_value;
}

auto RSym::operator!=(const RSym &other) const noexcept -> bool {
  return m_value != other.m_value;
}

auto operator+(const RSym &lhs, const RSym &rhs) -> RSym {
  return {{{lhs, 1.0}, {rhs, 1.0}}, lhs.value() + rhs.value()};
}

auto operator-(const RSym &lhs, const RSym &rhs) -> RSym {
  return {{{lhs, 1.0}, {rhs, -1.0}}, lhs.value() - rhs.value()};
}

auto operator*(const RSym &lhs, const RSym &rhs) -> RSym {
  return {{{lhs, rhs.value()}, {rhs, lhs.value()}}, lhs.value() * rhs.value()};
}

auto operator/(const RSym &lhs, const RSym &rhs) -> RSym {
  const RSym inverse{{{rhs, -1.0 / std::pow(rhs.value(), 2)}},
                     1.0 / rhs.value()};
  return lhs * inverse;
}

auto gradient(const RSym &variable) -> std::map<RSym, double> {
  std::map<RSym, double> _gradients{};

  std::function<auto(const RSym &, double)->void> _compute_gradient =
      [&_compute_gradient, &_gradients](const RSym &variable,
                                        double path_value) {
        double value_of_path_to_child{};

        for (auto &[child, local_gradient] : variable.local_gradient()) {
          value_of_path_to_child = path_value * local_gradient;
          _gradients[child] += value_of_path_to_child;

          _compute_gradient(child, value_of_path_to_child);
        }
      };

  _compute_gradient(variable, 1);

  return _gradients;
}
} // namespace ad