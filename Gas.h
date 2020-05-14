#ifndef GAS_H
#define GAS_H

#include <vector>
#include <set>
#include "DrawableParticle.h"

using namespace std;

class Gas
{
protected:
  vector<DrawableParticle> molecules;
  double pressure;
  double volume;
  double temperature;
  double nu;
  double energy;
  double R;
public:
  Gas();
  Gas(vector<DrawableParticle> m);
  ~Gas();

  double getP() const;
  double getV() const;
  double getT() const;
  double getU() const;
  double getNu() const;

  void updateU();
  void updateT();
  void friend live(Gas &f, Gas &g, double dt, sf::RenderWindow &w);
};

void live(Gas &f, Gas &g, double dt, sf::RenderWindow &w);

#endif
