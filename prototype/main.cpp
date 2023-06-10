#include "reverse_mode.h"

#include <iostream>
#include <iomanip>

using namespace ad;

auto test_trig(const Symbol& a, const Symbol& b) -> void {
  auto y = sin(a) * cos(a*b) * cot(a-b) *pow(a, b)/tan(a) * sec(b) - csc(b*a);
  auto df_y = gradient(y);

  std::cout << "df_y wrt a: " <<  std::setprecision(15) << df_y[a] << '\n'; 
  std::cout << "df_y wrt b: " <<  std::setprecision(15) << df_y[b] << '\n';
}

auto test_trigh(const Symbol& a, const Symbol& b) -> void {
  auto y = sinh(a) * cosh(a*b) * coth(a-b) *pow(a, b)/tanh(a) * sech(b) - csch(b*a);
  auto df_y = gradient(y);

  std::cout << "df_y wrt a: " <<  std::setprecision(15) << df_y[a] << '\n'; 
  std::cout << "df_y wrt b: " <<  std::setprecision(15) << df_y[b] << '\n';
}

auto test_atrig(const Symbol& a, const Symbol& b) -> void {
  auto y = asin(a) * acos(a*b) * acot(a-b) *pow(a, b)/atan(a) * asec(b) - acsc(b*a);
  auto df_y = gradient(y);

  std::cout << "df_y wrt a: " <<  std::setprecision(15) << df_y[a] << '\n'; 
  std::cout << "df_y wrt b: " <<  std::setprecision(15) << df_y[b] << '\n';
}

auto test_atrigh(const Symbol& a, const Symbol& b) -> void {
  auto y = asinh(a) * acosh(a*b) * acoth(a-b) *pow(a, b)/atanh(a) * asech(b) - acsch(b*a);
  auto df_y = gradient(y);

  std::cout << "df_y wrt a: " <<  std::setprecision(15) << df_y[a] << '\n'; 
  std::cout << "df_y wrt b: " <<  std::setprecision(15) << df_y[b] << '\n';
}

auto main(void) -> int {
  Symbol a{1.1};
  Symbol b{0.5};

  test_trig(a,b);
  std::cout << '\n';
  test_trigh(a,b);
  std::cout << '\n';
  test_atrig(a,b);
  std::cout << '\n';
  test_atrigh(a,b);

}
