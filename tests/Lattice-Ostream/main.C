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

  int sites[4] = {4,4,4,4};
  Lattice lattice(sites);
  lattice.Initialize(DISORDERED);

  cout << lattice<< endl;

  exit(EXIT_SUCCESS);
}


