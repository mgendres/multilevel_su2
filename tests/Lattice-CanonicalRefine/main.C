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
  int sitesX[4] = {4,4,4,4};
  Lattice lattice(sites);
  Lattice latticeX(sitesX);

  latticeX.Initialize(DISORDERED);

  if ( CanonicalRefine(latticeX, lattice) ) {
    cout << "Refinement successful. " << endl;
  } else {
    cout << "Refinement failed. " << endl;
    exit(EXIT_FAILURE);
  }

  cout << latticeX.MeanPlaquette(1,1) << endl;;
  cout << lattice.MeanPlaquette(2,2) << endl;;


  int s[4];
  for ( s[0]=0; s[0]<sitesX[0]; ++s[0] )
  for ( s[1]=0; s[1]<sitesX[1]; ++s[1] )
  for ( s[2]=0; s[2]<sitesX[2]; ++s[2] )
  for ( s[3]=0; s[3]<sitesX[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {
    for (int nu=0; nu<4; ++nu) { cout << s[nu] << " "; }
    cout << lattice.GaugeField(mu,s).Tr() << endl;
  }

  exit(EXIT_SUCCESS);

}


