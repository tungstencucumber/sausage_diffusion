#include "Circle.h"

//v - положение круга, r - радиус
Circle::Circle(const Vector2D &loc, double _r) : shape(_r) {
    r = _r;
    shape.setPosition(loc.getX() - r, loc.getY() - r);
}

void Circle::display(sf::RenderWindow &w) const {
    w.draw(shape);
}

void Circle::fill(int r, int g, int b) {
    shape.setFillColor(sf::Color(r, g, b));
}

void Circle::setLoc(const Vector2D &loc) {
    shape.setPosition(loc.getX() - r, loc.getY() - r);
}