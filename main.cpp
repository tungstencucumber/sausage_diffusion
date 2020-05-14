#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <SFML/graphics.hpp>
#include "Gas.h"
#include <random>
#include <chrono>

int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution<int> d(min, max);
    return d(e);
}


using namespace std;

int main() {
    double r[] = {3, 5, 7}, m[] = {10, 20, 30}, dt = 0.01;
    unsigned int n = 1000;

    vector<DrawableParticle> particles;
    particles.reserve(n);

    for (unsigned int i = 0; i < n; i++) {
        double x = (double) rand_uns(10, 790);
        double y = (double) rand_uns(10, 790);
        double vx = (double) rand_uns(0, 20) - 10;
        double vy = (double) rand_uns(0, 20) - 10;
        Vector2D loc(x, y);
        Vector2D v(vx, vy);
        particles.push_back(DrawableParticle(m[i % 3], r[i % 3], loc, v));
        particles[i].fill(255 * (i % 3 / 2), 255 * (i % 3 % 2), 255 * ((i + 2) % 3 / 2));
    }
    Gas g(particles);

    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Standard");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        g.live(dt, window);
        window.display();
    }
    return 0;
}
