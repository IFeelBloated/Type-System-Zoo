#include <iostream>

using namespace std::literals;

struct A {
    // coercion: A >-> string
    operator auto() {
        return "A"s;
    }
};

struct B {
    // coercion: B >-> string
    operator auto() {
        return "B"s;
    }
};

auto Print(std::string msg) {
    std::cout << msg << std::endl;
}

auto main()->int {
    Print("oops");
    Print(A{});
    Print(B{});
}