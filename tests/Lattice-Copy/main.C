#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "mt19937.h"
#include "constants.h"
#include "lattice.h"

int main(void)
{

  rng.Init(time(0));

  int sites0[4] = {3,5,7,11};
  int sites1[4] = {3,5,7,11};
  Lattice lattice0(sites0);
  Lattice lattice1(sites1);
  lattice0.Initialize(DISORDERED);
  lattice1.Initialize(ORDERED);

  cout << "Lattice 0 : " << endl;
  cout << "Mean plaquette : " << lattice0.MeanPlaquette() << endl;
  cout << "Mean trace link: " << lattice0.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice0.MeanPolyakovLoop() << endl;

  cout << "Lattice 1 : " << endl;
  cout << "Mean plaquette : " << lattice1.MeanPlaquette() << endl;
  cout << "Mean trace link: " << lattice1.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice1.MeanPolyakovLoop() << endl;

  cout << "Difference in lattices : " << Diff(lattice0,lattice1) << endl;

  if (!Copy(lattice0, lattice1) ) {
    cout << "Failed to copy lattice!" << endl;
    exit(EXIT_FAILURE);
  } else {
    cout << "Copied lattice 0 to Lattice 1. " << endl;
  }

  cout << "Lattice 1 : " << endl;
  cout << "Mean plaquette : " << lattice1.MeanPlaquette() << endl;
  cout << "Mean trace link: " << lattice1.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice1.MeanPolyakovLoop() << endl;

  cout << "Difference in lattices : " << Diff(lattice0,lattice1) << endl;

  exit(EXIT_SUCCESS);
}


