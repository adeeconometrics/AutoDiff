#ifndef __RSYMBOL_H__
#define __RSYMBOL_H__

#include <map>

namespace ad {

struct RSym {
public:
  RSym(const std::map<RSym, double> &t_sym, double t_num);
  RSym(double t_num);

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

}; // namespace ad

#endif // __RSYMBOL_H__