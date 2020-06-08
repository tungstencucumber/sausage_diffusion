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
    double r[] = {5, 7}, m[] = {10, 20}, dt = 0.01;
    int w = 1600, vmax = 800;
    unsigned int n = 500;

    vector<DrawableParticle> particles1;
    particles1.reserve(n);
    vector<DrawableParticle> particles2;
    particles2.reserve(n);

    for (unsigned int i = 0; i < n; i++) {
        double x = (double) (rand_uns(0, w) % 800);
        double y = (double) (rand_uns(0, w) % 1000);
        double vx = (double) (rand_uns(0, w) % (2 * vmax) - vmax);
        double vy = (double) (rand_uns(0, w) % (2 * vmax) - vmax);
        Vector2D loc(x, y);
        Vector2D v(vx, vy);
        particles1.push_back(DrawableParticle(m[0], r[0], loc, v));
        particles1[i].fill(255, 0, 0);
    }
    for (unsigned int i = 0; i < n; i++) {
        double x = (double) (rand_uns(0, w) % 800 + 800);
        double y = (double) (rand_uns(0, w) % 1000);
        double vx = (double) (rand_uns(0, w) % (2 * vmax) - vmax);
        double vy = (double) (rand_uns(0, w) % (2 * vmax) - vmax);
        Vector2D loc(x, y);
        Vector2D v(vx, vy);
        particles2.push_back(DrawableParticle(m[1], r[1], loc, v));
        particles2[i].fill(0, 0, 255);
    }
    Gas f(particles1);
    Gas g(particles2);

    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Standard");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        live(f, g, dt, window);
        window.display();
    }
    return 0;
}
