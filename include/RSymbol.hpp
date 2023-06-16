#ifndef __RSYMBOL_H__
#define __RSYMBOL_H__

#include <map>

namespace ad {

struct RSym {
public:
  RSym(const std::map<RSym, double> &t_loc_grad, double t_value);
  RSym(double t_value);

  auto value() const noexcept -> double;
  auto local_gradient() const noexcept -> std::map<RSym, double>;

  auto operator<(const RSym &other) const noexcept -> bool;
  auto operator>(const RSym &other) const noexcept -> bool;
  auto operator==(const RSym &other) const noexcept -> bool;
  auto operator!=(const RSym &other) const noexcept -> bool;

private:
  std::map<RSym, double> m_local_grad;
  double m_value;
};

auto operator+(const RSym &lhs, const RSym &rhs) -> RSym;
auto operator-(const RSym &lhs, const RSym &rhs) -> RSym;
auto operator*(const RSym &lhs, const RSym &rhs) -> RSym;
auto operator/(const RSym &lhs, const RSym &rhs) -> RSym;

auto gradient(const RSym &other) -> std::map<RSym, double>;

}; // namespace ad

#endif // __RSYMBOL_H__