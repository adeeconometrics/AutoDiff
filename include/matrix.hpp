#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cassert>
#include <initializer_list>
#include <type_traits>
#include <vector>

namespace ad {

template <typename T, std::size_t Rows, std::size_t Cols> class Matrix {
public:
  using iterator = std::vector<T>::iterator;
  using const_iterator = std::vector<T>::const_iterator;

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
    return m_data[t_row * Cols + t_col];
  }

private:
  std::vector<T> m_data;
};

} // namespace ad

#endif // __MATRIX_H__