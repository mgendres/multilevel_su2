#include "stopwatch.h"


Stopwatch::Stopwatch() {
  Restart();
}

Stopwatch::~Stopwatch() {}

double Stopwatch::ElapsedTime() {
  return  double ( clock() - base ) / CLOCKS_PER_SEC;
}

void Stopwatch::Restart() {
  base = clock();
}
