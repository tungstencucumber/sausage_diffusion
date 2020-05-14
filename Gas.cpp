#include "Gas.h"

Gas::Gas() : pressure(0), volume(0), temperature(0), nu(0) {}

Gas::Gas(vector<DrawableParticle> m) {
  molecules = m;
  R = 0;
  for (auto it = molecules.begin(); it != molecules.end(); it++)
    if (it->getR() > R)
      R = it->getR();
  R = 4 * R * R;
  nu = molecules.size() / 6.02;
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

void live(Gas &f, Gas&g, double dt, sf::RenderWindow &w) {
  vector<DrawableParticle*> all_mols;
  for(unsigned int i = 0; i < f.molecules.size(); ++i)
    all_mols.push_back(&f.molecules[i]);
  for(unsigned int i = 0; i < g.molecules.size(); ++i)
    all_mols.push_back(&g.molecules[i]);

  vector<unsigned int> collisions;
  collisions.resize(all_mols.size());
  for (auto it = collisions.begin(); it != collisions.end(); it++)
    *it = all_mols.size();
  vector<set<unsigned int>> area;
  area.resize(all_mols.size());

  for (unsigned int i = 0; i < all_mols.size(); i++) {
    if (collisions[i] < all_mols.size()) {
      for (auto it = area[collisions[i]].begin();
           it != area[collisions[i]].end(); it++)
        if (*it != i && all_mols[i]->sqrho(*all_mols[*it]) <
                        (all_mols[i]->getR() + all_mols[*it]->getR()) * (all_mols[i]->getR() + all_mols[*it]->getR())) {
          all_mols[i]->collision(*all_mols[*it]);
        }
    } else {
      for (unsigned int j = i + 1; j < all_mols.size(); j++)
        if (all_mols[i]->sqrho(*all_mols[j]) < f.R || all_mols[i]->sqrho(*all_mols[j]) < g.R ) {
          area[i].insert(j);
          if (all_mols[i]->sqrho(*all_mols[j]) <
              (all_mols[i]->getR() + all_mols[j]->getR()) * (all_mols[i]->getR() + all_mols[j]->getR())) {
            collisions[j] = i;
            all_mols[i]->collision(*all_mols[j]);
          }
        }
    }
    all_mols[i]->update(dt, w);
  }
}
