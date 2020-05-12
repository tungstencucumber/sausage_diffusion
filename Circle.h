#ifndef PRIMITIVES_CIRCLE_H
#define PRIMITIVES_CIRCLE_H

#include "Vector2D.h"
#include <SFML/graphics.hpp>

class Circle {
protected:
    sf::CircleShape shape;
    double r;
public:
    Circle(const Vector2D &loc, double _r);

    void display(sf::RenderWindow &w) const;

    void fill(int r, int g, int b);

    void setLoc(const Vector2D &loc);
};


#endif //PRIMITIVES_CIRCLE_H
