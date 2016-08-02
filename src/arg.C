#ifndef INCLUDED_ARG_C
#define INCLUDED_ARG_C

#include <cstdlib>
#include <iostream>
#include "arg.h"

Arg::Arg()
{
}

Arg::~Arg()
{
}

bool Arg::OpenFile(std::string filename)
{
  std::cout << "Importing : ";
  std::cout << filename << std::endl;
  file.open(filename.c_str());
  if (!file) { return false; } else { return true; }
}

void Arg::CloseFile()
{
//  std::cout << "Closing file" << std::endl;
  file.close();
}

template <typename T>
bool Arg::ReadLine(T &param) {
  file >> param;
  if ( file.eof() ) { return true; } else { return false; };
}

bool Arg::ReadLine(enum lat_state &param) {
  std::string state;
  file >> state;
  if (state=="ORDERED") {
    param = ORDERED;
  } else if (state=="DISORDERED") {
    param = DISORDERED;
  } else {
    std::cout << "State must be ORDERED or DISORDERED" << std::endl;
    exit(EXIT_FAILURE);
  }
  if ( file.eof() ) { return true; } else { return false; };
}


LatticeArg::LatticeArg(std::string filename)
{
  if ( !Decode(filename) ) {
    std::cout << "Failed to decode : ";
    std::cout << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}

bool LatticeArg::Decode(std::string filename)
{
  if ( !OpenFile(filename) ) return false;
  ReadLine( state );
  std::cout << "\t";
  std::cout << "LatticeArg::state : " << state;
  std::cout << std::endl;
  for (int mu=0; mu<4; ++mu) {
    ReadLine( sites[mu]);
    std::cout << "\t";
    std::cout << "LatticeArg::sites["<<mu<<"] : " << sites[mu];
    std::cout << std::endl;
  }
  CloseFile();
  return true;
}

LatticeArg::~LatticeArg()
{
}

EvoArg::EvoArg(std::string filename)
{
  if ( !Decode(filename) ) {
    std::cout << "Failed to decode : ";
    std::cout << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}

bool EvoArg::Decode(std::string filename)
{
  if ( !OpenFile(filename) ) return false;
  ReadLine( n_conf );
  std::cout << "\t";
  std::cout << "EvoArg::n_conf : " << n_conf;
  std::cout << std::endl;
  ReadLine( n_chkpt );
  std::cout << "\t";
  std::cout << "EvoArg::n_chkpt : " << n_chkpt;
  std::cout << std::endl;
  ReadLine( file_stem );
  std::cout << "\t";
  std::cout << "EvoArg::file_stem : " << file_stem;
  std::cout << std::endl;
  CloseFile();
  return true;
}

EvoArg::~EvoArg()
{
}

CouplingArg::CouplingArg(std::string filename)
{
  if ( !Decode(filename) ) {
    std::cout << "Failed to decode : ";
    std::cout << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}

bool CouplingArg::Decode(std::string filename)
{
  if ( !OpenFile(filename) ) return false;
  ReadLine( beta );
  std::cout << "\t";
  std::cout << "CouplingArg::beta: " << beta;
  std::cout << std::endl;
  CloseFile();
  return true;
}

CouplingArg::~CouplingArg()
{
}

RethermArg::RethermArg(std::string filename)
{
  if ( !Decode(filename) ) {
    std::cout << "Failed to decode : ";
    std::cout << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}

bool RethermArg::Decode(std::string filename)
{
  if ( !OpenFile(filename) ) return false;
  ReadLine( sweeps );
  std::cout << "\t";
  std::cout << "RethermArg::sweeps: " << sweeps;
  std::cout << std::endl;
  CloseFile();
  return true;
}

RethermArg::~RethermArg()
{
}

PlaquetteArg::PlaquetteArg(std::string filename)
{
  if ( !Decode(filename) ) {
    std::cout << "Failed to decode : ";
    std::cout << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}

bool PlaquetteArg::Decode(std::string filename)
{
  if ( !OpenFile(filename) ) return false;
  ReadLine( n_plaq );
  std::cout << "\t";
  std::cout << "PlaquetteArg::n_plaq: " << n_plaq;
  std::cout << std::endl;
  ReadLine( file_stem );
  std::cout << "\t";
  std::cout << "PlaquetteArg::file_stem: " << file_stem;
  std::cout << std::endl;
  CloseFile();
  return true;
}

PlaquetteArg::~PlaquetteArg()
{
}



#endif
