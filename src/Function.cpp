#include <algorithm>
#include <vector>
#include <cmath>

#include "Function.h"
#include "Symbol.h"


namespace ad{
    template <typename T, typename U = T>
    requires SymbolLike<T> && SymbolLike<U>
    auto pow(const T &lhs, const U &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto exp(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto ln(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto sin(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto cos(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto tan(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto cot(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto sec(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto csc(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto sinh(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto cosh(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto tanh(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto coth(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto sech(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto csch(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto asin(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto acos(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto atan(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto acot(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto asec(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto acsc(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto asinh(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto acosh(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto atanh(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto acoth(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto asech(const T &rhs) noexcept -> Symbol;

    template <typename T>
    requires SymbolLike<T>
    auto acsch(const T &rhs) noexcept -> Symbol;
    
} // namespace ad

