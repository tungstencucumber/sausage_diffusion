#include "DrawableParticle.h"

DrawableParticle::DrawableParticle(double m, double r, Vector2D &_x, Vector2D &_v) : Particle(m, r, _x, _v),
                                                                                     Circle(Vector2D(_x), r) {}


void DrawableParticle::update(double dt, sf::RenderWindow &w) {
    if (loc.getX() < r || loc.getX() > (double) w.getSize().x - r) {
        v.setX(-v.getX());
        if (loc.getX() < r)
            loc.setX(r);
        else loc.setX(double(w.getSize().x - r));
    }
    if (loc.getY() < r || loc.getY() > (double) w.getSize().y - r) {
        v.setY(-v.getY());
        if (loc.getY() < r)
            loc.setY(r);
        else loc.setY(double(w.getSize().y - r));
    }
    move(dt);
    setLoc(loc);
    display(w);
}

void DrawableParticle::setLoc(const Vector2D &_loc) {
    Particle::setLoc(_loc);
    Circle::setLoc(loc);
}