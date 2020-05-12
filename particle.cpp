#include "particle.h"

Particle::Particle() {}

Particle::Particle(double m, double r, double* _x, double* _v) :mass(m), radius(r), loc(_x[0], _x[1]), v(_v[0], _v[1]) {}

Particle::~Particle() {}

double Particle::getM() const {
  return mass;
}

double Particle::getR() const {
    return radius;
}

Vector2D Particle::getLoc() const {
  return loc;
}

Vector2D Particle::getV() const {
  return v;
}

void Particle::setLoc(const Vector2D &_loc) {
  loc = _loc;
}

void Particle::setV(const Vector2D &_v) {
  v = _v;
}

void Particle::move() {
    loc = loc + v;
}

double Particle::sqrho(Particle &p2) const {
  return (loc.getX() - p2.getLoc().getX())*(loc.getX() - p2.getLoc().getX()) + (loc.getY() - p2.getLoc().getY())*(loc.getY() - p2.getLoc().getY());
}

void Particle::collision(Particle &p2) {
  Vector2D Vc = (mass/(mass + p2.getM()))*v + (p2.getM()/(mass + p2.getM()))*p2.getV();
  double k = ( (p2.getV() - Vc).getX() )/( (v - Vc).getX() );
  double k1 = ( 2*k*p2.getM() + mass - p2.getM() )/( mass + p2.getM() );
  double k2 = ( 2*mass + (p2.getM() - mass)*k )/( mass + p2.getM() );
  v = k1*v + (1 - k1)*Vc;
  p2.setV(k2*v + (1 - k2)*Vc);
}
