#include <iostream>

using Nat = unsigned int;

// leq : (a : Nat) -> (b : Nat) -> Set
template<Nat a, Nat b>
struct leq {
    consteval leq() requires ( a == 0 ) {}
    consteval leq(leq<a-1, b-1> = {}) requires ( a > 0 && b > 0 ) {}
};

// pair : (fst : Nat, scd : Nat)
template<Nat a, Nat b>
struct pair {
    constexpr static auto fst = a;
    constexpr static auto scd = b;
};

// ordered_pair : (fst : Nat, scd : Nat, proof : leq fst scd)
template<Nat a, Nat b, leq<a, b> p = leq<a, b>()>
struct ordered_pair : pair<a,b> {
    static constexpr auto proof = p;
};

// sort_pair : pair -> sorted_pair
consteval auto sort_pair(auto p) {
    if constexpr (p.fst < p.scd) {
        return ordered_pair<p.fst, p.scd>();
    } else {
        return ordered_pair<p.scd, p.fst>();
    }
}

int main() {
    constexpr auto sorted_pair = sort_pair(pair<8,6>());
    std::cout << sorted_pair.fst << ", " << sorted_pair.scd << "\n";
}
