#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cassert>
#include <initializer_list>
#include <type_traits>
#include <vector>

namespace ad {

template <typename T, std::size_t Rows, std::size_t Cols> class Matrix {
public:
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

public:
  Matrix() { m_data.reserve(Rows * Cols); }

  Matrix(std::initializer_list<std::initializer_list<T>> t_list) {
    if (t_list.size() != Rows) {
      throw std::invalid_argument("Invalid number of rows in initializer list");
    }

    m_data.resize(Rows * Cols); // Resizing the vector to the appropriate size

    for (const auto &row : t_list) {
      if (row.size() != Cols) {
        throw std::invalid_argument(
            "Invalid number of columns in initializer list");
      }
      for (const auto &elem : row) {
        m_data.emplace_back(elem);
      }
    }
  }

  Matrix(const std::vector<T> &t_data) : m_data(t_data) {
    if (m_data.size() != Rows * Cols) {
      throw std::runtime_error("Invalid matrix size");
    }
  }

  auto operator()(std::size_t t_row, std::size_t t_col) -> T & {
#ifndef DEBUG
    assert(t_row < Rows && t_col < Cols);
#endif
    return m_data[t_row * Cols + t_col];
  }

  auto operator()(std::size_t t_row, std::size_t t_col) const -> const T & {
#ifndef DEBUG
    assert(t_row < Rows && t_col < Cols);
#endif
    return m_data[t_row * Cols + t_col];
  }

  constexpr auto rows() const noexcept -> std::size_t { return Rows; }
  constexpr auto cols() const noexcept -> std::size_t { return Cols; }

  constexpr auto begin() noexcept -> iterator { return m_data.begin(); }
  constexpr auto end() noexcept -> iterator { return m_data.end(); }
  constexpr auto cbegin() const noexcept -> const_iterator {
    return m_data.cbegin();
  }
  constexpr auto cend() const noexcept -> const_iterator {
    return m_data.cend();
  }

  template <typename Expr>
  friend constexpr auto eval(const Expr &t_expr) -> Matrix<T, Rows, Cols> {
    Matrix<T, Rows, Cols> result{};
    for (std::size_t i = 0; i < Rows; ++i) {
#ifdef __clang__
#pragma clang loop vectorize(enable)
#endif
      for (std::size_t j = 0; j < Cols; ++j) {
        result(i, j) = t_expr(i, j);
      }
    }
    return result;
  }

  template <typename Expr>
  friend constexpr auto eval_at(const Expr &t_expr, std::size_t i,
                                std::size_t j) -> T {
    return t_expr(i, j);
  }

private:
  std::vector<T> m_data;
};

} // namespace ad

#endif // __MATRIX_H__