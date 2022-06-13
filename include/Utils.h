/**
 * @file Utils.h
 * @author ddamiana
 * @brief contains concept predicates and print module
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <concepts>
#include <iostream>
#include <type_traits>

namespace ad {

template <typename T>
concept IsNumber = std::is_arithmetic<T>::value;

template <typename T>
concept HasPushBack = requires(T t, typename T::const_reference element) {
  typename T::const_iterator;
  typename T::const_reference;

  { t.push_back(element) } -> std::same_as<void>;
};

template <typename T>
concept IsIterable = requires(T t) {
  typename T::const_iterator;
  typename T::iterator;
};

template <typename T>
concept HasNumericValueType = requires(typename T::value_type value) {
  typename T::value_type;
  std::is_arithmetic<decltype(value)>::value;
};

template <typename T>
concept IsSymbolOrNumeric = IsNumber<T> || std::is_same<T, Symbol>::value;

template <typename T>
concept AbstractNumericVector = HasNumericValueType<T> && HasPushBack<T>;

// template <typename T>
// concept IsCallable = requires(T t){
//     T
// }

const struct {
  uint8_t Width = 8;
  uint8_t DecimalSign = 1;
  uint8_t NegativeSign = 1;
  uint8_t SciNotation = 2;
  uint8_t Exponent = 2;
} TextSpace;

template <IsIterable T>
auto operator<<(std::ostream &, const T &) -> std::ostream &;

template <HasNumericValueType T>
auto operator<<(std::ostream &, const T &) -> std::ostream &;

} // namespace ad

#endif // __UTILS_H__
