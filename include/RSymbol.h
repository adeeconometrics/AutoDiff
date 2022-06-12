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

#include <type_traits>
#include <concepts>
#include <map>

#include "Function.h"

namespace ad{
template <typename T>
requires std::is_floating_point_v<T>
class RSymbol {
private:
	std::map<RSymbol, T> m_local_gradient;
	T m_value{};
public:
	RSymbol(const std::map<RSymbol, T> &, T);
	RSymbol(T);

	auto value() const noexcept -> T;
    auto local_gradient() const noexcept -> std::map<RSymbol, T>;

    auto operator<(const RSymbol<T>&) const -> bool;
	auto operator>(const RSymbol<T>&) const -> bool;
	auto operator==(const RSymbol<T>&) const -> bool;
	auto operator!=(const RSymbol<T>&) const -> bool;
};

template<typename T>
requires std::is_floating_point_v<T>
auto operator+(const RSymbol<T>&, const RSymbol<T>&) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto operator-(const RSymbol<T>&, const RSymbol<T>&) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto operator*(const RSymbol<T>&, const RSymbol<T>&) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto operator/(const RSymbol<T>&, const RSymbol<T>&) -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto pow(const RSymbol<T>&, const RSymbol<T>&) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>;
auto exp(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>;
auto ln(const RSymbol<T>&) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto sin(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto cos(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto tan(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto cot(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto sec(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto csc(const RSymbol<T>&) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto sinh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto cosh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto tanh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto coth(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto sech(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto csch(const RSymbol<T>&) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto arcsin(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arccos(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arctan(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arccot(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arcsec(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arccsc(const RSymbol<T>&) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto arcsinh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arccosh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arctanh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arccoth(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arcsech(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto arccsch(const RSymbol<T>&) noexcept -> RSymbol;

auto gradient(const RSymbol<T>&) -> std::map<RSymbol, T>;

}


#endif // __RSYMBOL_H__
