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

  Matrix u, v;

  double p = 0.01;
  for (int i=0; i<1000; ++i) {
    u.RandomSU2();
    v = u.Power(p);
    std::cout << p << " : ";
    std::cout << u.Tr() << " ";
    std::cout << v.Tr() << std::endl;
  }

  exit(EXIT_SUCCESS);
}


