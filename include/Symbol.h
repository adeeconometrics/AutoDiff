#ifndef __SYMBOL_H__
#define __SYMBOL_H__

/**
 * @file Symbol.h
 * @author ddamiana
 * @brief contains declarations for forward-pass autodiff
 * @version 0.1
 * @date 2022-05-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <type_traits>
#include <functional>
#include <concepts>
#include <list>
#include <set>


namespace ad {

template <typename T>
concept SymbolLike =
    requires std::is_arithmetic_v<T> || std::is_base_of_v<Symbol>;

class Symbol {
private:
  
  std::functional<void(void)> m_backward;
  std::list<Symbol> m_children{};
  std::set<Symbol> m_prev;

  float m_val{};
  float m_grad{};

public:
  Symbol(float _value) : m_val(_val) {}
  Symbol(float _value, const std::list<Symbol> &_children): 
        m_children(_children), 
        m_prev(_children.cbegin(), _children.cend()),
        m_val(_val) {}

  Symbol() = default;
  ~Symbol() = default;

private:
  auto backward(void) -> void;
}

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

template <typename T, typename U = T>
requires SymbolLike<T> && SymbolLike<U>
auto pow(const T &lhs, const U &rhs) -> Symbol;

// template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
//                                                 std::is_same_v<T, Symbol>>>
// auto pow(const Symbol &lhs, const T &rhs) -> Symbol;

// template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
//                                                 std::is_same_v<T, Symbol>>>
// auto exp(const T& rhs) -> Symbol;

// template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
//                                                 std::is_same_v<T, Symbol>>>
// auto log10(const T &rhs) -> Symbol;

// template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
//                                                 std::is_same_v<T, Symbol>>>
// auto log2(const T &rhs) -> Symbol;

// template <typename T, typename std::enable_if_v<std::is_arithmetic_v<T> ||
//                                                 std::is_same_v<T, Symbol>>>
// auto ln(const T &rhs) -> Symbol;

// auto sin(const Symbol &rhs)->Symbol;
// auto cos(const Symbol &rhs)->Symbol;
// auto tan(const Symbol &rhs)->Symbol;
// auto sinh(const Symbol &rhs)->Symbol;
// auto cosh(const Symbol &rhs)->Symbol;
// auto tanh(const Symbol &rhs)->Symbol;

} // namespace ad

#endif // __SYMBOL_H__