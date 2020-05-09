#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
private:
  unsigned double mass; // daltons
  double* x; // m
  double* v; //10^2 m/s
public:
  Particle();
  Particle(unsigned double m, double* _x, double* _v);
  ~Particle();
  unsigned double getM();
  double* getX();
  double* getV();

  void collision(Particle p2);
};

#endif
