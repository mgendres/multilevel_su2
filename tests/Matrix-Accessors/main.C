#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
using namespace std;
#include "constants.h"
#include "matrix.h"

int main(void)
{

  Matrix u;
  u.PrintProperties();

  u.Element0() = 1.0;
  u.Element1() = 2.0;
  u.Element2() = 3.0;
  u.Element3() = 4.0;
  u.PrintProperties();

  exit(EXIT_SUCCESS);
}


