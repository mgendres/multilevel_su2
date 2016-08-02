#include <string>
//#include <vector>
#include <fstream>
#include "lattice.h"

#ifndef INCLUDED_ARG
#define INCLUDED_ARG


class Arg
{
  private:
    std::ifstream file;
    std::string input;
  public:
    explicit Arg();
    virtual ~Arg();
    virtual bool Decode(std::string)=0;
    bool OpenFile(std::string);
    void CloseFile();

    template <typename T>
    bool ReadLine(T &);
    bool ReadLine(enum lat_state &);

};


class LatticeArg : public Arg
{
  private:
    explicit LatticeArg();
  public:
    explicit LatticeArg(std::string);
    ~LatticeArg();
    bool Decode(std::string);
    int sites[4];
    enum lat_state state;
};

class EvoArg : public Arg
{
  private:
    explicit EvoArg();
  public:
    explicit EvoArg(std::string);
    ~EvoArg();
    bool Decode(std::string);
    int n_conf;
    int n_chkpt;
    std::string file_stem;
};

class CouplingArg : public Arg
{
  private:
    explicit CouplingArg();
  public:
    explicit CouplingArg(std::string);
    ~CouplingArg();
    bool Decode(std::string);
    double beta;
};

class RethermArg : public Arg
{
  private:
    explicit RethermArg();
  public:
    explicit RethermArg(std::string);
    ~RethermArg();
    bool Decode(std::string);
    double sweeps;
};

class PlaquetteArg : public Arg
{
  private:
    explicit PlaquetteArg();
  public:
    explicit PlaquetteArg(std::string);
    ~PlaquetteArg();
    bool Decode(std::string);
    double n_plaq;
    std::string file_stem;
};




#include "arg.C"

#endif
