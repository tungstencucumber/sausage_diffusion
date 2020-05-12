#include "DrawableParticle.h"

DrawableParticle::DrawableParticle(double m, double r, Vector2D &_x, Vector2D &_v) : Particle(m, r, _x, _v),
                                                                                 Circle(Vector2D(_x), r) {}


void DrawableParticle::update(double dt, sf::RenderWindow &w) {
    move(dt);
    setLoc(loc);
    display(w);
    if (loc.getX() < r || loc.getX() > (double)w.getSize().x - r)
        v.setX(-v.getX());
    if (loc.getY() < r || loc.getY() > (double)w.getSize().y - r)
        v.setY(-v.getY());
}

void DrawableParticle::setLoc(const Vector2D &_loc) {
    Particle::setLoc(_loc);
    Circle::setLoc(loc);
}