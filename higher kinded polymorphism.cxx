#include <concepts>
#include <vector>
#include <list>
#include <string>
#include <iostream>

template<typename, typename>
struct ReplaceTypeArgument {};

// ReplaceTypeArgument: (* -> *) -> * -> * -> *
template<template<typename> typename TypeConstructor, typename T, typename U>
struct ReplaceTypeArgument<TypeConstructor<T>, U> {
    using Type = TypeConstructor<U>;
};

// fmap: ∀ f a b. (a -> b) -> f a -> f b
auto fmap(auto f, auto x) requires requires {
    { std::next(x.begin()) }->std::same_as<decltype(x.end())>;
    x.push_back(*x.begin());
} {
    using ElementType = std::decay_t<decltype(*x.begin())>;
    using NewContainerType = ReplaceTypeArgument<decltype(x), decltype(f(ElementType{}))>::Type;
    auto z = NewContainerType{};
    for (auto y : x)
        z.push_back(f(y));
    return z;
}

auto main()->int {
    auto x = fmap([](auto x) { return x * 0.5; }, std::vector{ 1, 2, 3, 4 });
    auto y = fmap([](auto x) { return std::to_string(x) + " says hi"; }, std::list{ 42, 10 });

    static_assert(std::same_as<decltype(x), std::vector<double>>);
    static_assert(std::same_as<decltype(y), std::list<std::string>>);

    std::cout << "x: "; for (auto w : x) std::cout << w << " "; std::cout << std::endl;
    std::cout << "y: "; for (auto w : y) std::cout << w << " "; std::cout << std::endl;
}