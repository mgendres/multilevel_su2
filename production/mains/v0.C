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
#include "stopwatch.h"
#include "plaquette_monster.h"
#include "arg.h"

int main(int argc, char* argv[])
{

  if (argc != 5) {
    cout << "usage: ./a.out ";
    cout << "<coupling.arg> ";
    cout << "<evo.arg> ";
    cout << "<lattice.arg> ";
    cout << "<plaquette.arg> ";
    cout << endl;
    exit(EXIT_FAILURE);
  }

  // Get/set parameters
  CouplingArg coupling_arg( argv[1] );
  double beta = coupling_arg.beta;;

  EvoArg evo_arg( argv[2] );
  int n_conf = evo_arg.n_conf;
  int n_chkpt = evo_arg.n_chkpt;
  string cfg_file_stem = evo_arg.file_stem;

  LatticeArg lattice_arg( argv[3] );
  int sites[4]; for (int mu=0; mu<4; ++mu) sites[mu] = lattice_arg.sites[mu];
  enum lat_state state = lattice_arg.state;;

  PlaquetteArg plaquette_arg( argv[4] );
  int n_plaq = plaquette_arg.n_plaq;
  string plaq_file_stem = plaquette_arg.file_stem;

  std::cout << "Initializing the lattice ";
  if (state==DISORDERED) std::cout << "(DISORDERED)";
  if (state==ORDERED) std::cout << "(ORDERED)";
  std::cout << "..." << std::endl;
  Lattice lattice(sites);
  lattice.Initialize(state);

  std::cout << "Initializing the monster..." << endl;;
  PlaquetteMonster monster(sites, n_plaq);

  vector<double> **plaq;
  plaq = new vector<double> * [n_plaq];
  for (int i=0; i<n_plaq; ++i) {
    plaq[i] = new vector<double> [n_plaq];
  }

  std::stringstream ss;
  ofstream file;

  cout << setprecision(15);
  Stopwatch timer;
  int conf = 0;
  do {

    timer.Restart();

    if ( conf%n_chkpt==0 ) {
    
      std::cout << "\t";
      std::cout << "Computing observables..." << std::endl;

      monster.Initialize(lattice);
      for (int m=0; m<n_plaq; ++m)
      for (int n=0; n<n_plaq; ++n) {
        plaq[m][n].push_back( 1.0-monster.MeanPlaquette(m+1,n+1) );
      }

      std::cout << "\t";
      std::cout << "Saving configuration..." << std::endl;
      ss.str(std::string());
      ss << cfg_file_stem << "-" << conf << ".bin";
      std::cout << "\t";
      lattice.Write(ss.str());

    }
 
    lattice.HeatBathUpdate(beta);
    std::cout << "Total time for config " << conf << " is : " << timer.ElapsedTime() << std::endl;
    ++conf;

  } while (conf < n_conf);


//// Write observables to a file ////

  for (int m=0; m<n_plaq; ++m)
  for (int n=0; n<n_plaq; ++n) {
    ss.str(std::string());
    ss << plaq_file_stem << "-" << m+1 << "_" << n+1 << ".dat";
    std::cout << "Writing observables to file : ";
    std::cout << ss.str()  << std::endl;
    file.open(ss.str().c_str());
    file << setprecision(15);
    for(int j=0; j<plaq[m][n].size(); ++j) {
      file << plaq[m][n][j] << std::endl;
    }
    file.close();
  }

//// DONE! ////

  for (int i=0; i<n_plaq; ++i) {
    delete [] plaq[i];
  }
  delete [] plaq;

  cout << "Congratulations on a job... done!" << endl;
  exit(EXIT_SUCCESS);

}


