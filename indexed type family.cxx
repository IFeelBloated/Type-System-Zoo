#include <concepts>
#include <string>
#include <vector>

using namespace std::literals;

// class C a = { type G a, g: a -> G a }
//
// F: * -> *
// ∀ C a. F a = [G a]
// F _ = int
//
// f: ∀ a. a -> F a
auto f(auto x) {
    if constexpr (requires { x.g(); })
        return std::vector{ x.g() };
    else
        return 42;
}

// instance C A = { type G A = double, g _ = 2.71 }
struct A {
    auto g() {
        return 2.71;
    }
};

// instance C B = { type G B = string, g _ = "oops" }
struct B {
    auto g() {
        return "oops"s;
    }
};

struct C {};

auto main()->int {
    auto x = f(A{});
    auto y = f(B{});
    auto z = f(C{});

    static_assert(std::same_as<decltype(x), std::vector<double>>);
    static_assert(std::same_as<decltype(y), std::vector<std::string>>);
    static_assert(std::same_as<decltype(z), int>);
}