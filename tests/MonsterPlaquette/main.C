#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "mt19937.h"
#include "constants.h"
#include "lattice.h"
#include "plaquette_monster.h"

int main(void)
{

  int sites[4] = {8,8,8,8};
  Lattice lattice(sites);
  lattice.Initialize(DISORDERED);

  PlaquetteMonster plaquette_monster(sites,4);
  plaquette_monster.Initialize(lattice);

  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=0; m<4; ++m)
  for (int n=0; n<4; ++n) {
    cout << "Mean plaquette (" << m << "," << n << ") : ";
    cout << lattice.MeanPlaquette(m,n) << " ";
    cout << plaquette_monster.MeanPlaquette(m,n) << " ";
    cout << endl;
  }
  exit(EXIT_SUCCESS);
}


