#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector2D.h"

class Particle
{
private:
  double mass; // daltons
  Vector2D loc; // m
  Vector2D v; //10^2 m/s
public:
  Particle();
  Particle(double m, double* _x, double* _v);
  ~Particle();
  double getM();
  double* getX();
  double* getV();

  void collision(Particle p2);
};

#endif
