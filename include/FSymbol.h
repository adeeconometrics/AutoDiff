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

#include "Function.h"
#include "Utils.h"

#include <type_traits>
#include <concepts>
#include <map>

/**
 * todo:
 * - requires clause to constrain types on is_floating_point
 * - configure template parameters
 * - make_vjp
 * - vectorized function
 * */

namespace ad{

template <typename T> 
	requires std::is_floating_point_v<T>
class FSymbol {
private:
	T m_dot{};
	T m_val{};
public:
	FSymbol(const std::map<FSymbol, T> &, T);
	FSymbol(T);

	auto value() const noexcept -> T;
	auto dot() const noexcept -> T;
	
	auto operator<(const FSymbol<T>&) const -> bool;
	auto operator>(const FSymbol<T>&) const -> bool;
	auto operator==(const FSymbol<T>&) const -> bool;
	auto operator!=(const FSymbol<T>&) const -> bool;
};

template<typename T>
	requires std::is_floating_point_v<T> 
auto operator+(const FSymbol<T>&, const FSymbol<T>&) -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto operator-(const FSymbol<T>&, const FSymbol<T>&) -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto operator*(const FSymbol<T>&, const FSymbol<T>&) -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto operator/(const FSymbol<T>&, const FSymbol<T>&) -> FSymbol<T>;

template<typename T>
	requires std::is_floating_point_v<T>
auto pow(const FSymbol<T>&, const FSymbol<T>&) -> FSymbol<T>;

template <typename T>
requires std::is_arithmetic<T>
template<typename T>
	requires std::is_floating_point_v<T>
auto pow(const FSymbol<T>&, T) -> FSymbol<T>;

template<typename T>
	requires std::is_floating_point_v<T>
auto exp(const FSymbol<T>&) noexcept -> FSymbol
template<typename T>
	requires std::is_floating_point_v<T>;
auto ln(const FSymbol<T>&) noexcept -> FSymbol<T>;

template<typename T>
	requires std::is_floating_point_v<T>
auto sin(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto cos(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto tan(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto cot(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto sec(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto csc(const FSymbol<T>&) noexcept -> FSymbol<T>;

template<typename T>
	requires std::is_floating_point_v<T>
auto sinh(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto cosh(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto tanh(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto coth(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto sech(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto csch(const FSymbol<T>&) noexcept -> FSymbol<T>;

template<typename T>
	requires std::is_floating_point_v<T>
auto arcsin(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arccos(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arctan(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arccot(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arcsec(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arccsc(const FSymbol<T>&) noexcept -> FSymbol<T>;

template<typename T>
	requires std::is_floating_point_v<T>
auto arcsinh(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arccosh(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arctanh(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arccoth(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arcsech(const FSymbol<T>&) noexcept -> FSymbol<T>;
template<typename T>
	requires std::is_floating_point_v<T>
auto arccsch(const FSymbol<T>&) noexcept -> FSymbol<T>;

}


#endif // __FSYMBOL_H__
