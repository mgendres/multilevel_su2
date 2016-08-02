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
  int sitesX[4] = {4,4,4,4};
  Lattice latticeA(sites);
  Lattice latticeB(sites);
  Lattice latticeX(sitesX);

  latticeX.Initialize(DISORDERED);

  if ( Refine(latticeX, latticeA) ) {
    cout << "Refinement successful. " << endl;
  } else {
    cout << "Refinement failed. " << endl;
    exit(EXIT_FAILURE);
  }

  latticeX.RandomGaugeTransform();

  if ( Refine(latticeX, latticeB) ) {
    cout << "Refinement successful. " << endl;
  } else {
    cout << "Refinement failed. " << endl;
    exit(EXIT_FAILURE);
  }

  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  if (latticeA.TwoCellRootSiteQ(s) )
  for (int mu=0; mu<4; ++mu)
  for (int nu=0; nu<mu; ++nu) {
    for (int sigma=0; sigma<4; ++sigma) cout << s[sigma] << " ";
    cout << ": ";
    cout << mu;
    cout << " ";
    cout << nu;
    cout << " : ";
    cout << latticeA.Plaquette(mu,2,nu,2,s);
    cout << " ";
    cout << latticeB.Plaquette(mu,2,nu,2,s);
    cout << endl;
  }

  exit(EXIT_SUCCESS);

}


