#include "Utils.h"

#include <cmath>
#include <concepts>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>

namespace ad {

template <IsIterable T>
auto operator<<(std::ostream &os, const T &v) -> std::ostream & {
  for (const auto i : v)
    os << i;
  return os;
}

template <HasNumericValueType T>
auto operator<<(std::ostream &os, const T &v) -> std::ostream & {
  for (const auto i : v) {
    const float log = std::log10(std::abs(i));
    const uint8_t available_space =
        TextSpace.Width - (i < 0) * TextSpace.DecimalSign;
    const bool has_scientific_notation =
        i != 0.0 && (log < -1.0 * available_space + TextSpace.DecimalSign +
                               TextSpace.NegativeSign ||
                     log > available_space);
    os << "  " << std::setw(TextSpace.Width);
    if (has_scientific_notation) {
      double llog = std::log10(log);
      const uint8_t digits_after_exponent =
          std::max(TextSpace.Exponent, static_cast<uint8_t>(llog));
      const uint8_t digits_after_dot = std::max(1.0, llog);
      uint8_t new_precision = available_space - digits_after_exponent -
                              TextSpace.Exponent - TextSpace.DecimalSign -
                              digits_after_dot;
      if (new_precision > available_space) {
        new_precision = 0;
      }
      os << std::scientific << std::setprecision(new_precision);
    } else {
      const uint8_t fixed_digitspace_before_decimal = std::max(log + 1.0, 1.0);
      const uint8_t fixed_digitspace_after_decimal =
          available_space - TextSpace.DecimalSign -
          fixed_digitspace_before_decimal;
      os << std::fixed << std::setprecision(fixed_digitspace_after_decimal);
    }

    os << i;
  }
  return os << '\n';
}

} // namespace ad