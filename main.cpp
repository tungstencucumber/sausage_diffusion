#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <SFML/graphics.hpp>
#include "DrawableParticle.h"
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
    double r[] = {3, 5}, m[] = {10, 20}, dt = 0.1;
    double rmax = 9 * r[1] * r[1];
    unsigned int n = 5000;

    vector<DrawableParticle> particles;
    particles.reserve(n);
    vector<unsigned int> collisions;
    collisions.resize(n);
    vector<set<unsigned int>> area;
    area.resize(n);

    for (unsigned int i = 0; i < n; i++) {
        double x = (double) rand_uns(10, 790);
        double y = (double) rand_uns(10, 790);
        double vx = (double) rand_uns(0, 20) - 10;
        double vy = (double) rand_uns(0, 20) - 10;
        Vector2D loc(x, y);
        Vector2D v(vx, vy);
        particles.push_back(DrawableParticle(m[i % 2], r[i % 2], loc, v));
        particles[i].fill(0, 255 * (i % 2), 255 * ((i + 1) % 2));
        collisions[i] = n;
    }

    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Standard");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (unsigned int i = 0; i < n - 1; i++) {
            if (collisions[i] < n) {
                for (auto it = area[collisions[i]].begin();
                     it != area[collisions[i]].end(); it++)
                    if (*it != i && particles[i].sqrho(particles[*it]) < (particles[i].getR() + particles[*it].getR()) *
                                                                         (particles[i].getR() +
                                                                          particles[*it].getR())) {
                        particles[i].collision(particles[*it]);
                    }
            } else {
            for (unsigned int j = i + 1; j < n; j++)
                if (particles[i].sqrho(particles[j]) < rmax) {
                    area[i].insert(j);
                    if (particles[i].sqrho(particles[j]) < (particles[i].getR() + particles[j].getR()) *
                                                           (particles[i].getR() + particles[j].getR())) {
                        collisions[j] = i;
                        particles[i].collision(particles[j]);
                    }
                }
            }
            particles[i].update(dt, window);
        }
        particles[n - 1].update(dt, window);
        window.display();
        for (unsigned int i = 0; i < n; i++) {
            collisions[i] = n;
            area[i].clear();
        }
    }

    return 0;
}
