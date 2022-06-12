#include <iostream>
#include "autodiff.h"

auto main(void) -> int {
  using namespace ad;

  Symbol a{1.1};
  Symbol b{0.5};

  // auto y = sech(a) * cosh(a*b) * coth(a-b) *pow(a, b);
  // auto y = sin(a) * cos(a * b) * tan(a - b) * pow(a, b);
  auto y = sin(a*b)/cos(b)*pow(a,b);
  auto df = gradient(y);
  auto df_d2a = gradient(df[a]);


  // std::cout << "d value: " << std::setprecision(20) << y.value() << '\n';
  // std::cout << "df/da: " << std::setprecision(20) << df[a] << '\n';
  std::cout << "df/db: " << std::setprecision(20) << df_d2a[a] << '\n';
}
