#include <functional>
#include <iostream>
#include <iomanip>
#include <map>

#include <list>
#include <utility>
#include <cmath>

namespace ad {

class Symbol {
private:
  std::list<std::pair<Symbol, double>> m_local_gradient;
  double m_value{};

public:
  Symbol(const std::list<std::pair<Symbol, double>> &_local_gradient, double _value)
      : m_local_gradient(_local_gradient), m_value(_value) {}

  Symbol(double _value) : m_value(_value) {}

  auto value() const noexcept -> double { return m_value; }

  auto local_gradient() const noexcept -> std::list<std::pair<Symbol, double>> {
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
    {{lhs, 1.0}, {rhs, 1.0}},
    lhs.value() + rhs.value()
  };
}

auto operator-(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {
    {{lhs, 1.0}, {rhs, -1.0}},
    lhs.value() - rhs.value()
  };
}

auto operator*(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  return {
    {{lhs, rhs.value()}, {rhs, lhs.value()}},
    lhs.value() * rhs.value()
  };
}

auto operator/(const Symbol &lhs, const Symbol &rhs) -> Symbol {
  Symbol inverse{
    {{rhs, -1.0 / std::pow(rhs.value(), 2)}},
    1.0 / rhs.value()
  };

  return lhs * inverse;
}

auto gradient(const Symbol &variable) -> std::map<Symbol, double> {
  std::map<Symbol, double> _gradients{};

  std::function<auto(const Symbol &, double) -> void> _compute_gradient =
      [&_compute_gradient, &_gradients](const Symbol &variable,
                                        double path_value) {
        double value_of_path_to_child{};
        std::cout << "outer: " << path_value << '\n';

        for (auto &[child, local_gradient] : variable.local_gradient()) {
          value_of_path_to_child = path_value * local_gradient;
          
          // _gradients.emplace(child, 0);

          // std::cout << std::setprecision(20)
          //           << "\t local_gradient: " << local_gradient << '\n';
          // std::cout << std::setprecision(20)
          //           << "\t path value: " << path_value<< '\n';
          // std::cout << std::setprecision(20)
          //           << "\t gradient before: " << _gradients[child] << '\n';

          _gradients[child] += value_of_path_to_child;
          // if(_gradients.contains(child)){
          //   _gradients.at(child) += value_of_path_to_child;
          // } else {
          //   _gradients[child] = value_of_path_to_child;
          // }

          // std::cout << std::setprecision(20)
          //           << "\t gradient after: " << _gradients[child] << '\n';

          _compute_gradient(child, value_of_path_to_child);
        }
      };

  _compute_gradient(variable, 1);

  return _gradients;
}

} // namespace ad

auto main(void) -> int {
  using namespace ad;

  // auto a = Symbol(4.0f);
  // auto b = Symbol(3.0f);
  // auto c = a + b;
  // auto d = a * c / a;

  // auto df = gradient(d);
  // std::cout << d.value() << '\n';
  // std::cout << df[a] << '\n';
  // std::cout << df[b] << '\n';

  Symbol a{230.3};
  Symbol b{33.2};

  auto y = (a / b - a) * (b / a + a + b) * (a - b);
  auto df = gradient(y);

  std::cout << "d value: " << std::setprecision(20) << y.value() << '\n';
  std::cout << "df/da: " << std::setprecision(20) << df[a] << '\n';
  std::cout << "df/db: " << std::setprecision(20) << df[b] << '\n';
    // for(auto i: df)
    //     std::cout << std::setprecision(20) << &i.first << '\t' << i.second << '\n';
}