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
    Matrix u;
    u.Diagonal(3.2);
    u.PrintProperties();
  }

  if (1) {
    Matrix u;
    u.Initialize(1.0,2.0,3.0,4.0);
    u.PrintProperties();
  }

  if (1) {
    double alpha, theta, phi;
    alpha = 2*PI*rng.genrand_res53();
    theta = PI*rng.genrand_res53();
    phi = 2*PI*rng.genrand_res53();
    Matrix u;
    u.EulerSU2(alpha,theta,phi);
    u.PrintProperties();
  }

  if (1) {
    Matrix u;
    u.RandomSU2();
    u.PrintProperties();
  }

  if (1) {
    Matrix u;
    for (double x=0.0; x<1.0; x+=0.05) {
      cout << x << endl;
      u.RandomSU2(x);
      u.PrintProperties();
    }
  }
  exit(EXIT_SUCCESS);
}


