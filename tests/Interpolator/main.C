#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <ctime>

// Global parameters
#include "interpolator.h"


class RGfunc {
    Interpolator* r;
  public:
    RGfunc();
    ~RGfunc();
    double operator()(double);
};

RGfunc::RGfunc()
{
  r = new Interpolator("matching.dat");
}

RGfunc::~RGfunc()
{
  delete r;
}

double RGfunc::operator()(double K)
{
  if (K < 0.5) { 
    return 0;
  }
  if (K > 8.0) {
    return 0.472516 + 0.354651*K;
  }
  return r->operator()(K);
}


int main(void)
{

  cout << setprecision(15);
  RGfunc R;

  if (1) {
    for (double K=0.0; K<10.0; K+=0.01) {
      std::cout << K << " " <<  R(K) << std::endl;
    }
  }

  return(0);

}

