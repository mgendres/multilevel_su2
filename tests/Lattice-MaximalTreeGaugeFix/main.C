#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "ranlxd.h"
#include "constants.h"
#include "lattice.h"

int main(void)
{

  rng.Init(time(0));

  int sites[4] = {8,8,8,8};
  Lattice lattice(sites);
  lattice.Initialize(DISORDERED);

  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=0; m<4; ++m)
  for (int n=0; n<4; ++n)
  cout << "Mean plaquette (" << m << "," << n << ") : " << lattice.MeanPlaquette(m,n) << endl;

  cout << "Performing maximal tree gauge fixing..." << endl;
  lattice.MaximalTreeGaugeFix();

  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=0; m<4; ++m)
  for (int n=0; n<4; ++n)
  cout << "Mean plaquette (" << m << "," << n << ") : " << lattice.MeanPlaquette(m,n) << endl;

  exit(EXIT_SUCCESS);
}


