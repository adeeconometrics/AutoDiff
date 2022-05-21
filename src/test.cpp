#include <type_traits>
#include <concepts>
#include <iostream>

template <typename T>
concept number = std::is_arithmetic_v<T>;

template <typename T>
requires number<T>
auto f(T a)  -> void {
    std::cout << "this function runs! \n";
}


int main(void) {
    f(3);
}