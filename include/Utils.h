/**
 * @file Utils.h
 * @author ddamiana
 * @brief contains concept predicates and print module
 * @version 0.2
 * @date 2022-06-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <cmath>
#include <concepts>
#include <cstdint>
#include <iomanip>
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
concept HasSize = requires(T t) {
  { t.size(void) } -> std::same_as<size_t>;
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
concept HasRealValueType = requires(typename T::value_type value) {
  typename T::value_type;
  std::is_floating_point<decltype(value)>::value;
};

template <typename T>
concept IsSymbolOrNumeric = IsNumber<T> || std::is_same<T, Symbol>::value;

template <typename T>
concept AbstractNumericVector = HasNumericValueType<T> && HasPushBack<T>;

template <typename T>
concept AbstractRealVector = HasRealValueType<T> && HasPushBack<T>;

const struct {
  uint8_t Width = 8;
  uint8_t DecimalSign = 1;
  uint8_t NegativeSign = 1;
  uint8_t SciNotation = 2;
  uint8_t Exponent = 2;
} TextSpace;

} // namespace ad

template <typename T>
requires ad::IsIterable<T>
auto operator<<(std::ostream &, const T &) -> std::ostream &{
  for (const auto i : v)
    os << i;
  return os;
}

template <typename T>
requires ad::HasNumericValueType<T> && ad::IsIterable<T>
inline auto operator<<(std::ostream &os, const T &v) -> std::ostream & {
  for (const auto i : v) {
    const float log = std::log10(std::abs(i));
    const uint8_t available_space =
        ad::TextSpace.Width - (i < 0) * ad::TextSpace.DecimalSign;
    const bool has_scientific_notation =
        i != 0.0 && (log < -1.0 * available_space + ad::TextSpace.DecimalSign +
                               ad::TextSpace.NegativeSign ||
                     log > available_space);
    os << "  " << std::setw(ad::TextSpace.Width);
    if (has_scientific_notation) {
      double llog = std::log10(log);
      const uint8_t digits_after_exponent =
          std::max(ad::TextSpace.Exponent, static_cast<uint8_t>(llog));
      const uint8_t digits_after_dot = std::max(1.0, llog);
      uint8_t new_precision = available_space - digits_after_exponent -
                              ad::TextSpace.Exponent -
                              ad::TextSpace.DecimalSign - digits_after_dot;
      if (new_precision > available_space) {
        new_precision = 0;
      }
      os << std::scientific << std::setprecision(new_precision);
    } else {
      const uint8_t fixed_digitspace_before_decimal = std::max(log + 1.0, 1.0);
      const uint8_t fixed_digitspace_after_decimal =
          available_space - ad::TextSpace.DecimalSign -
          fixed_digitspace_before_decimal;
      os << std::fixed << std::setprecision(fixed_digitspace_after_decimal);
    }

    os << i;
  }
  return os << '\n';
}

#endif // __UTILS_H__
