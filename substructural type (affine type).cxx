template<auto, auto>                                         
struct ADLType {
    friend consteval auto ADLFunc(ADLType, auto...);
};

template<auto InstanceIdentifier, auto x>
struct InjectDefinitionForADLFunc {
    friend consteval auto ADLFunc(ADLType<InstanceIdentifier, x>, auto...) {}
};

template<auto InstanceIdentifier, auto x = 0, auto = []{}>
constexpr auto ExtractThenUpdateCurrentState()->decltype(x) {
    if constexpr (requires { ADLFunc(ADLType<InstanceIdentifier, x>{}); })
        return ExtractThenUpdateCurrentState<InstanceIdentifier, x + 1>();
    else 
        InjectDefinitionForADLFunc<InstanceIdentifier, x>{};
    return x;
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