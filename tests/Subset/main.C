#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <ctime>
using namespace std;
#include "constants.h"
#include "subset.h"

int main(void)
{

  int sites[4] = {4,4,4,4};

  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {
    for (int nu=0; nu<4; ++nu) cout << s[nu] << " ";
    cout << ": ";
    cout << mu;
    cout << " : ";
    cout << Subsets::all(mu, s);
    cout << " : ";
    cout << Subsets::checker_board(mu, s);
    cout << " : ";
    cout << Subsets::two_cell_bulk(mu, s);
    cout << " : ";
    cout << Subsets::two_cell_bulk_checker_board(mu, s);
    cout << " : ";
    cout << Subsets::fun(mu, s);
    cout << endl;
  }

  cout << Subsets::all.NumSubsets() << endl;
  cout << Subsets::checker_board.NumSubsets() << endl;
  cout << Subsets::two_cell_bulk.NumSubsets() << endl;
  cout << Subsets::two_cell_bulk_checker_board.NumSubsets() << endl;
  cout << Subsets::fun.NumSubsets() << endl;
  exit(EXIT_SUCCESS);

}


