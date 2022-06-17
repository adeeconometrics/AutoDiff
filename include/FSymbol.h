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
#include <functional>
#include <cmath>

/**
 * todo:
 * - vector and scalar function specialization
 * - make_vjp
 * */

namespace ad {

template <typename T> 
requires AbstractRealVector<T> || std::is_floating_point_v<T>
class FSymbol {
private:
	T m_dot;
	T m_val;
public:
	FSymbol(const T& _val, const T& _dot):
		m_val {_val}, m_dot {_dot} {}

	FSymbol(const T& _dot): 
		m_dot {_dot} {}

	auto value() const noexcept -> T {return m_val; }
	auto dot() const noexcept -> T {return m_dot; }
};

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T> 
auto operator+(const FSymbol<T>& lhs, const FSymbol<T>& rhs) -> FSymbol<T> {
	return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()}; // scalar
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto operator-(const FSymbol<T>& lhs, const FSymbol<T>& rhs) -> FSymbol<T> {
  return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto operator*(const FSymbol<T>& lhs, const FSymbol<T>& rhs) -> FSymbol<T>{
  return {lhs.value() * rhs.value(),
          lhs.dot() * rhs.value() + rhs.dot() * lhs.value()};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto operator/(const FSymbol<T>& lhs, const FSymbol<T>& rhs) -> FSymbol<T> {
  const auto df = (lhs.dot() * rhs.value() - lhs.value() * rhs.dot()) /
                    pow(rhs.value(), 2);
  return {lhs.value() / rhs.value(), df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto pow(const FSymbol<T>& base, const FSymbol<T>& exp) -> FSymbol<T> {
  const auto df_base = log(base.value()) * pow(base.value(), exp.value()) * exp.dot();
  return {pow(base.value(), exp.value()), df_base};
}

template <typename T, typename U>
	requires (AbstractRealVector<T> || std::is_floating_point_v<T>) &&
			std::is_arithmetic<U>::value
auto pow(const FSymbol<T>& base, U exp) -> FSymbol<T> {
	const auto df_base = base.dot() * pow(base.value(), exp - 1);
	return {pow(base.value(), exp), df_base};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto exp(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = exp(rhs.value());
  const auto df = value * rhs.dot();
  return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>;
auto ln(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = log(rhs.value());
  const auto df = (1.0 / rhs.value()) * rhs.dot();
  return {value, df};
}


template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto sin(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = sin(rhs.value());
  const auto df = cos(rhs.value()) * rhs.dot();
  return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto cos(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
	const auto value = cos(lhs.value());
	const auto df = -1*sin(rhs.value()) * rhs.dot();
	return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto tan(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
	const auto value = tan(rhs.value());
	const auto df = pow(1.0/cos(rhs.value()),2) * rhs.dot();
	return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto cot(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
	const auto value = 1.0 / tan(rhs.value());
	const auto df = -1 * pow(1.0/sin(rhs.value()), 2) * rhs.dot();
	return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto sec(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = 1.0 / cos(rhs.value());
  const auto df = value * tan(rhs.value()) * rhs.dot();
  return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto csc(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = 1.0 / sin(rhs.value());
  const auto df = -1.0 * value * (1.0 / tan(rhs.value())) * rhs.dot();
  return {value, df};
}


template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto sinh(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = sinh(rhs.value());
  const auto df = cosh(rhs.value()) * rhs.dot();
  return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto cosh(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = cosh(rhs.value());
  const auto df = -1.0 * sinh(rhs.value()) * rhs.dot();
  return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto tanh(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
	const auto value = tanh(rhs.value());
	const auto df = -1.0 * pow(1.0/sinh(rhs.value()), 2) * rhs.dot();
	return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto coth(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = 1.0 / tanh(rhs.value());
  const auto df = -1.0 * pow(1.0 / sinh(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto sech(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = 1.0 / std::cosh(rhs.value());
  const auto df = value * std::tanh(rhs.value()) * rhs.dot();
  return {value, df};
}

template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto csch(const FSymbol<T>& rhs) noexcept -> FSymbol<T> {
  const auto value = 1.0 / std::sinh(rhs.value());
  const auto df = -1.0*value * (1.0 / std::tanh(rhs.value())) * rhs.dot();
  return {value, df};
}


template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto asin(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto acos(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto atan(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto acot(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto asec(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto acsc(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;


template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto asinh(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto acosh(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto atanh(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto acoth(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto asech(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;
template<typename T>
	requires AbstractRealVector<T> || std::is_floating_point_v<T>
auto acsch(const FSymbol<T>& rhs) noexcept -> FSymbol<T>;

}


#endif // __FSYMBOL_H__
