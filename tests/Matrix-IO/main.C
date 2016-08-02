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
    Matrix u(1.0,2.0,3.0,4.0);
    std::cout << u << std::endl;
  }

  exit(EXIT_SUCCESS);
}


