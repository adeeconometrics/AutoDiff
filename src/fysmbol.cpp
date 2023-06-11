#include "../include/fysmbol.hpp"

#include <functional>
#include <cmath>

namespace ad {

	FSym::FSym(double t_value, double t_dot): m_value(t_value), m_dot(t_dot) {};
	FSym::FSym(double t_value): m_dot(t_dot) {};

	auto FSym::operator<(const FSym &other) const noexcept ->bool {
		return m_value < other.m_value;
	}
	auto FSym::operator>(const FSym &other) const noexcept ->bool {
		return m_value > other.m_value;
	}
	auto FSym::operator==(const FSym &other) const noexcept ->bool {
		return m_value == other.m_value;
	}
	auto FSym::operator!=(const FSym &other) const noexcept ->bool {
		return m_value != other.m_value;
	}

auto operator+(const FSym& rhs, const FSym& lhs) ->FSym {
	return {rhs.value() + lhs.value(), rhs.dot() + rhs.dot()};
}

auto operator-(const FSym& rhs, const FSym& lhs) ->FSym {
	return {rhs.value() - lhs.value(), rhs.dot() - rhs.dot()};
}

auto operator*(const FSym& rhs, const FSym& lhs) ->FSym {
	return {rhs.value() * lhs.value(), 
		lhs.value() * rhs.dot() + lhs.dot() * rhs.value()
	};
}

auto operator/(const FSym& rhs, const FSym& lhs) ->FSym {
	 const auto df = {(rhs.value() * lhs.dot() -  lhs.value() * rhs.dot())/std::pow(rhs.value(), 2)};
	 return {lhs.value()/rhs.value(), df};
}


}
