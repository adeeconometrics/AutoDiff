#ifndef __FSYMBOL_H__
#define __FSYMBOL_H__

namespace ad {

struct FSym {
public:
  FSym(double t_value, double t_dot);
  FSym(double t_value);

  auto value() const noexcept -> double;
  auto dot() const noexcept -> double;
  auto df(int t_index) const noexcept -> double;

  auto operator<(const FSym &other) const noexcept -> bool;
  auto operator>(const FSym &other) const noexcept -> bool;
  auto operator==(const FSym &other) const noexcept -> bool;
  auto operator!=(const FSym &other) const noexcept -> bool;

private:
  double m_value;
  double m_dot;
};

auto operator+(const FSym &lhs, const FSym &rhs) -> FSym;
auto operator-(const FSym &lhs, const FSym &rhs) -> FSym;
auto operator*(const FSym &lhs, const FSym &rhs) -> FSym;
auto operator/(const FSym &lhs, const FSym &rhs) -> FSym;

}; // namespace ad

#endif // __FSYMBOL_H__
