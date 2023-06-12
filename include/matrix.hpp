#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <algorithm>
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

namespace MatIterator {

template <typename T>
using iterator = typename std::vector<std::vector<T>>::iterator;

template <typename T>
using const_iterator = typename std::vector<std::vector<T>>::const_iterator;

} // namespace MatIterator

template <typename T> struct BaseMatrix {

public:
  BaseMatrix() = delete;
  BaseMatrix(const BaseMatrix<T> &) = default;
  BaseMatrix(BaseMatrix<T> &&) = default;

  BaseMatrix(std::size_t m, std::size_t n) : m_row(m), m_col(n) {}
  virtual ~BaseMatrix() = default;

  auto operator=(const BaseMatrix<T> &) -> BaseMatrix<T> & = default;
  auto operator=(BaseMatrix<T> &&) -> BaseMatrix<T> & = default;

  auto dims() const noexcept -> std::pair<std::size_t, std::size_t> {
    return {m_row, m_col};
  }

  virtual auto at(std::size_t t_row, std::size_t t_col) noexcept -> T & = 0;
  virtual auto at(std::size_t t_row, std::size_t t_col) const noexcept
      -> const T & = 0;

  virtual auto begin() noexcept -> MatIterator::iterator<T> = 0;
  virtual auto end() noexcept -> MatIterator::iterator<T> = 0;
  virtual auto cbegin() const noexcept -> MatIterator::const_iterator<T> = 0;
  virtual auto cend() const noexcept -> MatIterator::const_iterator<T> = 0;

private:
  std::size_t m_row;
  std::size_t m_col;
};

template <typename T> struct SquareMatrix : public BaseMatrix<T> {
  SquareMatrix(std::size_t m)
      : BaseMatrix<T>(m, m), m_matrix(m, std::vector<T>(m)) {}

  SquareMatrix(std::initializer_list<std::initializer_list<T>> t_list)
      : BaseMatrix<T>(t_list.size(), t_list.size()),
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

  auto begin() noexcept -> MatIterator::iterator<T> override {
    return m_matrix.begin();
  }

  auto end() noexcept -> MatIterator::iterator<T> override {
    return m_matrix.end();
  }

  auto cbegin() const noexcept -> MatIterator::const_iterator<T> override {
    return m_matrix.cbegin();
  }
  auto cend() const noexcept -> MatIterator::const_iterator<T> override {
    return m_matrix.cend();
  }

private:
  std::vector<std::vector<T>> m_matrix;
};

template <typename T> struct RectMatrix : public BaseMatrix<T> {
  RectMatrix(std::size_t m, std::size_t n)
      : BaseMatrix<T>(m, n), m_matrix(m, std::vector<T>(n)) {}

  // should check if all rows are in proper size
  RectMatrix(std::initializer_list<std::initializer_list<T>> t_list)
      : BaseMatrix<T>(t_list.size(), t_list.size()),
        m_matrix(std::vector<std::vector<T>>(t_list.begin(), t_list.end())) {}

  auto at(std::size_t t_row, std::size_t t_col) noexcept -> T & override {
    return m_matrix[t_row][t_col];
  }

  auto at(std::size_t t_row, std::size_t t_col) const noexcept
      -> const T & override {
    return m_matrix[t_row][t_col];
  }

  auto begin() noexcept -> MatIterator::iterator<T> override {
    return m_matrix.begin();
  }

  auto end() noexcept -> MatIterator::iterator<T> override {
    return m_matrix.end();
  }

  auto cbegin() const noexcept -> MatIterator::const_iterator<T> override {
    return m_matrix.cbegin();
  }
  auto cend() const noexcept -> MatIterator::const_iterator<T> override {
    return m_matrix.cend();
  }

private:
  std::vector<std::vector<T>> m_matrix;
};

} // namespace ad

#endif // __MATRIX_H__