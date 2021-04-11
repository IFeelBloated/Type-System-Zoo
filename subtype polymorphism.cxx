#include <memory>
#include <vector>
#include <iostream>

struct Messenger {
    virtual auto Print(std::string_view msg)->void = 0;
};

// A <: Messenger
struct A : Messenger {
    auto Print(std::string_view msg)->void override {
        std::cout << "A says " << msg << std::endl;
    }
};

// B <: Messenger
struct B : Messenger {
    auto Print(std::string_view msg)->void override {
        std::cout << "B says " << msg << std::endl;
    }
};

auto main()->int {
    auto x = std::vector<std::unique_ptr<Messenger>>{};
    x.emplace_back(new A{});
    x.emplace_back(new B{});
    for (auto& y : x)
        y->Print("hi");
}