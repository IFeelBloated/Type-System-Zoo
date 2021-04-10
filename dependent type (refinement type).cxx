// f: real[x|x >= 42] -> void
template<auto x>
auto f() requires (x >= 42) {}

auto main()->int {
    f<42>();
    // f<10>(); <- type level failure
}