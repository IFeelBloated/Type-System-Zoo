#include <concepts>

template<typename T>
struct A {
    // instance ∀ Eq a. Eq A a = { _ == _ = true  }
    auto operator==(std::same_as<A> auto) const requires std::equality_comparable<T> {
        return true;
    }
};

struct B {};

auto main()->int {
    static_assert(std::equality_comparable<A<int>> == true);
    static_assert(std::equality_comparable<A<B>> == false);
}