#include <iostream>
#include "matrix.h"
#include <complex>
#include <math.h>
#include "mt19937.h"
#include "constants.h"
#include <cstdlib>

Matrix::Matrix()
{
  Diagonal(1.0);
}

Matrix::Matrix(double k)
{
  Diagonal(k);
}

Matrix::Matrix(double a0, double a1, double a2, double a3)
: element0(a0),
  element1(a1),
  element2(a2),
  element3(a3)
{
}

Matrix::Matrix(const Matrix &rhs)
{
  element0 = rhs.element0;
  element1 = rhs.element1;
  element2 = rhs.element2;
  element3 = rhs.element3;
}

void Matrix::Diagonal(double k)
{
  element0 = k;
  element1 = 0.0;
  element2 = 0.0;
  element3 = 0.0;
}

void Matrix::Initialize(double a0, double a1, double a2, double a3)
// a_0 \sigma_0 + i a_j \sigma_j;
//  a_0^2 + a_j^2 = 1
{
  element0 = a0;
  element1 = a1;
  element2 = a2;
  element3 = a3;
}

void Matrix::EulerSU2(double alpha, double theta, double phi)
// a_0 + i a_j \sigma_j; a_0^2 + a_j^2 = 1
// where
// \sigma_1 = {{0,1},{1,0}}
// \sigma_2 = {{0,-i},{i,0}}
// \sigma_3 = {{1,0},{0,-1}}
//
// a_1 = r \sin\theta \cos\phi
// a_2 = r \sin\theta \sin\phi
// a_3 = r \cos\theta
// where \theta \in[0,\pi], \phi\in[0,2\pi]
// and  r^2 + a_0^2 = 1 with r \in[0,1]

// r = \sin\alpha
// a_0 = \cos\alpha
// with \alpha\in[0,2\pi]

// So: alpha in [0,2pi], theta in [0,pi], phi in [0,2pi]
{
  element0 = cos(alpha);
  element1 = sin(alpha) * sin(theta) * cos(phi);
  element2 = sin(alpha) * sin(theta) * sin(phi);
  element3 = sin(alpha) * cos(theta);
}

void Matrix::RandomSU2()
{
  double alpha = 2*PI*rng.genrand_res53();
  double theta = PI*rng.genrand_res53();
  double phi = 2*PI*rng.genrand_res53();
  EulerSU2(alpha,theta,phi);
}

void Matrix::RandomSU2(double x)
{

  if (x<0) {
    std::cout << "x < 0" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Generate a0
  double z0 = exp(-x);
  double z1 = exp(x);
  double z, p;

  bool rejected = true;
  do {
    z = (z1-z0)*rng.genrand_res53() + z0;
    element0 = ( x > 0.0 ? log(z)/x : 0.0 );
    p = sqrt(1.0 - element0*element0);
    if ( p > rng.genrand_res53() ) rejected = false; 
  } while (rejected);

  // Generate a1, a2, a3 uniformly on a sphere
  element3 = 2.0*rng.genrand_res53()-1.0;
  double r = sqrt(1.0-element3*element3);
  double phi = 2.0*PI*rng.genrand_res53();
  element1 = r*cos(phi);
  element2 = r*sin(phi);

  // Correct the radius
  element1 *= p;
  element2 *= p;
  element3 *= p;

}

void Matrix::PrintProperties() const
{
  std::cout << "Matrix elements : " << std::endl;
  std::cout << *this << std::endl;
  std::cout << "Det : " << Det() << std::endl;
  std::cout << "Tr : " << Tr() << std::endl;
  std::cout << std::endl;
}

double Matrix::Det() const
{
  double det(0.0);
  det += element0 * element0;
  det += element1 * element1;
  det += element2 * element2;
  det += element3 * element3;
  return det;
}

double Matrix::Tr() const
{
  return 2*element0;
}

Matrix Matrix::Dagger() const
{
  return Matrix(element0, -element1, -element2, -element3);
}

Matrix Matrix::Inverse() const
{
  double det = this->Det();
  return Matrix(element0/det, -element1/det, -element2/det, -element3/det);
}

Matrix Matrix::Power(double p) const
{
  double x(element0);
  double y(0.0);
  y += element1*element1;  
  y += element2*element2;  
  y += element3*element3;
  y = sqrt(y);
  std::complex<double> z(x,y);
  z = pow(z,p);
  if ( y < 1e-127 ) return Matrix( real(z), 0.0, 0.0, 0.0 );
  return Matrix( real(z), element1*imag(z)/y, element2*imag(z)/y, element3*imag(z)/y );
}

Matrix Matrix::RelationalTransformation(Matrix B) const {
  // Given "this" matrix (A) find a tranformation O st. O.A.O^\dagg = B
  // Note this function assume a0 == b0
  double d2 = B.Element0();
  d2 -= element0;
  d2 *= d2;
  d2 = sqrt(d2);
  if (d2 > 1e-12) {
    std::cout << "Matrix::RelationalTransformation(...) assumes a0=b0" << std::endl;
    exit(EXIT_FAILURE); 
  }
  // std::cout << "Matrix::RelationalTransformation(...) d2 = " << d2 << std::endl;
  Matrix V;
  V.Element0() = 1.0;
  V.Element1() = 0.0;
  V.Element2() = (B.Element3()-element3)/(element1+B.Element1());
  V.Element3() = (element2-B.Element2())/(element1+B.Element1());
  V /= sqrt( V.Det() );
  return V;
}


double& Matrix::Element0() { return element0; }
double& Matrix::Element1() { return element1; }
double& Matrix::Element2() { return element2; }
double& Matrix::Element3() { return element3; }

const double& Matrix::Element0() const { return element0; }
const double& Matrix::Element1() const { return element1; }
const double& Matrix::Element2() const { return element2; }
const double& Matrix::Element3() const { return element3; }

Matrix& Matrix::operator+=(const Matrix& rhs) {
  element0 += rhs.Element0();
  element1 += rhs.Element1();
  element2 += rhs.Element2();
  element3 += rhs.Element3();
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
  element0 -= rhs.Element0();
  element1 -= rhs.Element1();
  element2 -= rhs.Element2();
  element3 -= rhs.Element3();
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {


  double a0(element0);
  double a1(element1);
  double a2(element2);
  double a3(element3);

  double b0 = rhs.Element0();
  double b1 = rhs.Element1();
  double b2 = rhs.Element2();
  double b3 = rhs.Element3();

  double tmp;

  element0 *= b0;
  tmp = a1; tmp *= b1;
  element0 -= tmp;
  tmp = a2; tmp *= b2;
  element0 -= tmp;
  tmp = a3; tmp *= b3;
  element0 -= tmp;

  element1 *= b0;
  tmp = a0; tmp *= b1;
  element1 += tmp;
  tmp = a2; tmp *= b3;
  element1 -= tmp;
  tmp = a3; tmp *= b2;
  element1 += tmp;

  element2 *= b0;
  tmp = a1; tmp *= b3;
  element2 += tmp;
  tmp = a0; tmp *= b2;
  element2 += tmp;
  tmp = a3; tmp *= b1;
  element2 -= tmp;

  element3 *= b0;
  tmp = a1; tmp *= b2;
  element3 -= tmp;
  tmp = a2; tmp *= b1;
  element3 += tmp;
  tmp = a0; tmp *= b3;
  element3 += tmp;

  return *this;
}

Matrix& Matrix::operator/=(const Matrix& rhs) {

  double a0 = element0;
  double a1 = element1;
  double a2 = element2;
  double a3 = element3;

  double det = rhs.Det();
  double b0 = rhs.Element0()/det;
  double b1 = -rhs.Element1()/det;
  double b2 = -rhs.Element2()/det;
  double b3 = -rhs.Element3()/det;

  element0  = a0*b0;
  element0 -= a1*b1;
  element0 -= a2*b2;
  element0 -= a3*b3;

  element1  = a0*b1;
  element1 += a1*b0;
  element1 -= a2*b3;
  element1 += a3*b2;

  element2  = a0*b2;
  element2 += a1*b3;
  element2 += a2*b0;
  element2 -= a3*b1;

  element3  = a0*b3;
  element3 -= a1*b2;
  element3 += a2*b1;
  element3 += a3*b0;

  return *this;
}




Matrix& Matrix::operator+=(double rhs)
{
  element0 += rhs;
  element1 += rhs;
  element2 += rhs;
  element3 += rhs;
  return *this;
}

Matrix& Matrix::operator-=(double rhs)
{
  element0 -= rhs;
  element1 -= rhs;
  element2 -= rhs;
  element3 -= rhs;
  return *this;
}

Matrix& Matrix::operator*=(double rhs)
{
  element0 *= rhs;
  element1 *= rhs;
  element2 *= rhs;
  element3 *= rhs;
  return *this;
}

Matrix& Matrix::operator/=(double rhs)
{
  element0 /= rhs;
  element1 /= rhs;
  element2 /= rhs;
  element3 /= rhs;
  return *this;
}



const Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
  return Matrix(lhs) += rhs;
}

const Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
  return Matrix(lhs) -= rhs;
}

const Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
  return Matrix(lhs) *= rhs;
}

const Matrix operator/(const Matrix& lhs, const Matrix& rhs)
{
  return Matrix(lhs) /= rhs;
}

const Matrix operator+(const Matrix& lhs, double rhs)
{
  return Matrix(lhs) += rhs;
}

const Matrix operator-(const Matrix& lhs, double rhs)
{
  return Matrix(lhs) -= rhs;
}

const Matrix operator*(const Matrix& lhs, double rhs)
{
  return Matrix(lhs) *= rhs;
}

const Matrix operator/(const Matrix& lhs, double rhs)
{
  return Matrix(lhs) /= rhs;
}

const Matrix operator+(double lhs, const Matrix& rhs)
{
  return Matrix(rhs) += lhs;
}

const Matrix operator-(double lhs, const Matrix& rhs)
{
  return Matrix(lhs,lhs,lhs,lhs) -= rhs;
}

const Matrix operator*(double lhs, const Matrix& rhs)
{
  return Matrix(rhs) *= lhs;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
  out << m.Element0() << " ";
  out << m.Element1() << " ";
  out << m.Element2() << " ";
  out << m.Element3() << " ";
  return out;
}
