#include <concepts>
#include <iostream>

struct A {
    // overloading +: A -> A -> A
    auto operator+(A) const {
        return A{};
    }
};

struct B {};

// overloading f: A -> A
auto f(A) {
    std::cout << "f: A -> A" << std::endl;
    return A{};
}

// overloading f: B -> B
auto f(B) {
    std::cout << "f: B -> B" << std::endl;
    return B{};
}

auto main()->int {
    auto x = A{} + A{};
    auto y = f(A{});
    auto z = f(B{});

    static_assert(std::same_as<decltype(x), A>);
    static_assert(std::same_as<decltype(y), A>);
    static_assert(std::same_as<decltype(z), B>);
}