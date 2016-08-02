#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "mt19937.h"
#include "constants.h"
#include "lattice.h"
#include "utils.h"

int main(void)
{

  int sites[4] = {8,8,8,8};
  int sitesX[4] = {4,4,4,4};
  Lattice lattice(sites);
  Lattice latticeX(sitesX);
  Lattice latticeY(sites);

  lattice.Initialize(DISORDERED);

  if ( Decimate(lattice, latticeX) ) {
    cout << "Decimation successful. " << endl;
  } else {
    cout << "Decimation failed. " << endl;
    exit(EXIT_FAILURE);
  }

  if ( Refine(latticeX, latticeY) ) {
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
      cout << " ";
      cout << latticeY.Plaquette(mu,2,nu,2,t);
      cout << endl;
    }
  }


  double total(0.0);
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  if( !TwoCellRootSiteQ(s) )
  for (int mu=0; mu<4; ++mu) {
    total += latticeY.GaugeField(mu,s).Tr();
  }
  cout << "Total trace of non-root site links : " << total <<endl;
  cout << "Expected total trace of non-root site links : ";
  cout << 2*4*sites[0]*sites[1]*sites[2]*sites[3] - 2*4*sitesX[0]*sitesX[1]*sitesX[2]*sitesX[3] << endl;
  exit(EXIT_SUCCESS);

}


