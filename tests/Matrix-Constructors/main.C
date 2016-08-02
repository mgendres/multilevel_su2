#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
using namespace std;
#include "constants.h"
#include "matrix.h"

int main(void)
{

  if (1) {
    Matrix u;
    u.PrintProperties();
  }

  if (1) {
    Matrix u(3.3);
    u.PrintProperties();
  }

  if (1) {
    Matrix u(1.0,2.0,3.0,4.0);
    u.PrintProperties();

    Matrix v(u);
    v.PrintProperties();

    Matrix w = u;
    w.PrintProperties();
  }

  exit(EXIT_SUCCESS);
}


