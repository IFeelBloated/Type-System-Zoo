#include <concepts>
#include <iostream>

// invoke: ∀ a. a -> type F a
auto invoke(auto f) {
    // assert a: ∃ b. int -> string -> b ⊢ type F a = b
    if constexpr (requires { f(0, ""); })
        return f(42, "oops");
    // assert a: ∃ c. int -> c ⊢ type F a = c
    else if constexpr (requires { f(0); })
        return f(42);
}

auto main()->int {
    auto x = invoke([](auto x, auto y) { 
        std::cout << "invoked with " << x << ", " << y << std::endl;
        return 10;
    });
    auto y = invoke([](auto x) { 
        std::cout << "invoked with " << x << std::endl;
        return 2.71;
    });

    static_assert(std::same_as<decltype(x), int>);
    static_assert(std::same_as<decltype(y), double>);
}