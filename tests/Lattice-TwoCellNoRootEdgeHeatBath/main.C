#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "mt19937.h"
#include "constants.h"
#include "lattice.h"
#include "subset.h"

int main(void)
{

  int sites[4] = {4,4,4,4};
  Lattice lattice(sites);
  lattice.Initialize(DISORDERED);
  Lattice latticeX(sites);
  Copy(lattice,latticeX);

  latticeX.HeatBathUpdate(0.0,Subsets::two_cell_no_root_edge);

  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu)
  if ( ( lattice.GaugeField(mu,s) - latticeX.GaugeField(mu,s) ).Det() <1e-8 ) {
    for (int nu=0; nu<4; ++nu) cout << s[nu] << " ";
    cout << mu;
    cout << endl;
  }

  exit(EXIT_SUCCESS);

}


