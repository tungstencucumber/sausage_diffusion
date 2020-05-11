#include "particle.h"

Particle::Particle() {}

Particle::Particle(double m, double* _x, double* _v) :mass(m), loc(_x[0], _x[1]), v(_v[0], _v[1]) {}
