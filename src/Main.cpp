#include "Symbol.h"

#include <iostream>

using namespace ad;
int main(void) {
    Symbol a{-4.0f}, b{2.0f};
    auto c = a + b;
    auto d = a*b + ad::pow(a,3);
    
    std::cout << "value: " << a.value() << " grad: " << a.gradient();
}