#include <concepts>
#include <iostream>

using namespace std::literals;

// B: real -> *
// B x = int if x >= 42 else string
//
// f: real[x] -> B x
template<auto x>
auto f() {
    if constexpr (x >= 42)
        return 42;
    else
        return "oops"s;
}

auto main()->int {
    auto x = f<10>();
    auto y = f<42>();

    static_assert(std::same_as<decltype(x), std::string>);
    static_assert(std::same_as<decltype(y), int>);

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
}