#ifndef __FORWARD_MODE_H__
#define __FORWARD_MODE_H__

#include <vector>

namespace ad{
class Sym{
private:
	double m_val{};
	double m_dot{};
public:
	Sym(double, double);
	Sym(double);

	auto value() const noexcept -> double;
	auto dot() const noexcept -> double;
};

auto operator+(const Sym&, const Sym&) -> Sym;
auto operator-(const Sym&, const Sym&) -> Sym;
auto operator*(const Sym&, const Sym&) -> Sym;
auto operator/(const Sym&, const Sym&) -> Sym;

auto pow(const Sym&, const Sym&) -> Sym;

auto ln(const Sym&) noexcept -> Sym;

auto sin(const Sym&) noexcept -> Sym;
auto cos(const Sym&) noexcept -> Sym;
auto tan(const Sym&) noexcept -> Sym;
auto cot(const Sym&) noexcept -> Sym;
auto sec(const Sym&) noexcept -> Sym;
auto csc(const Sym&) noexcept -> Sym;

auto sinh(const Sym&) noexcept -> Sym;
auto cosh(const Sym&) noexcept -> Sym;
auto tanh(const Sym&) noexcept -> Sym;
auto coth(const Sym&) noexcept -> Sym;
auto sech(const Sym&) noexcept -> Sym;
auto csch(const Sym&) noexcept -> Sym;

auto asin(const Sym&) noexcept -> Sym;
auto acos(const Sym&) noexcept -> Sym;
auto atan(const Sym&) noexcept -> Sym;
auto acot(const Sym&) noexcept -> Sym;
auto asec(const Sym&) noexcept -> Sym;
auto acsc(const Sym&) noexcept -> Sym;

auto asinh(const Sym&) noexcept -> Sym;
auto acosh(const Sym&) noexcept -> Sym;
auto atanh(const Sym&) noexcept -> Sym;
auto acoth(const Sym&) noexcept -> Sym;
auto asech(const Sym&) noexcept -> Sym;
auto acsch(const Sym&) noexcept -> Sym;

} // namespace ad


#endif
