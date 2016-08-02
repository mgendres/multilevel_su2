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

  Matrix u;
  u.Element0() = 2.0*rng.genrand_res53()-1.0;
  u.Element1() = 2.0*rng.genrand_res53()-1.0;
  u.Element2() = 2.0*rng.genrand_res53()-1.0;
  u.Element3() = 2.0*rng.genrand_res53()-1.0;
  u.PrintProperties();

  double p;
  Matrix v;
  for (int i=0; i<10; ++i) {
    p = rng.genrand_res53();
    v = u.Power(p);
    std::cout << "power = " << p << std::endl;
    v.PrintProperties();
  }

  Matrix w(1.0);
  cout << w << endl;
  cout << w.Power(1.0) << endl;

  exit(EXIT_SUCCESS);
}


