template<auto, auto>                                         
struct ADLType {
    friend consteval auto ADLFunc(ADLType, auto...);
};

template<auto InstanceIdentifier, auto x>
struct InjectDefinitionForADLFunc {
    friend consteval auto ADLFunc(ADLType<InstanceIdentifier, x>, auto...) { return 42; }
};

template<auto InstanceIdentifier, auto x = 0>
constexpr auto ExtractThenUpdateCurrentState(auto...)->decltype(x) {
    InjectDefinitionForADLFunc<InstanceIdentifier, x>{};
    return x;
}

template<auto InstanceIdentifier, auto x = 0, auto = ADLFunc(ADLType<InstanceIdentifier, x>{})>
constexpr auto ExtractThenUpdateCurrentState() {
    return ExtractThenUpdateCurrentState<InstanceIdentifier, x + 1>();
}

template<auto InstanceIdentifier = []{}>
struct AffineType {
    template<auto x = ExtractThenUpdateCurrentState<InstanceIdentifier>()>
    auto Use() requires (x == 0) {}
};

auto main()->int {
    auto x = AffineType{};
    auto y = AffineType{};
    x.Use();
    y.Use();
    // x.Use(); <- type level failure
}