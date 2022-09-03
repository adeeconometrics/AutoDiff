#include "../include/Symbol.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <list>
#include <set>
#include <type_traits>

namespace ad {

auto Symbol::operator+(const Symbol &rhs) const noexcept -> Symbol {
  return *this + rhs;
}

auto Symbol::operator-(const Symbol &rhs) const noexcept -> Symbol {
  return *this - rhs;
}

auto Symbol::operator*(const Symbol &rhs) const noexcept -> Symbol {
  return (*this) * rhs;
}

auto Symbol::operator/(const Symbol &rhs) const noexcept -> Symbol {
  return *(this) / rhs;
}

const auto Symbol::value(void) const noexcept -> float { return m_val; }

const auto Symbol::gradient(void) const noexcept -> float { return m_grad; }

auto Symbol::backward(void) -> void {
  std::list<Symbol> _topology{};
  std::set<Symbol> _visited{};

  std::function<auto(const Symbol &)->void> build_topology =
      [&build_topology, &_topology, &_visited](const Symbol &_node) -> void {
    if (!std::any_of(_visited.cbegin(), _visited.cend(),
                     [&_node](const auto i) -> bool { return i == _node; })) {
      _visited.insert(_node);
      for (auto child : _node.m_prev) {
        build_topology(child);
      }

      _topology.push_back(_node);
    }
  };

  build_topology(*this);

  this->m_grad = 1.0;
  std::reverse(_topology.begin(), _topology.end());
  for (auto v : _topology) {
    v.m_backward();
  }
}

// auto Symbol::build_topology(std::list<Symbol> &_topology,
//                             std::set<Symbol> &_visited,
//                             Symbol &_node) const noexcept -> void {
//   if (!std::any_of(_visited.cbegin(), _visited.cend(), [&_node](const auto i)
//   -> bool {return i == _node;})) {
//     _visited.insert(_node);
//     for (auto child : _node.m_prev) {
//       build_topology(_topology, _visited, child);
//     }

//     _topology.push_back(_node);
//   }
// }

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator+(T &lhs, const U &rhs) -> Symbol {
  auto _rhs = std::is_same_v<U, Symbol> ? rhs : Symbol(rhs);
  auto _node = Symbol(lhs.m_value + rhs.m_value, {lhs, rhs});

  _node.m_backward = [&lhs, &_rhs, &_node]() -> void {
    lhs.m_grad = lhs.m_grad + _node.m_grad;
    _rhs.m_grad = _rhs.m_grad + _node.m_grad;
  };

  return _node;
}

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator-(T &lhs, const U &rhs) -> Symbol {
  auto _rhs = std::is_same_v<U, Symbol> ? rhs : Symbol(rhs);
  auto _node = Symbol(lhs.m_value + rhs.m_value, {lhs, rhs});

  _node.m_backward = [&lhs, &_rhs, &_node]() -> void {
    lhs.m_grad = lhs.m_grad - _node.m_grad;
    _rhs.m_grad = _rhs.m_grad - _node.m_grad;
  };

  return _node;
}

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator/(T &lhs, const U &rhs) -> Symbol {
  return pow(lhs * rhs, -1); // not sure if this works
}

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator*(T &lhs, const U &rhs) -> Symbol {
  auto _rhs = std::is_same_v<U, Symbol> ? rhs : Symbol(rhs);
  auto _node = Symbol(lhs.m_value + rhs.m_value, {lhs, rhs});

  _node.m_backward = [&lhs, &_rhs, &_node]() -> void {
    lhs.m_grad = lhs.m_grad + _rhs.m_grad * _node.m_grad;
    _rhs.m_grad = _rhs.m_grad + lhs.m_grad * _node.m_grad;
  };

  return _node;
}

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto pow(T &lhs, const U &rhs) -> Symbol {
  using std::pow;
  auto _node = Symbol(pow(lhs.m_value, rhs), {lhs});

  _node.m_backward = [&lhs, &rhs, &_node]() -> void {
    lhs.m_grad = lhs.m_grad + rhs * pow(lhs.m_grad, rhs - 1) * _node.m_grad;
  };

  return _node;
}
auto operator<(const Symbol &lhs, const Symbol &rhs) -> bool {
  return lhs.value() < rhs.value();
}

auto operator>(const Symbol &lhs, const Symbol &rhs) -> bool {
  return lhs.value() > rhs.value();
}

auto operator==(const Symbol &lhs, const Symbol &rhs) -> bool {
  return lhs.value() == rhs.value();
}

auto operator!=(const Symbol &lhs, const Symbol &rhs) -> bool {
  return lhs.value() != rhs.value();
}
} // namespace ad