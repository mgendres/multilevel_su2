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
  int sitesX[4] = {2,2,2,2};
  Lattice lattice(sites);
  Lattice latticeX(sitesX);

  latticeX.Initialize(DISORDERED);

  if ( InterpolatedTwoCellBoundaryRefine(latticeX, lattice) ) {
    cout << "Refinement successful. " << endl;
  } else {
    cout << "Refinement failed. " << endl;
    exit(EXIT_FAILURE);
  }

  int s[4];
  int t[4];
  for ( s[0]=0; s[0]<sitesX[0]; ++s[0] )
  for ( s[1]=0; s[1]<sitesX[1]; ++s[1] )
  for ( s[2]=0; s[2]<sitesX[2]; ++s[2] )
  for ( s[3]=0; s[3]<sitesX[3]; ++s[3] ) {
    for (int mu=0; mu<4; ++mu) t[mu]=2*s[mu];
    for (int mu=0; mu<4; ++mu)
    for (int nu=0; nu<mu; ++nu) {
      for (int sigma=0; sigma<4; ++sigma) cout << t[sigma] << " ";
      cout << ": ";
      cout << mu;
      cout << " ";
      cout << nu;
      cout << " : ";

      cout << latticeX.Plaquette(mu,1,nu,1,s);
      cout << " ";

      double u = lattice.Plaquette(mu,2,nu,2,t);
      cout << u;
      cout << " ";

      complex<double> uq(u, sqrt(4-u*u));
      uq *=0.5;
      uq = pow(uq, 0.25);
      uq *=2;
      cout << real(uq );
      cout << " ";

      cout << lattice.Plaquette(mu,1,nu,1,t);
      cout << " ";

      t[mu]++;
      cout << lattice.Plaquette(mu,1,nu,1,t);
      cout << " ";

      t[nu]++;
      cout << lattice.Plaquette(mu,1,nu,1,t);
      cout << " ";

      t[mu]--;
      cout << lattice.Plaquette(mu,1,nu,1,t);
      cout << endl;


    }
  }


  exit(EXIT_SUCCESS);

}


