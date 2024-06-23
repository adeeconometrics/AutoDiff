#ifndef __FSYMBOL_H__
#define __FSYMBOL_H__

#include "../include/matexpr.hpp"
#include "../include/matops.hpp"
#include "../include/matrix.hpp"

#include <cmath>
#include <type_traits>
#include <vector>

namespace ad {

template <typename Expr> struct FExpr {
public:
  FExpr(const Expr &t_expr) : m_content(t_expr) {}

  auto value() const noexcept -> Expr { return m_content; }

private:
  Expr m_content;
};

template <typename...> struct FSym;

/**
 * @brief Represents the forward mode operator for autodifferentiation. Note to
 * find partial derivative of a multivariable function, we need to seed the
 * `t_dot` value with 1.0 to express this e.g. df(x,y)/dx => FSym(x, 1.0),
 * df(x,y)/dy => FSym(y, 1.0).
 *
 * @tparam T
 * @tparam std::enable_if_t<std::is_floating_point_v<T>>
 */
template <typename T> struct FSym<T> {
public:
  FSym(T t_value, T t_dot) : m_value(t_value), m_dot(t_dot) {}
  FSym(T t_value) : m_value(t_value), m_dot(T{}) {}

  auto value() const noexcept -> T { return m_value; }
  auto dot() const noexcept -> T { return m_dot; }

private:
  T m_value;
  T m_dot;
};

template <typename T, std::size_t Rows, std::size_t Cols>
struct FSym<Matrix<T, Rows, Cols>> {
public:
  FSym(const Matrix<T, Rows, Cols> &t_mat, T t_dot)
      : m_value(FExpr<Matrix<T, Rows, Cols>>(t_mat)),
        m_dot(FExpr<decltype(t_mat * t_dot)>(t_mat * t_dot)) {}

  auto value() const noexcept -> decltype(auto) { return m_value.value(); }
  auto dot() const noexcept -> decltype(auto) { return m_dot.value(); }

private:
  FExpr<Matrix<T, Rows, Cols>> m_value;
  FExpr<decltype(std::declval<Matrix<T, Rows, Cols>>() * std::declval<T>())>
      m_dot;
};

template <typename LhsExpr, typename RhsExpr> struct FSym<LhsExpr, RhsExpr> {
public:
  FSym(LhsExpr t_value, RhsExpr t_dot)
      : m_value(FExpr<LhsExpr>(t_value)), m_dot(FExpr<RhsExpr>(t_dot)) {}

  auto value() const noexcept -> decltype(auto) { return m_value.value(); }
  auto dot() const noexcept -> decltype(auto) { return m_dot.value(); }

private:
  FExpr<LhsExpr> m_value;
  FExpr<RhsExpr> m_dot;
};

template <typename T> auto operator+(const FSym<T> &lhs, const FSym<T> &rhs) {
  const auto value = lhs.value() + rhs.value();
  const auto dot = lhs.dot() + rhs.dot();
  return FSym<decltype(value), decltype(dot)>{lhs.value() + rhs.value(),
                                              lhs.dot() + rhs.dot()};
}

// template <typename T, std::size_t Rows, std::size_t Cols>
// auto operator+(const FSym<Matrix<T, Rows, Cols>> &lhs,
//                const FSym<Matrix<T, Rows, Cols>> &rhs) {
//   const auto value = lhs.value() + rhs.value();
//   const auto dot = lhs.dot() + rhs.dot();
//   return FSym<decltype(value), decltype(dot)>{lhs.value() + rhs.value(),
//                                               lhs.dot() + rhs.dot()};
// }

template <typename T>
auto operator-(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  return {lhs.value() - rhs.value(), lhs.dot() - rhs.dot()};
}

template <typename T>
auto operator*(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  return {lhs.value() * rhs.value(),
          lhs.dot() * rhs.value() + rhs.dot() * lhs.value()};
}

template <typename T>
auto operator/(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  const T df = {(rhs.value() * lhs.dot() - lhs.value() * rhs.dot()) /
                std::pow(rhs.value(), 2)};
  return {lhs.value() / rhs.value(), df};
}

}; // namespace ad

#endif // __FSYMBOL_H__
