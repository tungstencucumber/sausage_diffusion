#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
  cout << "Vse khorosho." << endl;
  return 0;
}


/*Здесь я напишу пример цикла, как вижу его
    vector<DrawableParticle> particles = ...
    vector<DrawableParticle>::iterator it1, it2;
    for (it1 = particles.begin(); it1 != particles.end(); it1++) {
        for(it2 = next(it1); it2 != particles.end(); it2++)
            if (it1->sqrho(*it2) < (it1->getR() + it2->getR())*(it1->getR() + it2->getR()))
                it1->collision(*it2);
    it1->move();
    }
    */
