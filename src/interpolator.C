#include "interpolator.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// This function just reads in some pair-wise data
// And does a linear interpolation of that data

Interpolator::Interpolator(std::string fname)
{

  double x_, f_;
  std::cout << "Opening file : " << fname << std::endl;
  std::ifstream file( fname.c_str() );

  if (!file) {
    std::cout << "File cannot be opened" << std::endl;
    exit(1);
  }

  // While there's still stuff left to read
  while (file)
  {
      // Read stuff from the file into a string and print it
      std::string strInput;
      file >> x_;
      file >> f_;
      x.push_back(x_);
      f.push_back(f_);
  }

  std::cout << "Closing file : " << fname << std::endl;
  file.close();
}

Interpolator::~Interpolator() {
}


double Interpolator::operator()(double x_) {

  if (x_ < x[0]) {
    std::cout << "Domain of interpolation function data exceeded." << std::endl;
    exit(1);
  }
  if (x_ > x[x.size()-1]) {
    std::cout << "Domain of interpolation function data exceeded." << std::endl;
    exit(1);
  }

  std::vector<double>::iterator it = std::lower_bound(x.begin(), x.end(), x_);
//  int i = std::distance(begin(x), it);
  int i = std::distance(x.begin(), it);

  double x0 = x[i-1];
  double x1 = x[i];
  double f0 = f[i-1];
  double f1 = f[i];

//  std::cout << x0 << " " << x_ << " " << x1 << std::endl;

  double a = (x1*f0 - x0*f1) / (x1-x0);
  double b = (f1 - f0) / (x1 - x0);
  return (a + b * x_);
}

