/**
 * @file Symbol.h
 * @author ddamiana
 * @brief Root class for forward_mode and reverse_mode
 * @version 0.1
 * @date 2022-05-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __SYMBOL_H__
#define __SYMBOL_H__

// todo:
// remove obsolete methods!

#include <type_traits>
#include <functional>
#include <concepts>
#include <list>
#include <set>

namespace ad {
class Symbol {
private:
  
  std::function<void(void)> m_backward;
  std::list<Symbol> m_children{};
  std::set<Symbol> m_prev;

  float m_val{};
  float m_grad{};

public:
  Symbol(float _value) : m_val(_value) {}
  Symbol(float _value, const std::list<Symbol> &_children): 
        m_children(_children), 
        m_prev(_children.cbegin(), _children.cend()),
        m_val(_value) {}

  Symbol() = default;
  ~Symbol() = default;

  // auto operator=(const Symbol& lhs) -> Symbol& = default;
  // auto operator=(Symbol&& rhs) -> Symbol& = default;

  auto operator+(const Symbol& rhs) const noexcept -> Symbol;
  auto operator-(const Symbol &rhs) const noexcept -> Symbol;
  auto operator/(const Symbol &rhs) const noexcept -> Symbol;
  auto operator*(const Symbol &rhs) const noexcept -> Symbol;

  const auto value(void) const noexcept -> float;
  const auto gradient(void) const noexcept -> float; 

private:
  auto backward(void) -> void;
  // auto build_topology(std::list<Symbol>& _topology,
  //   std::set<Symbol>& _visited,
  //   Symbol &_node) const noexcept -> void;
};

template <typename T>
concept SymbolLike = std::is_arithmetic_v<T> || std::is_base_of_v<Symbol, T>;

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator+(const T& lhs, const U &rhs) -> Symbol;


template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator-(const T& lhs, const U &rhs) -> Symbol;

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator*(const T& lhs, const U &rhs) -> Symbol;

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto operator/(const T& lhs, const U &rhs) -> Symbol;

auto operator<(const Symbol& lhs, const Symbol& rhs) -> bool;
auto operator>(const Symbol &lhs, const Symbol &rhs) -> bool;
auto operator==(const Symbol &lhs, const Symbol &rhs) -> bool;
auto operator!=(const Symbol &lhs, const Symbol &rhs) -> bool;

} // namespace ad

#endif // __SYMBOL_H__
