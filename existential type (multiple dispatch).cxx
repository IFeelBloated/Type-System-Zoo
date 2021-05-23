#include <iostream>
#include <functional>
#include <vector>

struct asteroid {};
struct spaceship {};

auto collide(asteroid, asteroid) {
    std::cout << "asteroid hitting asteroid\n";
}

auto collide(asteroid, spaceship) {
    std::cout << "asteroid hitting spaceship\n";
}

auto collide(spaceship, asteroid) {
    std::cout << "spaceship hitting asteroid\n";
}

auto collide(spaceship, spaceship) {
    std::cout << "spaceship hitting spaceship\n";
}

struct collider {
    using QuantificationBound = auto()->void;
    std::function<QuantificationBound> f = {};

    collider() = default;
    collider(auto x, auto y) {
        f = [=] { ::collide(x, y); };
    }

    auto collide() {
        f();
    }
};

auto main()->int {
    auto c = std::vector<collider>{
        { spaceship{}, spaceship{} },
        { asteroid{}, asteroid{} },
        { asteroid{}, spaceship{} },
        { spaceship{}, asteroid{} }
    };
    for (auto x : c)
        x.collide();
}