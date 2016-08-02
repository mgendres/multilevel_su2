#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
#include "mt19937.h"
#include "constants.h"
#include "lattice.h"

#define PLAQ_N 2
#define PLAQ_M 2

int main(void)
{

  cout << setprecision(15);
  int sites[4] = {8,8,8,8};

  double beta_begin= 0.0;
  double beta_end = 10.0;
  double beta_inc = 0.1;

  int n_confs = 10000;
  int n_chkpt = 10;

  Lattice lattice(sites);

  vector<double> betas;
  vector<double> plaq[PLAQ_M][PLAQ_N];

  int conf;
  for (double beta=beta_begin; beta<beta_end; beta+=beta_inc) {

    std::cout << "beta = " << beta;
    std::cout << " on interval : [" << beta_begin;
    std::cout << "," << beta_end;
    std::cout << "] with increments of " << beta_inc<< std::endl;
    std::cout << "Initializing lattice..." << std::endl;
    lattice.Initialize(DISORDERED);
    std::cout << "Generating " << n_confs;
    std::cout << " configs, saved every " << n_chkpt << "..." << std::endl;
    conf = 0;
    do {
      if ( conf%n_chkpt==0 ) {

        std::cout << "Saving observables for configuration : " << conf  << std::endl;
        betas.push_back( beta );
        for (int m=0; m<PLAQ_M; ++m)
        for (int n=0; n<PLAQ_M; ++n) {
          plaq[m][n].push_back( 1.0-lattice.MeanPlaquette(m+1,n+1) );
        }

      } 
      lattice.HeatBathUpdate(beta);
      ++conf;
    } while (conf < n_confs);

  }


//// File I/O
  std::stringstream ss;
  ofstream file;

  for (int m=0; m<PLAQ_M; ++m)
  for (int n=0; n<PLAQ_N; ++n) {
    ss.str(std::string());
    ss << "data/plaq-" << m+1 << "_" << n+1 << ".dat";
    file.open(ss.str().c_str());
    file << setprecision(15);
    for(int j=0; j<betas.size(); ++j) {
      file << betas[j] << " " <<  plaq[m][n][j] << std::endl;
    }
    file.close();
  }

  exit(EXIT_SUCCESS);
}


