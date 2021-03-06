#include <concepts>
#include <iostream>

using namespace std::literals;

// id: ∀ a. a -> a
auto id(auto x) {
    return x;
}

auto main()->int {
    auto x = id(42);
    auto y = id(2.71);
    auto z = id("oops"s);

    static_assert(std::same_as<decltype(x), int>);
    static_assert(std::same_as<decltype(y), double>);
    static_assert(std::same_as<decltype(z), std::string>);

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;
}