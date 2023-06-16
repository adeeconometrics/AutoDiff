#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <algorithm>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

namespace ad {

template <typename T>
constexpr auto
all_same_size(std::initializer_list<std::initializer_list<T>> t_list) -> bool {
  const std::size_t m = t_list.size();
  return std::all_of(t_list.begin(), t_list.end(),
                     [m](const auto i) { return i.size() == m; });
}

template <typename T> struct Matrix {

public:
  using iterator = typename std::vector<std::vector<T>>::iterator;
  using const_iterator = typename std::vector<std::vector<T>>::const_iterator;

public:
  Matrix() = delete;
  Matrix(const Matrix<T> &) = default;
  Matrix(Matrix<T> &&) = default;

  Matrix(std::size_t m, std::size_t n) : m_row(m), m_col(n) {}
  virtual ~Matrix() = default;

  auto operator=(const Matrix<T> &) -> Matrix<T> & = default;
  auto operator=(Matrix<T> &&) -> Matrix<T> & = default;

  auto dims() const noexcept -> std::pair<std::size_t, std::size_t> {
    return {m_row, m_col};
  }

  virtual auto at(std::size_t t_row, std::size_t t_col) noexcept -> T & = 0;
  virtual auto at(std::size_t t_row, std::size_t t_col) const noexcept
      -> const T & = 0;

  virtual auto begin() noexcept -> iterator = 0;
  virtual auto end() noexcept -> iterator = 0;
  virtual auto cbegin() const noexcept -> const_iterator = 0;
  virtual auto cend() const noexcept -> const_iterator = 0;

private:
  std::size_t m_row;
  std::size_t m_col;
};

template <typename T> struct SquareMatrix : public Matrix<T> {
public:
  using typename Matrix<T>::iterator;
  using typename Matrix<T>::const_iterator;

public:
  SquareMatrix(std::size_t m)
      : Matrix<T>(m, m), m_matrix(m, std::vector<T>(m)) {}

  SquareMatrix(std::initializer_list<std::initializer_list<T>> t_list)
      : Matrix<T>(t_list.size(), t_list.size()),
        m_matrix(std::vector<std::vector<T>>(t_list.begin(), t_list.end())) {
    assert(all_same_size(t_list));
  }

  auto at(std::size_t t_row, std::size_t t_col) noexcept -> T & override {
    return m_matrix[t_row][t_col];
  }

  auto at(std::size_t t_row, std::size_t t_col) const noexcept
      -> const T & override {
    return m_matrix[t_row][t_col];
  }

  auto begin() noexcept -> iterator override { return m_matrix.begin(); }

  auto end() noexcept -> iterator override { return m_matrix.end(); }

  auto cbegin() const noexcept -> const_iterator override {
    return m_matrix.cbegin();
  }
  auto cend() const noexcept -> const_iterator override {
    return m_matrix.cend();
  }

private:
  std::vector<std::vector<T>> m_matrix;
};

template <typename T> struct RectMatrix : public Matrix<T> {
public:
  using typename Matrix<T>::iterator;
  using typename Matrix<T>::const_iterator;

public:
  RectMatrix(std::size_t m, std::size_t n)
      : Matrix<T>(m, n), m_matrix(m, std::vector<T>(n)) {}

  // should check if all rows are in proper size
  RectMatrix(std::initializer_list<std::initializer_list<T>> t_list)
      : Matrix<T>(t_list.size(), t_list.size()),
        m_matrix(std::vector<std::vector<T>>(t_list.begin(), t_list.end())) {}

  auto at(std::size_t t_row, std::size_t t_col) noexcept -> T & override {
    return m_matrix[t_row][t_col];
  }

  auto at(std::size_t t_row, std::size_t t_col) const noexcept
      -> const T & override {
    return m_matrix[t_row][t_col];
  }

  auto begin() noexcept -> iterator override { return m_matrix.begin(); }

  auto end() noexcept -> iterator override { return m_matrix.end(); }

  auto cbegin() const noexcept -> const_iterator override {
    return m_matrix.cbegin();
  }
  auto cend() const noexcept -> const_iterator override {
    return m_matrix.cend();
  }

private:
  std::vector<std::vector<T>> m_matrix;
};

template <typename T>
constexpr auto operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
    -> Matrix<T> {

  assert(lhs.dims() == rhs.dims());

  Matrix<T> result;

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result), std::plus<T>());
  return result;
}

template <typename T>
constexpr auto operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
    -> Matrix<T>;

template <typename T>
constexpr auto operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
    -> Matrix<T>;

template <typename T>
constexpr auto operator/(const Matrix<T> &lhs, const Matrix<T> &rhs)
    -> Matrix<T>;

} // namespace ad

#endif // __MATRIX_H__