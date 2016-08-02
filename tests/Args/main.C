#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "arg.h"



int main(void)
{

  LatticeArg lattice_arg("args/lattice.arg");

  EvoArg evo_arg("args/evo.arg");

  CouplingArg coupling_arg("args/coupling.arg");

  RethermArg retherm_arg("args/retherm.arg");

  PlaquetteArg plaquette_arg("args/plaquette.arg");


  exit(EXIT_SUCCESS);

}


