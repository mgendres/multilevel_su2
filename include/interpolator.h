#include <string>
#include <vector>

#ifndef INCLUDED_INTERPOLATOR
#define INCLUDED_INTERPOLATOR

class Interpolator
{
  private:

    std::vector<double> f;
    std::vector<double> x;

    Interpolator& operator=(const Interpolator&);
    Interpolator(const Interpolator&);

  public:
    explicit Interpolator(std::string);
    ~Interpolator();

    double operator()(double);

};

#endif
