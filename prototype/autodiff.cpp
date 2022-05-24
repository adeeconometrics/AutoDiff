#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>

namespace ad {

class Symbol {
private:
  std::map<Symbol, long double> m_local_gradient;
  long double m_value{};

public:
  Symbol(const std::map<Symbol, long double> &_local_gradient, long double _value)
      : m_local_gradient(_local_gradient), m_value(_value) {}

  Symbol(long double _value) : m_value(_value) {}

  auto value() const noexcept -> long double { return m_value; }

  auto local_gradient() const noexcept -> std::map<Symbol, long double> {
    return m_local_gradient;
  }

  auto operator<(const Symbol &rhs) const -> bool {
    return m_value < rhs.m_value;
  }

  auto operator>(const Symbol &rhs) const -> bool {
    return m_value > rhs.m_value;
  }

  auto operator==(const Symbol &rhs) const -> bool {
    return m_value == rhs.m_value;
  }

  auto operator!=(const Symbol &rhs) const -> bool {
    return m_value != rhs.m_value;
  }
};

auto operator+(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {
    _local_gradient : {{lhs, 1.0}, {rhs, 1.0}},
    _value : lhs.value() + rhs.value()
  };
}

auto operator-(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {
    _local_gradient : {{lhs, 1.0}, {rhs, 1.0}},
    _value : lhs.value() - rhs.value()
  };
}

auto operator*(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {
    _local_gradient : {{lhs, rhs.value()}, {rhs, lhs.value()}},
    _value : lhs.value() * rhs.value()
  };
}

auto operator/(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  Symbol inverse{
    _local_gradient : {{rhs, -1.0 / std::pow(rhs.value(), 2)}},
    _value : 1.0 / rhs.value()
  };

  return lhs * inverse;
}

auto gradient(const Symbol &variable) -> std::map<Symbol, long double> {
  std::map<Symbol, long double> _gradients{};

  std::function<void(const Symbol &, long double)> _compute_gradient =
      [&_compute_gradient, &_gradients](const Symbol &variable,
                                        long double path_value) {
        long double value_of_path_to_child{};
        for (const auto &[child, local_gradient] : variable.local_gradient()) {
          value_of_path_to_child = path_value * local_gradient;

          std::cout << std::setprecision(20) << _gradients[child] << '\n';

          _gradients[child] += value_of_path_to_child;
          _compute_gradient(child, value_of_path_to_child);
        }
      };

  _compute_gradient(variable, 1);

  return _gradients;
}

} // namespace ad

auto main(void) -> int {
  using namespace ad;

  //   auto a = Symbol(4.0f);
  //   auto b = Symbol(3.0f);
  //   auto c = a + b;
  //   auto d = a * c;

  //   auto df = gradient(d);
  //   std::cout << d.value() << '\n';
  //   std::cout << df[a] << '\n';
  //   std::cout << df[b] << '\n';
  Symbol a{230.3};
  Symbol b{33.2};

  auto y = (a / b - a) * (b / a + a + b) * (a - b);
  auto df = gradient(y);

  std::cout << "d value: " << std::setprecision(20) << y.value() << '\n';
//   std::cout << "df/da: " << std::setprecision(20) << df[a] << '\n';
//   std::cout << "df/db: " << std::setprecision(20) << df[b] << '\n';
    for(auto i: df)
        std::cout << std::setprecision(20) << i.second << '\n';
}