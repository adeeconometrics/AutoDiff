#include "Symbol.h"

#include <iostream>

using namespace ad;

int main(void) {
    Symbol a{-4.0f}, b{2.0f};
    Symbol c =  a + b;

    std::cout << "hello world!";
}