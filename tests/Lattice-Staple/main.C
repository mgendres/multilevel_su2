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

  Matrix U;
  Matrix S;

  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {
    for (int i=0; i<4; ++i) { std::cout << s[i] << " "; }
    //std::cout << lattice.LocalAction(mu,s) << " ";
    U = lattice.GaugeField(mu,s);
    S = lattice.Staple(mu,s);
    std::cout << -0.5*( S * U.Dagger() ).Tr() << " ";
    std::cout << std::endl;
  }
 

  exit(EXIT_SUCCESS);
}


