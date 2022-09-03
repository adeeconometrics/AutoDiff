#include "../include/Symbol.hpp"

#include <iostream>

using namespace ad;

auto test_vector_functions() -> void;
auto test_scalar_functions() -> void;

auto test_vector_fsym() -> void;
auto test_scalar_fsym() -> void;

auto test_vector_rsym() -> void;
auto test_scalar_rsym() -> void;

auto main(void) -> int {
  Symbol a{-4.0f}, b{2.0f};
  Symbol c = a + b;
}