/**
 * @file FSymbol.h
 * @author ddamiana
 * @brief contains methods for forward_mode AD
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __FSYMBOL_H__
#define __FSYMBOL_H__

#include <type_traits>
#include <concepts>
#include <map>

#include "Function.h"

/**
 * todo:
 * - requires clause to constrain types on is_floating_point
 * - configure template parameters
 * - make_vjp
 * - vectorized function
 * */

namespace ad{

template <typename T> class FSymbol {
private:
	T m_dot{};
	T m_val{};
public:
	FSymbol(const std::map<FSymbol, T> &, T);
	FSymbol(T);

	auto value() const noexcept -> T;
	auto dot() const noexcept -> T;
	
	auto operator<(const FSymbol&) const -> bool;
	auto operator>(const FSymbol&) const -> bool;
	auto operator==(const FSymbol&) const -> bool;
	auto operator!=(const FSymbol&) const -> bool;
};
// auto with templates
auto operator+(const FSymbol&, const FSymbol&) -> FSymbol;
auto operator-(const FSymbol&, const FSymbol&) -> FSymbol;
auto operator*(const FSymbol&, const FSymbol&) -> FSymbol;
auto operator/(const FSymbol&, const FSymbol&) -> FSymbol;

auto pow(const FSymbol&, const FSymbol&) -> FSymbol;

template <typename T>
requires std::is_arithmetic<T>
auto pow(const FSymbol&, T) -> FSymbol;

auto exp(const FSymbol&) noexcept -> FSymbol;
auto ln(const FSymbol&) noexcept -> FSymbol;

auto sin(const FSymbol&) noexcept -> FSymbol;
auto cos(const FSymbol&) noexcept -> FSymbol;
auto tan(const FSymbol&) noexcept -> FSymbol;
auto cot(const FSymbol&) noexcept -> FSymbol;
auto sec(const FSymbol&) noexcept -> FSymbol;
auto csc(const FSymbol&) noexcept -> FSymbol;

auto sinh(const FSymbol&) noexcept -> FSymbol;
auto cosh(const FSymbol&) noexcept -> FSymbol;
auto tanh(const FSymbol&) noexcept -> FSymbol;
auto coth(const FSymbol&) noexcept -> FSymbol;
auto sech(const FSymbol&) noexcept -> FSymbol;
auto csch(const FSymbol&) noexcept -> FSymbol;

auto arcsin(const FSymbol&) noexcept -> FSymbol;
auto arccos(const FSymbol&) noexcept -> FSymbol;
auto arctan(const FSymbol&) noexcept -> FSymbol;
auto arccot(const FSymbol&) noexcept -> FSymbol;
auto arcsec(const FSymbol&) noexcept -> FSymbol;
auto arccsc(const FSymbol&) noexcept -> FSymbol;

auto arcsinh(const FSymbol&) noexcept -> FSymbol;
auto arccosh(const FSymbol&) noexcept -> FSymbol;
auto arctanh(const FSymbol&) noexcept -> FSymbol;
auto arccoth(const FSymbol&) noexcept -> FSymbol;
auto arcsech(const FSymbol&) noexcept -> FSymbol;
auto arccsch(const FSymbol&) noexcept -> FSymbol;

}


#endif // __FSYMBOL_H__
