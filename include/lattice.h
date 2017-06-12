#ifndef INCLUDED_LATTICE
#define INCLUDED_LATTICE
#include "matrix.h"
#include "ostream"
#include "subset.h"

enum lat_state { ORDERED, DISORDERED };

class Lattice
{
  private:
    Matrix *gauge_field;
    int sites[4];
    int gauge_field_size;
    int volume;
  
  public:
    Lattice(int*);
    ~Lattice();

    friend std::ostream& operator<<(std::ostream&, const Lattice&);
 
    void Initialize(enum lat_state); 
    void Initialize(enum lat_state, const Subset &);

    int SiteIndex(const int*) const;
    int GaugeIndex(int, const int*) const;
    
    double Plaquette(int, int, int, int, const int*);
    double MeanLink();
    double MeanPlaquette();
    double MeanPlaquette(int, int);
    double MeanPolyakovLoop();

    Matrix Staple(int, const int*);
    void RandomGaugeTransform();
    void GlobalTransform(Matrix);
    void MaximalTreeGaugeFix();
    void UnitLinkGaugeFix(int, const int*); // Gauge transforms link to unity

    double CoolUpdate();
    double CoolUpdate(const Subset &);
    double HeatBathUpdate(double);
    double HeatBathUpdate(double, const Subset &);
    double SweepUpdate(double, double);

    Matrix& GaugeField(int, const int*) const;
    Matrix& GaugeField(int, const int*);
    Matrix& GaugeField(int) const;
    Matrix& GaugeField(int);

    void TwoCellCanonicalGaugeFix(); // Gauge fix two-cell edges

    friend double Diff(Lattice&, Lattice&); // Compare lattices
    friend bool Copy(const Lattice&, Lattice&); // Copies a alattice
    friend bool Decimate(Lattice&, Lattice&); // Copies a (2L)^4 lattice to an L^4 lattice, preserving 2Nx2M plaquettes
    friend bool Refine(Lattice&, Lattice&); // Copies an L^4 lattice to a (2L)^4 lattice
    friend bool InterpolatedTwoCellBoundaryRefine(Lattice&, Lattice&); // Copies an L^4 lattice to a (2L)^4 lattice
    friend bool CanonicalRefine(Lattice&, Lattice&); // Copies an L^4 lattice to a (2L)^4 lattice

    bool Read(std::string);
    bool Write(std::string);

};

#endif
