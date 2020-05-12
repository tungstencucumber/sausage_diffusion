#include "Gas.h"

Gas::Gas(): pressure(0), volume(0), temperature(0), nu(0) {}

Gas::Gas(vector<DrawableParticle> m) {
  molecules = m;
  nu = molecules.size()/6.02; // NEED TO DECLARE N_A HERE
  updateU();
  updateT();
  volume = 0;
}

Gas::~Gas() {}

double Gas::getP() const {
  return pressure;
}

double Gas::getV() const {
  return volume;
}

double Gas::getT() const {
  return temperature;
}

double Gas::getNu() const {
  return nu;
}

double Gas::getU() const {
  return energy;
}

void Gas::updateU() {
  energy = 0;
  for(unsigned int i = 0; i < molecules.size(); ++i)
    energy += molecules[i].getE();
}

void Gas::updateT() {
  temperature = energy/(nu * 8.31);
}

void Gas::live(double dt) {
  for (unsigned int i = 0; i < molecules.size(); i++) {
    molecules[i].setLoc(molecules[i].getLoc() + molecules[i].getV() * dt);
  }
  for(unsigned int i = 0; i < molecules.size(); i++)
    for(unsigned int j = i; j < molecules.size(); j++) {
      if(i == j)
        continue;
      if(molecules[i].sqrho(molecules[j]) <= (molecules[i].getR() + molecules[j].getR())*(molecules[i].getR() + molecules[j].getR()) ) {
        molecules[i].collision(molecules[j]);
        molecules[j].setLoc(molecules[j].getLoc() + molecules[j].getLoc() - molecules[i].getLoc() );
      }
    }
}
