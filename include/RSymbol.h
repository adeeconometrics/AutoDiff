/**
 * @file RSymbol.h
 * @author ddamiana
 * @brief contains methods for reverse_mode AD
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __RSYMBOL_H__
#define __RSYMBOL_H__

#include <map>

#include "Function.h"

namespace ad{
class RSymbol {
private:
	std::map<RSymbol, double> m_local_gradient;
	double m_value{};
public:
	RSymbol(const std::map<RSymbol, double> &, double);
	RSymbol(double);

	auto value() const noexcept -> double;
	auto local_gradient() const noexcept -> double;
	
	auto operator<(const RSymbol&) const -> bool;
	auto operator>(const RSymbol&) const -> bool;
	auto operator==(const RSymbol&) const -> bool;
	auto operator!=(const RSymbol&) const -> bool;
};

auto operator+(const RSymbol&, const RSymbol&) -> RSymbol;
auto operator-(const RSymbol&, const RSymbol&) -> RSymbol;
auto operator*(const RSymbol&, const RSymbol&) -> RSymbol;
auto operator/(const RSymbol&, const RSymbol&) -> RSymbol;

auto pow(const RSymbol&, const RSymbol&) -> RSymbol;
auto exp(const RSymbol&) noexcept -> RSymbol;
auto ln(const RSymbol&) noexcept -> RSymbol;

auto sin(const RSymbol&) noexcept -> RSymbol;
auto cos(const RSymbol&) noexcept -> RSymbol;
auto tan(const RSymbol&) noexcept -> RSymbol;
auto cot(const RSymbol&) noexcept -> RSymbol;
auto sec(const RSymbol&) noexcept -> RSymbol;
auto csc(const RSymbol&) noexcept -> RSymbol;

auto sinh(const RSymbol&) noexcept -> RSymbol;
auto cosh(const RSymbol&) noexcept -> RSymbol;
auto tanh(const RSymbol&) noexcept -> RSymbol;
auto coth(const RSymbol&) noexcept -> RSymbol;
auto sech(const RSymbol&) noexcept -> RSymbol;
auto csch(const RSymbol&) noexcept -> RSymbol;

auto arcsin(const RSymbol&) noexcept -> RSymbol;
auto arccos(const RSymbol&) noexcept -> RSymbol;
auto arctan(const RSymbol&) noexcept -> RSymbol;
auto arccot(const RSymbol&) noexcept -> RSymbol;
auto arcsec(const RSymbol&) noexcept -> RSymbol;
auto arccsc(const RSymbol&) noexcept -> RSymbol;

auto arcsinh(const RSymbol&) noexcept -> RSymbol;
auto arccosh(const RSymbol&) noexcept -> RSymbol;
auto arctanh(const RSymbol&) noexcept -> RSymbol;
auto arccoth(const RSymbol&) noexcept -> RSymbol;
auto arcsech(const RSymbol&) noexcept -> RSymbol;
auto arccsch(const RSymbol&) noexcept -> RSymbol;

auto gradient(const RSymbol&) -> std::map<RSymbol, double>;

}


#endif // __RSYMBOL_H__
