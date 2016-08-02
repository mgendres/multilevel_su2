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
  u.RandomSU2();
  std::cout << "u : " << std::endl;
  u.PrintProperties();

  Matrix v;
  v.RandomSU2();
  std::cout << "v : " << std::endl;
  v.PrintProperties();


  bool mmQ(true);
  bool msQ(false);


  if (mmQ) {
    std::cout << "Matrix/Matrix operations: " << std::endl;
  }

  if (mmQ) {
    std::cout << "u += v : " << std::endl;
    Matrix w = u;
    w += v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "u -= v : " << std::endl;
    Matrix w = u;
    w -= v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "u *= v : " << std::endl;
    Matrix w = u;
    w *= v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "2 u /= v : " << std::endl;
    Matrix w = 2*u;
    w /= v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "u + v : " << std::endl;
    Matrix w = u + v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "u - v : " << std::endl;
    Matrix w = u - v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "u * v : " << std::endl;
    Matrix w = u * v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << " (2*u) / v : " << std::endl;
    Matrix w = (2*u) / v;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "v + u : " << std::endl;
    Matrix w = v + u;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "v - u : " << std::endl;
    Matrix w = v - u;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "v * u : " << std::endl;
    Matrix w = v * u;
    w.PrintProperties();
  }

  if (mmQ) {
    std::cout << "v / (2*u) : " << std::endl;
    Matrix w = v / (2*u);
    w.PrintProperties();
  }







  if (msQ) {
    std::cout << "Matrix/Scalar operations: " << std::endl;
  }

  if (msQ) {
    std::cout << "u += 3.7 : " << std::endl;
    Matrix w = u;
    w += 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "u -= 3.7 : " << std::endl;
    Matrix w = u;
    w -= 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "u *= 3.7 : " << std::endl;
    Matrix w = u;
    w *= 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "u /= 3.7 : " << std::endl;
    Matrix w = u;
    w /= 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "u + 3.7 : " << std::endl;
    Matrix w = u + 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "u - 3.7 : " << std::endl;
    Matrix w = u - 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "u * 3.7 : " << std::endl;
    Matrix w = u * 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "u / 3.7 : " << std::endl;
    Matrix w = u / 3.7;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "3.7 + u : " << std::endl;
    Matrix w = 3.7 + u;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "3.7 - u: " << std::endl;
    Matrix w = 3.7 - u;
    w.PrintProperties();
  }

  if (msQ) {
    std::cout << "3.7 * u: " << std::endl;
    Matrix w = 3.7 * u;
    w.PrintProperties();
  }










//std::cout << "w = v : " << std::endl;
//w = v;
//w.PrintProperties();

//std::cout << "w = v.Dagger() : " << std::endl;
//w = v.Dagger();
//w.PrintProperties();

//std::cout << "z = v.Dagger() (instantiation) : " << std::endl;
//Matrix z = v.Dagger();
//z.PrintProperties();

//z += w;

  exit(EXIT_SUCCESS);
}


