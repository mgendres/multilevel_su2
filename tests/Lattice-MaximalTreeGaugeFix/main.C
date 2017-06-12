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

  cout << "Create a disordered lattice..." << endl;
  lattice.Initialize(DISORDERED);
  cout << "Creating copy of lattice..." << endl;
  Lattice latticeX(sites);
  Copy(lattice,latticeX);
  latticeX.RandomGaugeTransform();
  Diff(lattice,latticeX);

  exit(EXIT_SUCCESS);
}


