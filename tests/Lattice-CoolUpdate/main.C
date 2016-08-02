#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "constants.h"
#include "lattice.h"

int main(void)
{

  int sites[4] = {12,12,12,12};
  Lattice lattice(sites);

  lattice.Initialize(DISORDERED);

  for (int sweeps=0; sweeps<300; ++sweeps) {
    cout << sweeps << " : ";
    for (int m=0; m<4; ++m)
    for (int n=0; n<m; ++n) {
    cout << lattice.MeanPlaquette(m+1,n+1) << " ";
    }
    cout << endl;
    lattice.CoolUpdate();

  }

  exit(EXIT_SUCCESS);

}


