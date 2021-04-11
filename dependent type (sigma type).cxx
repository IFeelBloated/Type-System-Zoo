#include <concepts>
#include <string>

using namespace std::literals;

// Selector: real -> *
// Selector x = int if x >= 42 else string
template<typename T, auto x>
concept Selector = std::same_as<std::decay_t<T>, std::conditional_t<x >= 42, int, std::string>>;

// f: real[x] -> Selector x -> void
template<auto x>
auto f(Selector<x> auto) {}

auto main()->int {
    f<42>(42);
    f<10>("oops"s);

    // f<64>("lol"s); <- type level failure
}