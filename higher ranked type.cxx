#include <tuple>
#include <iostream>

using namespace std::literals;

// PolymorphicEval: (∀ a. a -> a) -> ∀ ...b. b... -> Π b...
auto PolymorphicEval(auto f, auto ...x) {
    return std::tuple{ f(x)... };
}

auto main()->int {
    auto [x, y, z] = PolymorphicEval([](auto x) { return x + x; }, 21, 1.57, "ja"s);

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;
}