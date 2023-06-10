#ifndef __FYSMBOL_H__
#define __FYSMBOL_H__

namespace ad{

struct FSym {
public: 
	FSym(double t_value, double t_dot);
	FSym(double t_value);


	auto value() const noexcept -> double;
	auto dot() const noexcept -> double;

	auto operator<(const FSym &other) const noexcept ->bool;
	auto operator>(const FSym &other) const noexcept ->bool;
	auto operator==(const FSym &other) const noexcept ->bool;
	auto operator!=(const FSym &other) const noexcept ->bool;

private:
	double m_value;
	double m_dot;
};


auto operator+(const FSym& rhs, const FSym& lhs) -> FSym;
auto operator-(const FSym& rhs, const FSym& lhs) -> FSym;
auto operator*(const FSym& rhs, const FSym& lhs) -> FSym;
auto operator/(const FSym& rhs, const FSym& lhs) -> FSym;

};


#endif // __FYSMBOL_H__
