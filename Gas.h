#ifndef GAS_H
#define GAS_H

#include <vector>
#include "Particle.h"

class Gas
{
protected:
  vector<DrawableParticle> molecules;
  double pressure;
  double volume;
  double temperature;
  double moles;
public:
  Gas();
  Gas(vector<DrawableParticle> m);
  ~Gas();

  void live(double dt);

}

#endif
