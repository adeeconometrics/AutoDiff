#ifndef __FSYMBOL_H__
#define __FSYMBOL_H__

#include "../include/matexpr.hpp"
#include "../include/matrix.hpp"

#include <cmath>
#include <type_traits>
#include <vector>

namespace ad {

/**
 * @brief Represents the forward mode operator for autodifferentiation. Note to
 * find partial derivative of a multivariable function, we need to seed the
 * `t_dot` value with 1.0 to express this e.g. df(x,y)/dx => FSym(x, 1.0),
 * df(x,y)/dy => FSym(y, 1.0).
 *
 * @tparam T
 * @tparam std::enable_if_t<std::is_floating_point_v<T>>
 */
template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
struct FSym {
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
  FSym(const Matrix<T, Rows, Cols> &t_value, const Matrix<T, Rows, Cols> &t_dot)
      : m_value(t_value), m_dot(t_dot) {}

  FSym(const Matrix<T, Rows, Cols> &t_value, T t_dot)
      : m_value(t_value),
        m_dot(Matrix<T, Rows, Cols>{std::vector<T>(Rows * Cols, t_dot)}) {}

  auto value() const noexcept -> Matrix<T, Rows, Cols> { return m_value; }
  auto dot() const noexcept -> Matrix<T, Rows, Cols> { return m_dot; }

private:
  Matrix<T, Rows, Cols> m_value;
  Matrix<T, Rows, Cols> m_dot;
};

template <typename Expr> struct FExpr {

  FExpr(const Expr &t_content) : content(t_content) {}

  auto value() const noexcept -> Expr { return content; }

private:
  Expr content;
};

template <typename Expr> struct FSym<FExpr<Expr>> {
public:
  FSym(const FSym<Expr> &t_value, const FSym<Expr> &t_dot)
      : m_value(t_value), m_dot(t_dot) {}

  FSym(const FSym<Expr> &t_value, Expr t_dot)
      : m_value(t_value), m_dot(FExpr<Expr>{t_dot}) {}

  auto value() const noexcept -> FSym<Expr> { return m_value; }
  auto dot() const noexcept -> FSym<Expr> { return m_dot; }

private:
  Expr m_value;
  Expr m_dot;
};

template <typename T>
auto operator+(const FSym<T> &lhs, const FSym<T> &rhs) -> FSym<T> {
  return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()};
}

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
                pow(rhs.value(), 2)};
  return {lhs.value() / rhs.value(), df};
}

}; // namespace ad

#endif // __FSYMBOL_H__
