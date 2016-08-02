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

  int sitesX[4] = {4,4,4,4};
  Lattice latticeX(sitesX);

  int sites[4] = {8,8,8,8};
  Lattice lattice(sites);
  lattice.Initialize(DISORDERED);

  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=1; m<4; ++m)
  for (int n=1; n<4; ++n)
  cout << "Mean plaquette (" << m << "," << n << ") : " << lattice.MeanPlaquette(m,n) << endl;

  if( !lattice.Write("cfg.bin") )
    cout << "Failed to export lattice!" << endl;

  lattice.Initialize(ORDERED);


  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=1; m<4; ++m)
  for (int n=1; n<4; ++n)
  cout << "Mean plaquette (" << m << "," << n << ") : " << lattice.MeanPlaquette(m,n) << endl;


  if( !lattice.Read("cfg.bin") )
    cout << "Failed to import lattice!" << endl;

  cout << "Mean trace link: " << lattice.MeanLink() << endl;
  cout << "Mean Polyakov loop: " << lattice.MeanPolyakovLoop() << endl;
  for (int m=1; m<4; ++m)
  for (int n=1; n<4; ++n)
  cout << "Mean plaquette (" << m << "," << n << ") : " << lattice.MeanPlaquette(m,n) << endl;

  if( !latticeX.Read("cfg.bin") )
    cout << "Failed to import lattice!" << endl;
  exit(EXIT_SUCCESS);
}


