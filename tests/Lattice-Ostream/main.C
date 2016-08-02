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

  int sites[4] = {4,4,4,4};
  Lattice lattice(sites);
  lattice.Initialize(DISORDERED);

  cout << lattice<< endl;

  exit(EXIT_SUCCESS);
}


