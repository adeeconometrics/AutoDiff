#include "../include/fsymbol.hpp"
#include "../include/rsymbol.hpp"

#include <iostream>

using namespace ad;
using std::cout;

// auto tf(double x, double y) -> FSym {
//   FSym a {}
// }

auto main() -> int {

  RSym a{1.1};
  RSym b{0.5};

  FSym fa{1.1};
  FSym fb{0.5};

  const auto f = fb * fa + fa * fb;

  auto expr = a / b + b * a;
  auto df_expr = gradient(expr);

  cout << df_expr[a] << '\n' << df_expr[b] << "\n\n";
  cout << f.dot();

#ifdef DEBUG
  cout << "DEBUG\n";
#endif

  return 0;
}