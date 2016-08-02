#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include "ranlxd.h"
using namespace std;

int main(void)
{

  double r;
  int i;
  int a[10];

  for (int k=0;k<10;++k) { a[k]=0; }

  for (int k=0;k<10;++k) { cout << a[k] << " "; }
  cout << endl;

  for (int k=0;k<10000000;++k) {
    r = 10*rng.UniformDeviate();
    i = floor(r);
    a[i] += 1;
  }

  for (int k=0;k<10;++k) { cout << a[k] << " "; }
  cout << endl;


  exit(EXIT_SUCCESS);
}


