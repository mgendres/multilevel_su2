#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
using namespace std;
#include "mt19937.h"
#include "constants.h"
#include "matrix.h"

int main(void)
{

  if (1) {
    Matrix u(1.0,2.0,3.0,4.0);
    u.PrintProperties(); // Confirms Det(), Tr()

    Matrix v = u.Dagger();
    v.PrintProperties();


    Matrix w = u.Inverse();
    w.PrintProperties();
  }

  exit(EXIT_SUCCESS);
}


