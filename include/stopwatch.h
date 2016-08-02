#include "time.h"

#ifndef INCLUDED_STOPWATCH
#define INCLUDED_STOPWATCH

class Stopwatch
{
  private:

    clock_t base;
    clock_t elapsed;

    Stopwatch& operator=(const Stopwatch&);
    Stopwatch(const Stopwatch&);

  public:
    explicit Stopwatch();
    ~Stopwatch();

    double ElapsedTime();
    void Restart();

};

#endif
