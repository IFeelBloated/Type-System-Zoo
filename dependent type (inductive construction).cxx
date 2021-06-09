#include <concepts>

using Zero = struct {};

template<typename>
struct Succ {};

template<auto x>
auto NatConstructor() {
    if constexpr (x == 0)
        return Zero{};
    else
        return Succ<decltype(NatConstructor<x - 1>())>{};
}

// Nat: nat -> *
// Nat 0 = Zero
// Nat x = Succ (Nat x - 1)
template<auto x>
using Nat = decltype(NatConstructor<x>());

auto main()->int {
    using One = Succ<Zero>;
    using Two = Succ<Succ<Zero>>;
    using Three = Succ<Succ<Succ<Zero>>>;

    using x = Nat<1>;
    using y = Nat<2>;
    using z = Nat<3>;
    using w = Nat<0>;

    static_assert(std::same_as<w, Zero>);
    static_assert(std::same_as<x, One>);
    static_assert(std::same_as<y, Two>);
    static_assert(std::same_as<z, Three>);
}