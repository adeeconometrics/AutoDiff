#ifndef __AUTODIFF_H__
#define __AUTODIFF_H__

#include <map>

namespace ad {
class Symbol {
private:
  std::map<Symbol, double> m_local_gradient;
  double m_value{};

public:
  Symbol(const std::map<Symbol, double> &, double);
  Symbol(double);

  auto value() const noexcept -> double;
  auto local_gradient() const noexcept -> std::map<Symbol, double>;

  auto operator<(const Symbol &) const -> bool;
  auto operator>(const Symbol &) const -> bool;
  auto operator==(const Symbol &) const -> bool;
  auto operator!=(const Symbol &) const -> bool;
};

auto operator+(const Symbol &, const Symbol &) -> Symbol;
auto operator-(const Symbol &, const Symbol &) -> Symbol;
auto operator*(const Symbol &, const Symbol &) -> Symbol;
auto operator/(const Symbol &, const Symbol &) -> Symbol;

auto pow(const Symbol &, const Symbol &) -> Symbol;
auto exp(const Symbol &) noexcept -> Symbol;
auto ln(const Symbol &) noexcept -> Symbol;

auto sin(const Symbol &) noexcept -> Symbol;
auto cos(const Symbol &) noexcept -> Symbol;
auto tan(const Symbol &) noexcept -> Symbol;
auto cot(const Symbol &) noexcept -> Symbol;
auto sec(const Symbol &) noexcept -> Symbol;
auto csc(const Symbol &) noexcept -> Symbol;

auto sinh(const Symbol &) noexcept -> Symbol;
auto cosh(const Symbol &) noexcept -> Symbol;
auto tanh(const Symbol &) noexcept -> Symbol;
auto coth(const Symbol &) noexcept -> Symbol;
auto sech(const Symbol &) noexcept -> Symbol;
auto csch(const Symbol &) noexcept -> Symbol;

auto asin(const Symbol &) noexcept -> Symbol;
auto acos(const Symbol &) noexcept -> Symbol;
auto atan(const Symbol &) noexcept -> Symbol;
auto acot(const Symbol &) noexcept -> Symbol;
auto asec(const Symbol &) noexcept -> Symbol;
auto acsc(const Symbol &) noexcept -> Symbol;

auto asinh(const Symbol &) noexcept -> Symbol;
auto acosh(const Symbol &) noexcept -> Symbol;
auto atanh(const Symbol &) noexcept -> Symbol;
auto acoth(const Symbol &) noexcept -> Symbol;
auto asech(const Symbol &) noexcept -> Symbol;
auto acsch(const Symbol &) noexcept -> Symbol;

auto gradient(const Symbol &) -> std::map<Symbol, double>;

} // namespace ad

#endif // __AUTODIFF_H__
