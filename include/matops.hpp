#ifndef __MATOPS_H__
#define __MATOPS_H__

#include "../include/matexpr.hpp"
#include "../include/matrix.hpp"

#include <cmath>
#include <functional>
#include <type_traits>

namespace ad {

template <typename T, std::size_t Row, std::size_t Col>
constexpr auto operator==(const Matrix<T, Row, Col> &lhs,
                          const Matrix<T, Row, Col> &rhs) -> bool {
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr auto operator!=(const Matrix<T, Row, Col> &lhs,
                          const Matrix<T, Row, Col> &rhs) -> bool {
  return !(lhs == rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator+(const Lhs &lhs,
                         const Rhs &rhs) -> BinaryExpr<std::plus<>, Lhs, Rhs> {
  return BinaryExpr<std::plus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator-(const Lhs &lhs,
                         const Rhs &rhs) -> BinaryExpr<std::minus<>, Lhs, Rhs> {
  return BinaryExpr<std::minus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator*(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::multiplies<>, Lhs, Rhs> {
  return BinaryExpr<std::multiplies<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator/(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::divides<>, Lhs, Rhs> {
  return BinaryExpr<std::divides<>, Lhs, Rhs>(lhs, rhs);
}
// matmul unary: matmul(Expr(A), B) | matmul(A, Expr(B))
// matmul binary: matmul(Expr(A), Expr(B))
template <typename Lhs, typename Rhs>
constexpr auto matmul(const Lhs &lhs, const Rhs &rhs) -> MatMulExpr<Lhs, Rhs> {
  return MatMulExpr<Lhs, Rhs>(lhs, rhs);
}

} // namespace ad
#endif // __MATOPS_H__