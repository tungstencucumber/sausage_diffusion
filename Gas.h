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
  unsigned int C = 10; // number of volume sections made by division of general volume
  double N[C]; // number of molecules in this volume section
  double n[C]; // current concentration
  double n0[C]; // concentration one step ago
  double dN[C-1]; // number of molecules crossed transverse sections
  double j[C-1]; // particle stream density
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
