#ifndef __UTILS_H__
#define __UTILS_H__

#include "../include/matrix.hpp"
#include "../include/vector.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
auto operator<<(std::ostream &os, const ad::Matrix<T> &Matrix)
    -> std::ostream & {
  static_assert(std::is_arithmetic_v<T>,
                "template parameter must be of type arithmetic");

  if (Matrix.empty()) {
    os << "[]" << std::endl;
    return os;
  }

  std::size_t max_width = 0;
  for (const auto &row : Matrix) {
    for (const auto &element : row) {
      std::size_t width = std::to_string(element).size();
      if (width > max_width) {
        max_width = width;
      }
    }
  }

  os << "[";
  for (std::size_t i = 0; i < Matrix.size(); ++i) {
    if (i != 0) {
      os << " ";
    }
    os << "[";
    for (std::size_t j = 0; j < Matrix[i].size(); ++j) {
      os << std::setw(max_width) << Matrix[i][j];
      if (j != Matrix[i].size() - 1) {
        os << ", ";
      }
    }
    os << "]";
    if (i != Matrix.size() - 1) {
      os << '\n';
    }
  }
  return os << "]\n";
}

template <typename T>
auto operator<<(std::ostream &os, const std::vector<T> &v) -> std::ostream & {
  os << "[";
  for (const auto i : v) {
    os << i << " ";
  }
  return os << "]\n";
};

template <typename Fn, typename ArgType>
constexpr auto apply_fn(Fn &&fn, const ad::vector<ArgType> &v)
    -> ad::vector<std::invoke_result_t<Fn &, const ArgType &>> {

  using ResultType = std::invoke_result_t<Fn &, const ArgType &>;
  ad::vector<ResultType> result;
  result.reserve(v.size());

  std::transform(std::cbegin(v), std::cend(v), std::back_inserter(result), fn);

  return result;
}

template <typename Fn, typename ArgType>
constexpr auto apply_fn(Fn &&functor, const ad::Matrix<ArgType> &v)
    -> ad::Matrix<std::invoke_result_t<Fn &, const ArgType &>> {

  using ResultType = std::invoke_result_t<Fn &, const ArgType &>;
  ad::Matrix<ResultType> result{};

  for (const auto row : v) {
    result.emplace_back(apply_fn(row, functor));
  }

  return result;
}

#endif // __UTILS_H__