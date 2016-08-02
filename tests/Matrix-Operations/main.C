#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
using namespace std;
#include "constants.h"
#include "matrix.h"

int main(void)
{


  std::cout << "u : " << std::endl;
  Matrix u;
  u.RandomSU2();
  u.PrintProperties();

  std::cout << "v : " << std::endl;
  Matrix v;
  v.RandomSU2();
  v.PrintProperties();

  std::cout << "w : " << std::endl;
  Matrix w;
  w.RandomSU2();
  w.PrintProperties();

  std::cout << "v.u : " << std::endl;
  Matrix vu;
  vu = v*u;
  vu.PrintProperties();

  std::cout << "u.w : " << std::endl;
  Matrix uw;
  uw = u*w;
  uw.PrintProperties();

//std::cout << "vdag.u : " << std::endl;
//Matrix vdagu(u);
//vdagu.LeftDaggerMultiply(v);
//vdagu.PrintProperties();

//std::cout << "u.wdag : " << std::endl;
//Matrix uwdag(u);
//uwdag.RightDaggerMultiply(w);
//uwdag.PrintProperties();

  exit(EXIT_SUCCESS);
}


