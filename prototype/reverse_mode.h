#ifndef __AUTODIFF_H__
#define __AUTODIFF_H__

#include <map>

namespace ad{
class Symbol {
private:
	std::map<Symbol, double> m_local_gradient;
	double m_value{};
public:
	Symbol(const std::map<Symbol, double> &, double);
	Symbol(double);

	auto value() const noexcept -> double;
	auto local_gradient() const noexcept -> double;
	
	auto operator<(const Symbol&) const -> bool;
	auto operator>(const Symbol&) const -> bool;
	auto operator==(const Symbol&) const -> bool;
	auto operator!=(const Symbol&) const -> bool;
};

auto operator+(const Symbol&, const Symbol&) -> Symbol;
auto operator-(const Symbol&, const Symbol&) -> Symbol;
auto operator*(const Symbol&, const Symbol&) -> Symbol;
auto operator/(const Symbol&, const Symbol&) -> Symbol;

auto pow(const Symbol&, const Symbol&) -> Symbol;
auto exp(const Symbol&) noexcept -> Symbol;
auto ln(const Symbol&) noexcept -> Symbol;

auto sin(const Symbol&) noexcept -> Symbol;
auto cos(const Symbol&) noexcept -> Symbol;
auto tan(const Symbol&) noexcept -> Symbol;
auto cot(const Symbol&) noexcept -> Symbol;
auto sec(const Symbol&) noexcept -> Symbol;
auto csc(const Symbol&) noexcept -> Symbol;

auto sinh(const Symbol&) noexcept -> Symbol;
auto cosh(const Symbol&) noexcept -> Symbol;
auto tanh(const Symbol&) noexcept -> Symbol;
auto coth(const Symbol&) noexcept -> Symbol;
auto sech(const Symbol&) noexcept -> Symbol;
auto csch(const Symbol&) noexcept -> Symbol;

auto arcsin(const Symbol&) noexcept -> Symbol;
auto arccos(const Symbol&) noexcept -> Symbol;
auto arctan(const Symbol&) noexcept -> Symbol;
auto arccot(const Symbol&) noexcept -> Symbol;
auto arcsec(const Symbol&) noexcept -> Symbol;
auto arccsc(const Symbol&) noexcept -> Symbol;

auto arcsinh(const Symbol&) noexcept -> Symbol;
auto arccosh(const Symbol&) noexcept -> Symbol;
auto arctanh(const Symbol&) noexcept -> Symbol;
auto arccoth(const Symbol&) noexcept -> Symbol;
auto arcsech(const Symbol&) noexcept -> Symbol;
auto arccsch(const Symbol&) noexcept -> Symbol;

auto gradient(const Symbol&) -> std::map<Symbol, double>;

}


#endif // __AUTODIFF_H__
