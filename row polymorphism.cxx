#include <concepts>
#include <iostream>

template<typename T>
concept Real = std::integral<std::decay_t<T>> || std::floating_point<std::decay_t<T>>;

template<typename T, typename U>
concept SameAs = std::same_as<std::decay_t<T>, std::decay_t<U>>;

using Vec2D = struct { double x; double y; };
using iVec3D = struct { int x; int y; int z; };

auto TransposeXY(auto Vec) requires requires {
    { Vec.x }->Real;
    { Vec.y }->SameAs<decltype(Vec.x)>;
} {
    std::swap(Vec.x, Vec.y);
    return Vec;
}

auto main()->int {
    auto v1 = TransposeXY(Vec2D{ .x = 2.71, .y = 3.14 });
    auto v2 = TransposeXY(iVec3D{ .x = 42, .y = 13, .z = 7 });

    std::cout << "v1: x = " << v1.x << ", y = " << v1.y << std::endl;
    std::cout << "v2: x = " << v2.x << ", y = " << v2.y << ", z = " << v2.z << std::endl;
}