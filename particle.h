#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector2D.h"

class Particle
{
protected:
  double mass; // daltons
  double radius; // angstrom
  Vector2D loc; // m
  Vector2D v; //10^2 m/s
public:
  Particle();
  Particle(double m, double* _x, double* _v);
  ~Particle();
  double getM() const;
  double getR() const;
  Vector2D getLoc() const;
  Vector2D getV() const;
  void setLoc(const Vector2D &_loc);
  void setV(const Vector2D &_V);
  void move();

  double sqrho(Particle &p2) const; // return distance between two particles SQUARED (for the sake of runtime economy)
  void collision(Particle &p2);
};

#endif
