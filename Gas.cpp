#include "Gas.h"

Gas::Gas() : pressure(0), volume(0), temperature(0), nu(0) {}

Gas::Gas(vector<DrawableParticle> m) {
  molecules = m;
  R = 0;
  N = new double[C];
  n = new double[C];
  for (unsigned int i = 0; i < C; i++)
    n[i] = 0;
  n0 = new double[C];
  dN = new double[C];
  j = new double[C];
  l = new double[C];
  Dt = new double[C];
  Dc = new double[C];
  for (auto it = molecules.begin(); it != molecules.end(); it++)
    if (it->getR() > R)
      R = it->getR();
  R = 4 * R * R;
  nu = molecules.size() / 6.02;
  updateU();
  updateT();
  volume = 0;
}

Gas::~Gas() {
    delete[] N;
    delete[] n;
    delete[] n0;
    delete[] dN;
    delete[] j;
    delete[] l;
    delete[] Dt;
    delete[] Dc;
}

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

  for(unsigned int i = 0; i < f.C; i++) {
    f.n0[i] = f.n[i];
    f.n[i] = 0;
    f.N[i] = 0;
    f.dN[i] = 0;
    f.j[i] = 0;
    f.v = 0;

    g.n0[i] = g.n[i];
    g.n[i] = 0;
    g.N[i] = 0;
    g.dN[i] = 0;
    g.j[i] = 0;
    g.v = 0;
  }

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

    // checking if the particle is going to cross neighbour section
    double current = (all_mols[i]->getLoc().getX())*f.C/1600;
    double next = (all_mols[i]->getLoc().getX() + all_mols[i]->getV().getX()*dt)*f.C/1600;
    int d = 1;
    if (all_mols[i]->getV().getX() < 0)
        d = -1;
    for (unsigned int j = 0; j < f.C; j++) {
      if ((double) j < next && next < (double) j + 1 ) {
        if (i < f.molecules.size()) { // reporting that the particle is in this volume section now
            f.N[j] ++;
            f.v += all_mols[i]->getV().getLen();
        } else {
            g.N[j] ++;
            g.v += all_mols[i]->getV().getLen();
        }
        if ((current < j || j + 1 < current)) {
          if (i < f.molecules.size()) { //if particles belongs to f gas...
            f.dN[j] += d; // increment the value of molecules crossed this particular section
          } else { //else it belongs to g gas
            g.dN[j] += d; // and we do the same stuff
          }
        }
      }
    }

    all_mols[i]->update(dt, w); //moving particle
  }
  f.v = f.v/f.molecules.size()/1000;
  g.v = g.v/g.molecules.size()/1000;
  //recalculating concentrations and densities, assuming S = 1
  for(unsigned int i = 0; i < f.C; i++) {
    f.n[i] = f.N[i]/(1.6/f.C);
    f.j[i] = f.dN[i]/dt; // THE FORMULA IS INCORRECT THE AREA IS NEEDED TO BE INSERTED
    f.l[i] = 1/f.n[i]/(3.14*f.R);
    f.Dt[i] = f.v*f.l[i]/3;

    g.n[i] = g.N[i]/(1.6/g.C);
    g.j[i] = g.dN[i]/dt; // THE FORMULA IS INCORRECT THE AREA IS NEEDED TO BE INSERTED x2
    g.l[i] = 1/g.n[i]/g.R;
    g.Dt[i] = g.v*g.l[i]/3;
    if (i > 0 && (f.N[i-1] != 0 || f.N[i] != 0)) {
      f.Dc[i-1] = f.j[i]*(1.6/f.C)/(f.n[i]-f.n[i-1]);
      cout << f.Dt[i-1] << ' ' << f.Dc[i-1] << endl;
    }
  }
}
