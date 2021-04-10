#include <concepts>

// Apply is of kind (* -> *) -> * -> *
template<template<typename> typename TypeConstructor, typename TypeArgument>
using Apply = TypeConstructor<TypeArgument>;

template<typename>
struct A{};

template<typename>
struct B{};

auto main()->int {
    using X = Apply<A, int>;
    using Y = Apply<B, double>;
    
    static_assert(std::same_as<X, A<int>>);
    static_assert(std::same_as<Y, B<double>>);
}