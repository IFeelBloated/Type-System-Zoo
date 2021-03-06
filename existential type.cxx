#include <functional>
#include <vector>
#include <iostream>

// type Messenger = ∃ a. { x: a, Print: a -> string -> ⊥ }
struct Messenger {
    using QuantificationBound = auto(std::string_view)->void;
    std::function<QuantificationBound> f = {};

    Messenger() = default;
    Messenger(auto x) {
        f = [=](auto msg) { x.Print(msg); };
    }

    auto Print(auto msg) const {
        f(msg);
    }
};

struct A {
    auto Print(auto msg) const {
        std::cout << "A says " << msg << std::endl;
    }
};

struct B {
    auto Print(auto msg) const {
        std::cout << "B says " << msg << std::endl;
    }
};

auto main()->int {
    auto x = std::vector<Messenger>{ A{}, B{} };
    for (auto y : x)
        y.Print("hi");
}