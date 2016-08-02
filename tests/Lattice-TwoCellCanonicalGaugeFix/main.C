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

  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=0; m<4; ++m)
  for (int n=0; n<4; ++n)
  cout << "Mean plaquette (" << m << "," << n << ") : " << lattice.MeanPlaquette(m,n) << endl;

  lattice.TwoCellCanonicalGaugeFix();

  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=0; m<4; ++m)
  for (int n=0; n<4; ++n)
  cout << "Mean plaquette (" << m << "," << n << ") : " << lattice.MeanPlaquette(m,n) << endl;

  if (1) {
    int s[4];
    for ( s[0]=0; s[0]<sites[0]; ++s[0] )
    for ( s[1]=0; s[1]<sites[1]; ++s[1] )
    for ( s[2]=0; s[2]<sites[2]; ++s[2] )
    for ( s[3]=0; s[3]<sites[3]; ++s[3] )
    for (int mu=0; mu<4; ++mu)
    if ( abs (lattice.GaugeField(mu,s).Tr() - 2.0) < 1e-8 ) {
      for (int nu=0; nu<4; ++nu) cout << s[nu] << " ";
      cout << ": ";
      cout << mu;
      cout << endl; 
    }
  }

  exit(EXIT_SUCCESS);
}


