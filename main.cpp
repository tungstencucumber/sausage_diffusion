#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/graphics.hpp>
#include "DrawableParticle.h"

using namespace std;

int main() {
    double loc1[] = {50, 400};
    double loc2[] = {750, 450};
    double v1[] = {20, 0};
    double v2[] = {-10, 0};
    double dt = 0.01;
    DrawableParticle part1(1, 50, loc1, v1);
    DrawableParticle part2(1, 50, loc2, v2);
    part1.fill(255, 0, 0);
    part2.fill(0, 0, 255);

    sf::RenderWindow window(sf::VideoMode(800, 800), "Example");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (part1.sqrho(part2) < (part1.getR() + part2.getR()) * (part1.getR() + part2.getR())) {
            part1.collision(part2);
            //window.close();
        }
        window.clear();
        part1.update(dt, window);
        part2.update(dt, window);
        window.display();
    }
    return 0;
}


/*Здесь я напишу пример цикла, как вижу его
    vector<DrawableParticle> particles = ...
    vector<DrawableParticle>::iterator it1, it2;
    for (it1 = particles.begin(); it1 != particles.end(); it1++) {
        for(it2 = next(it1); it2 != particles.end(); it2++)
            if (it1->sqrho(*it2) < (it1->getR() + it2->getR())*(it1->getR() + it2->getR()))
                it1->collision(*it2);
    it1->move();
    }
*/
