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

#include "Function.h"
#include "Utilities.h"

#include <type_traits>
#include <concepts>
#include <map>

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

    auto operator<(const RSymbol<T>& rhs) const -> bool;
	auto operator>(const RSymbol<T>& rhs) const -> bool;
	auto operator==(const RSymbol<T>& rhs) const -> bool;
	auto operator!=(const RSymbol<T>& rhs) const -> bool;
};

template<typename T>
requires std::is_floating_point_v<T>
auto operator+(const RSymbol<T>& lhs, const RSymbol<T>& rhs) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto operator-(const RSymbol<T>& lhs, const RSymbol<T>& rhs) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto operator*(const RSymbol<T>& lhs, const RSymbol<T>& rhs) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto operator/(const RSymbol<T>& lhs, const RSymbol<T>& rhs) -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto pow(const RSymbol<T>& lhs, const RSymbol<T>& rhs) -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>;
auto exp(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>;
auto ln(const RSymbol<T>& rhs) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto sin(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto cos(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto tan(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto cot(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto sec(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto csc(const RSymbol<T>& rhs) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto sinh(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto cosh(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto tanh(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto coth(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto sech(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto csch(const RSymbol<T>& rhs) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto asin(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto acos(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto atan(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto acot(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto asec(const RSymbol<T>& rhs) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto acsc(const RSymbol<T>& rhs) noexcept -> RSymbol;

template<typename T>
requires std::is_floating_point_v<T>
auto asinh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto acosh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto atanh(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto acoth(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto asech(const RSymbol<T>&) noexcept -> RSymbol;
template<typename T>
requires std::is_floating_point_v<T>
auto acsch(const RSymbol<T>&) noexcept -> RSymbol;

auto gradient(const RSymbol<T>&) -> std::map<RSymbol, T>;

}


#endif // __RSYMBOL_H__
