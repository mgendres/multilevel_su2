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

  int sites[4] = {8,8,8,8};
  int sitesX[4] = {4,4,4,4};
  Lattice lattice(sites);
  Lattice latticeX(sitesX);
  lattice.Initialize(DISORDERED);

  if ( Decimate(lattice, latticeX) ) {
    cout << "Decimation successful. " << endl;
  } else {
    cout << "Decimation failed. " << endl;
    exit(EXIT_FAILURE);
  }

  int s[4];
  int t[4];
  for ( s[0]=0; s[0]<sitesX[0]; ++s[0] )
  for ( s[1]=0; s[1]<sitesX[1]; ++s[1] )
  for ( s[2]=0; s[2]<sitesX[2]; ++s[2] )
  for ( s[3]=0; s[3]<sitesX[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {
    for (int nu=0; nu<4; ++nu) t[nu]=2*s[nu];
    for (int nu=0; nu<mu; ++nu) {
      for (int sigma=0; sigma<4; ++sigma) cout << s[sigma] << " ";
      cout << ": ";
      cout << mu;
      cout << " ";
      cout << nu;
      cout << " : ";
      cout << lattice.Plaquette(mu,2,nu,2,t);
      cout << " ";
      cout << latticeX.Plaquette(mu,1,nu,1,s);
      cout << endl;
    }
  }
  exit(EXIT_SUCCESS);

}


