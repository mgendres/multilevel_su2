#ifndef INCLUDED_MATRIX
#define INCLUDED_MATRIX
#include <ostream>

//using namespace std;

class Matrix
{

  private:
    double element0;
    double element1;
    double element2;
    double element3;

  public:
    Matrix(); //
    Matrix(double); //
    Matrix(const Matrix &); //
    Matrix(double, double, double, double); //

    void Diagonal(double); //
    void Initialize(double, double, double, double); //
    void EulerSU2(double, double, double); //
    void RandomSU2(); //
    void RandomSU2(double);

    friend std::ostream& operator<<(std::ostream&, const Matrix&); //

    void PrintProperties() const; //
    double Det() const; //
    double Tr() const; //
    Matrix Dagger() const; //
    Matrix Inverse() const; //
    Matrix Power(double) const; //

    Matrix& operator+=(const Matrix&); //
    Matrix& operator-=(const Matrix&); //
    Matrix& operator*=(const Matrix&); //
    Matrix& operator/=(const Matrix&); //

    Matrix& operator+=(double); //
    Matrix& operator-=(double); //
    Matrix& operator*=(double); //
    Matrix& operator/=(double); //

    double& Element0(); //
    double& Element1(); //
    double& Element2(); //
    double& Element3(); //
    const double& Element0() const; //
    const double& Element1() const; //
    const double& Element2() const; //
    const double& Element3() const; //

};

const Matrix operator+(const Matrix&, const Matrix&); //
const Matrix operator-(const Matrix&, const Matrix&); //
const Matrix operator*(const Matrix&, const Matrix&); //
const Matrix operator/(const Matrix&, const Matrix&); //

const Matrix operator+(const Matrix&, double); //
const Matrix operator-(const Matrix&, double); //
const Matrix operator*(const Matrix&, double); //
const Matrix operator/(const Matrix&, double); //

const Matrix operator+(double, const Matrix&); //
const Matrix operator-(double, const Matrix&); //
const Matrix operator*(double, const Matrix&); //



#endif
