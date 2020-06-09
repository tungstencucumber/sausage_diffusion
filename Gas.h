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
  double v; // average absolute velocity
  unsigned int C = 50; // number of volume sections made by division of general volume
  double* N; // number of molecules in this volume section
  double* n; // current concentration
  double* n0; // concentration one step ago
  double* dN; // number of molecules crossed transverse sections
  double* j; // particle stream density
  double* l; //mean free path
  double* Dt; //diffusion factor theoretical
  double* Dc; //diffusion factor calculated
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
