#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "plaquette_monster.h"


PlaquetteMonster::PlaquetteMonster(const int* s, int l)
: len(l)
{
  for (int mu=0; mu<4; ++mu) sites[mu] = s[mu];
  lats = new Lattice* [len];
  for (int i=0; i<len; ++i) { lats[i] = new Lattice(sites); }

}

PlaquetteMonster::~PlaquetteMonster()
{
  for (int i=0; i<len; ++i) { delete lats[i]; }
  delete [] lats;
}

void PlaquetteMonster::Initialize(const Lattice & lat)
{

  Copy( lat, *lats[0]);

  int s[4];
  int t[4];
  for ( int m=1; m<len; ++m) {
    Copy( *lats[m-1], *lats[m]);
    for ( s[0]=0, t[0]=0; s[0]<sites[0]; ++s[0], ++t[0] )
    for ( s[1]=0, t[1]=0; s[1]<sites[1]; ++s[1], ++t[1] )
    for ( s[2]=0, t[2]=0; s[2]<sites[2]; ++s[2], ++t[2] )
    for ( s[3]=0, t[3]=0; s[3]<sites[3]; ++s[3], ++t[3] )
    for (int mu=0; mu<4; ++mu) {
      t[mu]+=m;
      lats[m]->GaugeField(mu,s) *= lat.GaugeField(mu,t);
      t[mu]-=m;
    }
  }
}

double PlaquetteMonster::MeanPlaquette(int m,int n)
{

  double plaq(0.0);
  Matrix P;
  P.Diagonal(1.0);

  if (m<1) return 1;
  if (n<1) return 1;
  if (m>len) return 0;
  if (n>len) return 0;

  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu)
  for (int nu=0; nu<mu; ++nu) {
    P = lats[m-1]->GaugeField(mu,s);
    s[mu]+=m;
    P *= lats[n-1]->GaugeField(nu,s);
    s[nu]+=n;
    s[mu]-=m;
    P *= lats[m-1]->GaugeField(mu,s).Dagger();
    s[nu]-=n;
    P *= lats[n-1]->GaugeField(nu,s).Dagger();
    plaq += P.Tr();
  }

  int volume(1);
  for (int mu=0; mu<4; ++mu) volume *= sites[mu];
  return plaq / double(2*6*volume);
}

Lattice& PlaquetteMonster::operator[](const int i) { return *lats[i]; }
