#include "lattice.h"
#include <vector>


#ifndef INCLUDED_PLAQUETTE_MONSTER
#define INCLUDED_PLAQUETTE_MONSTER

class PlaquetteMonster
{
  private:

    int sites[4];
    int len;
    Lattice ** lats;

    PlaquetteMonster& operator=(const PlaquetteMonster&);
    PlaquetteMonster(const PlaquetteMonster&);

  public:
    explicit PlaquetteMonster(const int*, int);
    ~PlaquetteMonster();

    void Initialize(const Lattice &);
    double MeanPlaquette(int,int);
    
    Lattice & operator[](const int);

};

#endif
