#include "../include/rsymbol.hpp"

#include <iostream>

using namespace ad;
using std::cout;

auto main() -> int {

  RSym a{1.1};
  RSym b{0.5};

  auto expr = a / b + b * a;
  auto df_expr = gradient(expr);

  cout << df_expr[a] << '\n' << df_expr[b];

  return 0;
}