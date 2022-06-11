#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>

namespace ad {

class Sym {
private:
	double m_val{};
	double m_dot{};
public:
	Sym(double _val, double _dot):
		m_val(_val), m_dot(_dot){}

	Sym(double _val):m_val(_val){}
	
	auto value() const noexcept -> double {return m_val;}
	auto dot() const noexcept -> double {return m_dot; }
};

auto operator+(const Sym& lhs, const Sym& rhs) -> Sym {
	return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()};
}

auto operator-(const Sym& lhs, const Sym& rhs) -> Sym {
	return {lhs.value() - rhs.value(), lhs.dot() - rhs.dot()};
}

auto operator*(const Sym& lhs, const Sym& rhs) -> Sym {
	return {lhs.value() * rhs.value(), 
		lhs.dot()*rhs.value() + rhs.dot()*lhs.value()};
}

auto operator/(const Sym& lhs, const Sym& rhs) -> Sym {
	const double df = (lhs.dot()*rhs.value() - lhs.value()*rhs.dot())/std::pow(rhs.value(),2);
	return {lhs.value()/rhs.value(), df};
}

auto pow(const Sym& base, const Sym& exp) -> Sym{
	const double df_base = std::log(base.value())*std::pow(base.value(), exp.value())*exp.dot();
	return {
		std::pow(base.value(), exp.value()),
		df_base
	};
}

auto exp(const Sym& rhs) noexcept -> Sym {
	const double value= std::exp(rhs.value());
	const double df = value*rhs.dot();
	return {value, df};
}

auto ln(const Sym& rhs) noexcept -> Sym{
	const double value= std::log(rhs.value());
	const double df = (1.0f/rhs.value())*rhs.dot();
	return {value, df};
}

auto sin(const Sym& rhs) noexcept -> Sym{
	const double value= std::sin(rhs.value());
	const double df = std::cos(rhs.value())*rhs.dot();
	return {value, df};
}

auto cos(const Sym& rhs) noexcept -> Sym{
	const double value= std::cos(rhs.value());
	const double df = -std::sin(rhs.value())*rhs.dot();
	return {value, df};
}

auto tan(const Sym& rhs) noexcept -> Sym{
	const double value= std::tan(rhs.value());
	const double df = std::pow(1.0f/std::cos(rhs.value()),2)*rhs.dot();
	return {value, df};
}

auto cot(const Sym& rhs) noexcept -> Sym{
	const double value= 1.0f/std::tan(rhs.value());
	const double df = -std::pow(1.0f/std::sin(rhs.value()),2)*rhs.dot();
	return {value, df};
}

auto sec(const Sym& rhs) noexcept -> Sym{
	const double value= 1.0f/std::cos(rhs.value());
	const double df = value*std::tan(rhs.value())*rhs.dot();
	return {value, df};
}

auto csc(const Sym& rhs) noexcept -> Sym{
	const double value= 1.0f/std::sin(rhs.value());
	const double df = -value*(1.0f/std::tan(rhs.value()))*rhs.dot();
	return {value, df};
}

};


auto main(void) -> int {
	auto a = ad::Sym{1.5, 0};
	auto b = ad::Sym{0.5, 1};

	auto f = ad::sin(a*b)/ad::cos(b)*ad::pow(a,b);
	std::cout << std::setprecision(15) << f.dot() << '\n'; 
}
