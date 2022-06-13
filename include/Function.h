/**
 * @file Function.h
 * @author ddamiana
 * @brief contains base functions for scalar and vector-valued functions
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "Utils.h"

namespace ad {

template <typename T>
requires AbstractNumericVector<T>
auto operator+(const T &t, const T &t) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto operator-(const T &, const T &) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto operator*(const T &, const T &) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto operator/(const T &, const T &) -> T;

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator+(const T &t, U) -> T;

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator-(const T &, U) -> T;

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator*(const T &, U) -> T;

template <typename T, typename U>
requires AbstractNumericVector<T> && IsNumber<U>
auto operator/(const T &, U) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto sin(const T &t) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto cos(const T &t) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto tan(const T &t) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto cot(const T &) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto sec(const T &) -> T;

template <typename T>
requires AbstractNumericVector<T>
auto csc(const T &) -> T;

} // namespace ad

#endif // __FUNCTION_H__
