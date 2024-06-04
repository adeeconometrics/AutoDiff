#ifndef __RSYMBOL_H__
#define __RSYMBOL_H__

#include <functional>
#include <map>
#include <type_traits>

namespace ad {

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
struct RSym {
public:
  RSym(const std::map<RSym, T> &t_loc_grad, T t_value)
      : m_local_grad(t_loc_grad), m_value(t_value) {}
  RSym(T t_value) : m_value(t_value) {}

  auto value() const noexcept -> T { return m_value; }

  auto local_gradient() const noexcept -> std::map<RSym, T> {
    return m_local_grad;
  }

  auto operator<(const RSym &other) const noexcept -> bool {
    return m_value < other.m_value;
  }

  auto operator>(const RSym &other) const noexcept -> bool {
    return m_value > other.m_value;
  }
  auto operator==(const RSym &other) const noexcept -> bool {
    return m_value == other.m_value;
  }

  auto operator!=(const RSym &other) const noexcept -> bool {
    return m_value != other.m_value;
  }

private:
  std::map<RSym, T> m_local_grad;
  T m_value;
};

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator+(const RSym<T> &lhs, const RSym<T> &rhs) -> RSym<T> {
  return {{{lhs, 1.0}, {rhs, 1.0}}, lhs.value() + rhs.value()};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator-(const RSym<T> &lhs, const RSym<T> &rhs) -> RSym<T> {
  return {{{lhs, 1.0}, {rhs, -1.0}}, lhs.value() - rhs.value()};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator*(const RSym<T> &lhs, const RSym<T> &rhs) -> RSym<T> {
  return {{{lhs, rhs.value()}, {rhs, lhs.value()}}, lhs.value() * rhs.value()};
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto operator/(const RSym<T> &lhs, const RSym<T> &rhs) -> RSym<T> {
  const RSym<T> inverse{{{rhs, -1.0 / std::pow(rhs.value(), 2)}},
                        1.0 / rhs.value()};
  return lhs * inverse;
}

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
auto gradient(const RSym<T> &variable) -> std::map<RSym<T>, T> {
  std::map<RSym<T>, T> _gradients{};

  std::function<auto(const RSym<T> &, T)->void> _compute_gradient =
      [&_compute_gradient, &_gradients](const RSym<T> &variable, T path_value) {
        T value_of_path_to_child{};

        for (auto &[child, local_gradient] : variable.local_gradient()) {
          value_of_path_to_child = path_value * local_gradient;
          _gradients[child] += value_of_path_to_child;

          _compute_gradient(child, value_of_path_to_child);
        }
      };

  _compute_gradient(variable, 1);

  return _gradients;
}

}; // namespace ad

#endif // __RSYMBOL_H__