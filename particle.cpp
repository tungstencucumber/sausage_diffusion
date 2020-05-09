Particle::Particle() {}

Particle::Particle(unsigned double m, double* _x, double* _v)
{
  mass = m;
  x[0] = _x[0];
  x[1] = _x[1];
  v[0] = _v[0];
  v[1] = _v[1];
}
