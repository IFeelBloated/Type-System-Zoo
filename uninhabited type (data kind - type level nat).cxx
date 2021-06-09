#include <concepts>

using Zero = struct {};

template<typename>
struct Succ {};

template<typename>
constexpr auto IsNat = false;

template<>
constexpr auto IsNat<Zero> = true;

template<typename x>
constexpr auto IsNat<Succ<x>> = IsNat<x>;

// kind Nat = Zero | Succ Nat
template<typename x>
concept Nat = IsNat<x>;

template<Nat, Nat>
struct AddFunc {};

// Add: Nat -> Nat -> Nat
// Add Zero y = y
// Add (Succ x) y = Succ (Add x y)
template<Nat x, Nat y>
using Add = AddFunc<x, y>::Result;

template<Nat y>
struct AddFunc<Zero, y> {
    using Result = y;
};

template<Nat x, Nat y>
struct AddFunc<Succ<x>, y> {
    using Result = Succ<Add<x, y>>;
};

auto main()->int {
    using One = Succ<Zero>;
    using Two = Succ<Succ<Zero>>;
    using Three = Succ<Succ<Succ<Zero>>>;

    using x = Add<One, One>;
    using y = Succ<x>;

    static_assert(Nat<Three>);
    static_assert(Nat<x>);
    static_assert(Nat<double> == false);
    static_assert(Nat<Succ<void>> == false);

    static_assert(std::same_as<x, Two>);
    static_assert(std::same_as<y, Three>);
    static_assert(std::same_as<Add<One, Two>, Three>);
}