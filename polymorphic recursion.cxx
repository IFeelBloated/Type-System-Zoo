#include <concepts>
#include <iostream>
#include <sstream>

// technically, you could use a fold expression here
// but we'll spell out the recursion explicitly
// for the sake of demonstrating polymorphic recursion
//
// FuseIntoString: ∀ Show ...a. a... -> string
auto FuseIntoString(auto x, auto ...p) requires requires { std::ostringstream{} << x; } {
    auto y = std::ostringstream{};
    y << x << " ";
    if constexpr (sizeof...(p) != 0)
        y << FuseIntoString(p...);
    return y.str();
}

auto main()->int {
    auto x = FuseIntoString(0, "is zero", "π is approximately", 3.14);

    static_assert(std::same_as<decltype(x), std::string>);

    std::cout << x;
}