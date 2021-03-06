#include <tuple>
#include <array>
#include <iostream>

using namespace std::literals;

// PolymorphicTransform: [∀ a. [a] -> [a]] -> ∀ ...b. [b]... -> Π [b]...
auto PolymorphicTransform(auto f, auto ...x) {
    if constexpr (std::tuple_size_v<decltype(f)> == 0)
        return std::tuple{ x... };
    else
        return PolymorphicTransform(std::apply([](auto, auto ...p) { return std::tuple{ p... }; }, f), std::get<0>(f)(x)...);
}

auto main()->int {
    auto f = std::tuple{
        [](auto x) { for(auto& y : x) y += y; return x; },
        [](auto x) { std::reverse(x.begin(), x.end()); return x; }
    };

    auto [x, y, z] = PolymorphicTransform(f, std::array{ 1, 2, 3, 4 }, std::array{ 1.57, 3.2 }, std::array{ "ja"s, "bye"s });

    std::cout << "x: "; for (auto w : x) std::cout << w << " "; std::cout << std::endl;
    std::cout << "y: "; for (auto w : y) std::cout << w << " "; std::cout << std::endl;
    std::cout << "z: "; for (auto w : z) std::cout << w << " "; std::cout << std::endl;
}