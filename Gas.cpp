#include "Gas.h"

Gas::Gas() : pressure(0), volume(0), temperature(0), nu(0) {}

Gas::Gas(vector<DrawableParticle> m) {
  molecules = m;
  R = 0;
  for (auto it = molecules.begin(); it != molecules.end(); it++)
    if (it->getR() > R)
      R = it->getR();
  R = 4 * R * R;
  nu = molecules.size() / 6.02; // NEED TO DECLARE N_A HERE
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
  for (unsigned int i = 0; i < molecules.size(); ++i)
    energy += molecules[i].getE();
}

void Gas::updateT() {
  temperature = energy / (nu * 8.31);
}

void Gas::live(double dt, sf::RenderWindow &w) {
  vector<unsigned int> collisions;
  collisions.resize(molecules.size());
  for (auto it = collisions.begin(); it != collisions.end(); it++)
    *it = molecules.size();
  vector<set<unsigned int>> area;
  area.resize(molecules.size());

  for (unsigned int i = 0; i < molecules.size(); i++) {
    if (collisions[i] < molecules.size()) {
      for (auto it = area[collisions[i]].begin();
           it != area[collisions[i]].end(); it++)
        if (*it != i && molecules[i].sqrho(molecules[*it]) <
                        (molecules[i].getR() + molecules[*it].getR()) * (molecules[i].getR() + molecules[*it].getR())) {
          molecules[i].collision(molecules[*it]);
        }
    } else {
      for (unsigned int j = i + 1; j < molecules.size(); j++)
        if (molecules[i].sqrho(molecules[j]) < R) {
          area[i].insert(j);
          if (molecules[i].sqrho(molecules[j]) <
              (molecules[i].getR() + molecules[j].getR()) * (molecules[i].getR() + molecules[j].getR())) {
            collisions[j] = i;
            molecules[i].collision(molecules[j]);
          }
        }
    }
    molecules[i].update(dt, w);
  }
}
