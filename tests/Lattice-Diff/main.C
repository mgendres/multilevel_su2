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

  int sites0[4] = {3,5,7,11};
  int sites1[4] = {3,5,7,11};
  Lattice lattice0(sites0);
  Lattice lattice1(sites1);
  lattice0.Initialize(DISORDERED);
  lattice1.Initialize(ORDERED);

  if (!Copy(lattice0, lattice1) ) {
    cout << "Failed to copy lattice!" << endl;
    exit(EXIT_FAILURE);
  } else {
    cout << "Copied lattice 0 to Lattice 1. " << endl;
  }

  cout << "Difference in lattices : " << Diff(lattice0,lattice1) << endl;

  lattice1.RandomGaugeTransform();

  cout << "Difference in lattices : " << Diff(lattice0,lattice1) << endl;

  lattice0.MaximalTreeGaugeFix();
  lattice1.MaximalTreeGaugeFix();

//int s[4];
//int count(0);
//for ( s[0]=0; s[0]<sites0[0]; ++s[0] )
//for ( s[1]=0; s[1]<sites0[1]; ++s[1] )
//for ( s[2]=0; s[2]<sites0[2]; ++s[2] )
//for ( s[3]=0; s[3]<sites0[3]; ++s[3] )
//for (int mu=0; mu<4; ++mu) {
//  if ( lattice0.GaugeField(mu,s).Tr() - lattice1.GaugeField(mu,s).Tr() > 1e-8) {
//    count++;
//    cout << s[0] << " ";
//    cout << s[1] << " ";
//    cout << s[2] << " ";
//    cout << s[3] << " ";
//    cout << mu << " : ";
//    cout << lattice0.GaugeField(mu,s) << " | ";
//    cout << lattice1.GaugeField(mu,s);
//    cout << endl;
//  }
//}
//cout << count<< " ";
//cout << endl;

  exit(EXIT_SUCCESS);
}


