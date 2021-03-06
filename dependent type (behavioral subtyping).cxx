// NoLessThan: nat -> *
// NoLessThan x = ⊤ ∩ NoLessThan x - 1 ⊢ NoLessThan x <: NoLessThan x - 1
// NoLessThan 0 = ⊤
template<auto x>
struct NoLessThan : NoLessThan<x - 1> {};

template<>
struct NoLessThan<0> {};

auto f(NoLessThan<42>) {}

auto main()->int {
    f(NoLessThan<64>{});
    f(NoLessThan<42>{});

    // f(NoLessThan<10>{}); <- type level failure
}