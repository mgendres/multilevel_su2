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

  int sites[4] = {12,12,12,12};
  int sitesX[4] = {6,6,6,6};
  Lattice latticeA(sites);
  Lattice latticeB(sites);
  Lattice latticeX(sitesX);

  Lattice latticeAA(sites);
  Lattice latticeBB(sites);

  latticeX.Initialize(DISORDERED);

  if ( InterpolatedTwoCellBoundaryRefine(latticeX, latticeA) ) {
    cout << "Refinement successful. " << endl;
  } else {
    cout << "Refinement failed. " << endl;
    exit(EXIT_FAILURE);
  }

  if ( InterpolatedTwoCellBoundaryRefine(latticeX, latticeB) ) {
    cout << "Refinement successful. " << endl;
  } else {
    cout << "Refinement failed. " << endl;
    exit(EXIT_FAILURE);
  }

  cout << Diff(latticeA, latticeB) << endl;
  latticeA.TwoCellBulkInitialize(DISORDERED);
  latticeB.TwoCellBulkInitialize(DISORDERED);
  cout << Diff(latticeA, latticeB) << endl;

  for (int sweeps=0; sweeps<1000; ++sweeps) {

//    latticeA.TwoCellBulkHeatBathUpdate(100.0);
//    latticeB.TwoCellBulkHeatBathUpdate(100.0);

    latticeA.TwoCellBulkCoolUpdate();
    latticeB.TwoCellBulkCoolUpdate();

    cout << sweeps << " : ";
    Copy(latticeA, latticeAA); // Need to do this since Diff changes the lattice
    Copy(latticeB, latticeBB);
    cout << Diff(latticeAA, latticeBB) << endl;
  }

  exit(EXIT_SUCCESS);

}


