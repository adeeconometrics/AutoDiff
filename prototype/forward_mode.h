#ifndef __FORWARD_MODE_H__
#define __FORWARD_MODE_H__

#include <vector>

using namespace ad{
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

auto ln(const Sym&) -> Sym;

auto sin(const Sym&) -> Sym;
auto cos(const Sym&) -> Sym;
auto tan(const Sym&) -> Sym;
auto cot(const Sym&) -> Sym;
auto sec(const Sym&) -> Sym;
auto csc(const Sym&) -> Sym;

auto sinh(const Sym&) -> Sym;
auto cosh(const Sym&) -> Sym;
auto tanh(const Sym&) -> Sym;
auto coth(const Sym&) -> Sym;
auto sech(const Sym&) -> Sym;
auto csch(const Sym&) -> Sym;

auto asin(const Sym&) -> Sym;
auto acos(const Sym&) -> Sym;
auto atan(const Sym&) -> Sym;
auto acot(const Sym&) -> Sym;
auto asec(const Sym&) -> Sym;
auto acsc(const Sym&) -> Sym;

auto asinh(const Sym&) -> Sym;
auto acosh(const Sym&) -> Sym;
auto atanh(const Sym&) -> Sym;
auto acoth(const Sym&) -> Sym;
auto asech(const Sym&) -> Sym;
auto acsch(const Sym&) -> Sym;

} // namespace ad


#endif
