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

double Particle::getE() const {
  return mass*(v.getX()*v.getX() + v.getY()*v.getY())/2;
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

double Particle::sqrho(Particle &p2) const {
  return (loc.getX() - p2.getLoc().getX())*(loc.getX() - p2.getLoc().getX()) + (loc.getY() - p2.getLoc().getY())*(loc.getY() - p2.getLoc().getY());
}

void Particle::collision(Particle &p2) {
  Vector2D dist = p2.getLoc() - loc;
  Vector2D v1 = (v*dist)/(dist.getX()*dist.getX() + dist.getY()*dist.getY()) * dist;
  Vector2D v2 = (p2.getV()*dist)/(dist.getX()*dist.getX() + dist.getY()*dist.getY()) * dist;
  v = v - v1;
  p2.setV(p2.getV() - v2);
  double k = v2.getX()/v1.getX();
  double k1 = (2*k*p2.getM() + mass - p2.getM())/(mass + p2.getM() );
  double k2 = (2*mass + (p2.getM() - mass)*k)/(mass + p2.getM());
  v = v + k1*v1;
  p2.setV(p2.getV() + k2*v1);
}

void Particle::move(double dt) {
    loc = loc + v*dt;
}
