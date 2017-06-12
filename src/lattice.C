#include "lattice.h"
#include "constants.h"
#include "mt19937.h"
#include "utils.h"
#include "subset.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>

Lattice::Lattice(int* my_sites)
{

  volume = 1;
  for (int mu=0; mu<4; ++mu) {
     sites[mu] = my_sites[mu];
     volume *= sites[mu];
  }

  gauge_field_size = 4*volume;
  gauge_field = new Matrix [gauge_field_size]; // [mu][z][y][x][t]
  Initialize(ORDERED);

}

Lattice::~Lattice()
{
  delete[] gauge_field;
}

void Lattice::Initialize(enum lat_state state, const Subset& subset)
{

  int s[4];
  for ( int set=0; set<subset.NumSubsets(); ++set)
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu)
  if ( set==subset(mu,s) ) {
    if (state==ORDERED) {
      GaugeField(mu,s).Diagonal(1.0);
    }
    if (state==DISORDERED) {
      GaugeField(mu,s).RandomSU2();   
    }
  }
}

void Lattice::Initialize(enum lat_state state)
{
  Initialize(state, Subsets::all);
}

int Lattice::SiteIndex(const int* s) const
{
  int t[4];
  for (int nu=0; nu<4; ++nu) { t[nu] = ( s[nu]+sites[nu] ) % sites[nu]; } // Impose PBCs
  int idx = t[3]+sites[3]*( t[2] + sites[2]*( t[1]+ sites[1]*t[0] ) );
  return idx;
}

int Lattice::GaugeIndex(int mu, const int* s) const { return mu + 4*SiteIndex(s); }

Matrix& Lattice::GaugeField(int idx) { return gauge_field[idx]; }

Matrix& Lattice::GaugeField(int idx) const { return gauge_field[idx]; }

Matrix& Lattice::GaugeField(int mu, const int* s) const
{
  int idx = GaugeIndex(mu, s);
  return gauge_field[idx];
}

Matrix& Lattice::GaugeField(int mu, const int* s)
{
  int idx = GaugeIndex(mu, s);
  return gauge_field[idx];
}

double Lattice::Plaquette(int mu, int m, int nu, int n, const int* t)
{
  int s[4]; for (int i=0; i<4; ++i) s[i] = t[i];
  Matrix P;
  P.Diagonal(1.0);
  for (int i=0; i<m; ++i) {
    P *= GaugeField(mu,s);
    s[mu]++;
  }
  for (int i=0; i<n; ++i) {
    P *= GaugeField(nu,s);
    s[nu]++;
  }
  for (int i=0; i<m; ++i) {
    s[mu]--;
    P *= GaugeField(mu,s).Dagger();
  }
  for (int i=0; i<n; ++i) {
    s[nu]--;
    P *= GaugeField(nu,s).Dagger(); 
  }
  return P.Tr();
}

double Lattice::MeanLink()
{
  double link = 0.0;
  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {
    link += GaugeField(mu, s).Tr();
  }
  link /= 2*4*volume;
  return link;

}

double Lattice::MeanPlaquette()
{

  double plaquette = 0.0;
  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] ) {
    for (int mu=0; mu<4; ++mu)
    for (int nu=0; nu<mu; ++nu) {
      plaquette += Plaquette(mu, 1, nu, 1, s);
    }
  }
  plaquette /= 2*6*volume;
  return plaquette;
}

double Lattice::MeanPlaquette(int m, int n)
{

  double plaquette = 0.0;
  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] ) {
    for (int mu=0; mu<4; ++mu)
    for (int nu=0; nu<mu; ++nu) {
      plaquette += Plaquette(mu, m, nu, n, s);
    }
  }
  plaquette /= 2*6*volume;
  return plaquette;
}

Matrix Lattice::Staple(int mu, const int* t)
{
  int s[4]; for (int i=0; i<4; ++i) s[i] = t[i];
  Matrix U(0.0,0.0,0.0,0.0);
  Matrix P;
  for (int nu=0; nu<4; ++nu) {
    if (mu!=nu) {
      // forward staple
      P.Diagonal(1.0);
      P *= GaugeField(nu,s);
      s[nu] += 1;
      P *= GaugeField(mu,s);
      s[nu] -= 1;
      s[mu] += 1;
      P *= GaugeField(nu,s).Dagger();
      U += P;
      // backward staple
      P.Diagonal(1.0);
      s[nu] -= 1;
      P *= GaugeField(nu,s).Dagger();
      s[mu] -= 1;
      P *= GaugeField(mu,s).Dagger();
      P *= GaugeField(nu,s);
      s[nu] += 1;
      U += P.Dagger();
    }
  }
  return U;
}


void Lattice::GlobalTransform(Matrix v)
{

  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {
    GaugeField(mu,s) = v * GaugeField(mu,s);   
    GaugeField(mu,s) *= v.Dagger();   
  }
  
}

void Lattice::RandomGaugeTransform()
{

  int s[4];
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] ) {

    Matrix v;
    v.RandomSU2();

    for (int mu=0; mu<4; ++mu) {
      GaugeField(mu,s) = v * GaugeField(mu,s);   
      s[mu] -= 1;
      GaugeField(mu,s) *= v.Dagger();   
      s[mu] += 1;
    }
  }

}

double Lattice::HeatBathUpdate(double beta, const Subset& subset)
{
  int s[4];
  Matrix S;
  double k;
  for ( int set=0; set<subset.NumSubsets(); ++set)
  for (int mu=0; mu<4; ++mu)
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  if ( set==subset(mu,s) ) {
    S = Staple(mu,s).Dagger();
    k = sqrt( S.Det() );
    S /= k;
    GaugeField(mu,s).RandomSU2(k*beta);
    GaugeField(mu,s) /= S;
  }
  return 1.0;
}

double Lattice::HeatBathUpdate(double beta)
{
  return HeatBathUpdate(beta, Subsets::checker_board);
}

double Lattice::SweepUpdate(double beta, double eps)
{

  double accepts = 0.0;
  int s[4];
  double a0;
  double a1;
  double da;
  Matrix U;
  Matrix S;
  Matrix V;
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {

    // Get current link
    U = GaugeField(mu,s);

    // Get the staple, get the current action
    S = Staple(mu,s);
    a0 = -0.5*( S * U.Dagger() ).Tr();

    // Propose small change to link, get proposed action
    double alpha = 2.0 * PI * rng.genrand_res53();
    alpha *= eps;
    double theta = PI * rng.genrand_res53();
    double phi = 2.0 * PI * rng.genrand_res53();
    V.EulerSU2(alpha,theta,phi);
    U *=  V;
    a1 = -0.5*( S * U.Dagger() ).Tr();

    da = a1-a0;
    if ( exp(-beta*da) > rng.genrand_res53() ) {
      GaugeField(mu,s) = U;   
      accepts += 1.0;
    } 

  }
  accepts /= gauge_field_size;
  return accepts;
}


double Lattice::MeanPolyakovLoop()
{

  int s[4];
  double loop = 0.0;
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] ) {
    Matrix L;
    for ( s[0]=0; s[0]<sites[0]; ++s[0] ) {
      L *= GaugeField(0,s);
    }
    loop += L.Tr();
  }

  loop /= 2.0*sites[1]*sites[2]*sites[3];
  return loop;

}


void Lattice::MaximalTreeGaugeFix()
{

  int s[4]; for (int mu=0; mu<4; ++mu) { s[mu] = 0.0; }

  for ( s[0]=sites[0]-1; s[0]>0; --s[0] ) {
    UnitLinkGaugeFix(0,s);
  }

  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=sites[1]-1; s[1]>0; --s[1] ) {
    UnitLinkGaugeFix(1,s);
  }

  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=sites[2]-1; s[2]>0; --s[2] ) {
    UnitLinkGaugeFix(2,s);
  }

  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=sites[3]-1; s[3]>0; --s[3] ) {
    UnitLinkGaugeFix(3,s);
  }

}

double Diff(Lattice& lattice0, Lattice& lattice1)
{
  // This function determines if two lattices are gauge equivalent

  for (int mu=0; mu<4; ++mu) {
    if ( lattice0.sites[mu] != lattice1.sites[mu]) {
      std::cout << "Lattices are of different sizes!" << std::endl;
      exit(EXIT_FAILURE);
    }
  } 

  // Maximal tree gauge fixing
  lattice0.MaximalTreeGaugeFix();
  lattice1.MaximalTreeGaugeFix();

  // Currently, this comparison doesn't account for a possible global
  // transformation on the lattice. For example,
  // A = a_0 + I a_j \sigma_j
  // B = \Omega A \Omega^\dagger = a_0 + I a_j \Omega \sigma_j \Omega^\dagger
  // Also note that eigenvalues of an SU(2) matrix are (a_0 +- i \sqrt{1-a_0^2} ),
  // so agreement in a_0 is a start.

//// To confirm the rest:
//// Begin by selecting two links in maximal tree gauge that were not set to unity
//// In this case I picked the first site and 0 direction
  int s[4] = {0,0,0,0};
  int mu = 0;
  Matrix X = lattice0.GaugeField(mu, s);
  Matrix Y = lattice1.GaugeField(mu, s);
  std::cout << X << std::endl;
  std::cout << Y << std::endl;
  // Then find the transformation that takse X to Y
  Matrix V = X.RelationalTransformation(Y);
  // Finally perform global transformation on the lattice so that X = Y
  lattice0.GlobalTransform(V);
  std::cout << lattice0.GaugeField(mu, s) << std::endl;
  std::cout << lattice1.GaugeField(mu, s) << std::endl;

// After performing this transformation, 
// lattice0.GaugeField(mu, s) == lattice1.GaugeField(mu, s) = Y
// But there still remains a residual freedom to rotate either field by Y^alpha since Y
// commutes with itself and the links set to unity.
// We may determine alpha numerically. There is probably a fancy analytic formula, but
// I'll take the lazy route. Not even Newton's method lazy, but worse.

  Matrix diff;
  double d2;
  {
    double pow(0.1);
    double thresh(1.0);
    int step_count(0);
    do {
      step_count +=1;
      lattice1.GlobalTransform(Y.Power( pow ));
      diff = lattice0.GaugeField( (mu+5)%4 , s);
      diff -= lattice1.GaugeField( (mu+5)%4, s);
      diff *= diff.Dagger();
      d2 = sqrt( diff.Tr() );
      std::cout << step_count << " " << d2 << " " << thresh << std::endl;
      if (d2> thresh) {
        if (step_count==2) {
          pow *= 0.1;
        }
        pow *= -1.0;
        step_count = 0;
      }
      thresh = d2;
    } while ( d2 > 1e-12 );
  }

  d2 = 0.0;
  for ( s[0]=0; s[0]<lattice0.sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<lattice0.sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<lattice0.sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<lattice0.sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu) {
//    std::cout << lattice0.GaugeField(mu,s) << std::endl;
//    std::cout << lattice1.GaugeField(mu,s) << std::endl;
    diff =  lattice0.GaugeField(mu,s) - lattice1.GaugeField(mu,s);
    diff *= diff.Dagger();
    d2 += sqrt( diff.Tr() );
  } 
  std::cout << "Trace difference squared (total over lattice): " << d2 << std::endl;

  return d2;

}



bool Copy(const Lattice& source, Lattice& target)
{
  for (int i=0; i<4; ++i) {
    if ( source.sites[i] != target.sites[i]) {
      return false;
    }
  } 

  for (int i=0; i<source.gauge_field_size; ++i) {
    target.gauge_field[i] = source.gauge_field[i];
  }
  return true;

}

void Lattice::UnitLinkGaugeFix(int mu, const int* t)
{

  int s[4]; for (int nu=0; nu<4; ++nu) s[nu] = t[nu];
  Matrix V = GaugeField(mu,s);
  for (int nu=0; nu<4; ++nu) {
    GaugeField(nu,s) = V.Dagger() * GaugeField(nu,s);   
    s[nu]--;
    GaugeField(nu,s) *= V;
    s[nu]++;
  }

}

void Lattice::TwoCellCanonicalGaugeFix()
{

  int s[4]; for (int mu=0; mu<4; ++mu) s[mu] = sites[mu];
  if ( !TwoCellRootSiteQ(s) ) {
    std::cout << "Number of sites must be even in each direction" << std::endl;
    exit(EXIT_FAILURE);
  }

  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  if ( TwoCellRootSiteQ(s) )
  for (int mu=0; mu<4; ++mu)  {
      s[mu]++;
      UnitLinkGaugeFix(mu,s);
      s[mu]--;
  }

}

bool Decimate(Lattice& source, Lattice& target)
{

  for (int mu=0; mu<4; ++mu) {
    if ( source.sites[mu] != 2*target.sites[mu]) {
      return false;
    }
  }

  source.TwoCellCanonicalGaugeFix();

  int t[4];
  int s[4];
  for ( t[0]=0; t[0]<target.sites[0]; ++t[0] )
  for ( t[1]=0; t[1]<target.sites[1]; ++t[1] )
  for ( t[2]=0; t[2]<target.sites[2]; ++t[2] )
  for ( t[3]=0; t[3]<target.sites[3]; ++t[3] ) {
    for (int mu=0; mu<4; ++mu) s[mu] = 2*t[mu];
    for (int mu=0; mu<4; ++mu) target.GaugeField(mu,t) = source.GaugeField(mu,s);
  }

  return true;

}

bool Refine(Lattice& source, Lattice& target)
{

  for (int mu=0; mu<4; ++mu) {
    if ( 2*source.sites[mu] != target.sites[mu]) {
      return false;
    }
  }

  target.Initialize(ORDERED);

  int t[4];
  int s[4];
  for ( s[0]=0; s[0]<source.sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<source.sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<source.sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<source.sites[3]; ++s[3] ) {
    for (int mu=0; mu<4; ++mu) t[mu] = 2*s[mu];
    for (int mu=0; mu<4; ++mu) target.GaugeField(mu,t) = source.GaugeField(mu,s);
  }

  return true;

}

bool CanonicalRefine(Lattice& source, Lattice& target)
{

  //
  //           C              1
  //   |---------------|--------------|
  //   |               |              |
  //   |               |              |
  //   |               |              |
  //   |               |              |
  // 1 |               | 1            | 1
  //   |               |              |
  //   |      C        |      1       |
  //   |---------------|--------------|
  //   |               |              |
  //   |               |              |
  //   |               |              |
  //   |               |              |
  // D |               | B            | B
  //   |               |              |
  //   |               |              |
  //   |---------------|--------------|
  //           A              1
  //

  if ( !Refine(source,target) ) return false;

  int s[4];
  Matrix U;
  for ( s[0]=0; s[0]<target.sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<target.sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<target.sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<target.sites[3]; ++s[3] )
  if ( TwoCellRootSiteQ(s) )
  for (int mu=0; mu<4; ++mu) {
    U = target.GaugeField(mu,s);
    for (int nu=0; nu<4; ++nu) {
      if(nu!=mu) {
        s[nu]--;
        target.GaugeField(mu,s) = U;
        for (int sigma=0; sigma<nu; ++sigma) {
          if(sigma!=mu) {
            s[sigma]--;
            target.GaugeField(mu,s) = U;
            for (int rho=0; rho<sigma; ++rho) {
              if(rho!=mu) {
                s[rho]--;
                target.GaugeField(mu,s) = U;
                s[rho]++;
              } 
            } 
            s[sigma]++;
          } 
        }
        s[nu]++;
      }
    }
  }

  return true;

}






bool InterpolatedTwoCellBoundaryRefine(Lattice& source, Lattice& target)
{

  // Fill in the two-cell plaquette links
  //
  //           C              1
  //   |---------------|--------------|
  //   |               |              |
  //   |               |              |
  //   |               |              |
  //   |               |              |
  // 1 |               | 1            | 1
  //   |               |              |
  //   |   C*Uq        |    Uq        |
  //   |---------------|--------------|
  //   |               |              |
  //   |               |              |
  //   |               |              |
  //   |               |              |
  // D |               | B/Uh         | B
  //   |               |              |
  //   |               |              |
  //   |---------------|--------------|
  //           A              1
  //
  //  U = C.Dagger() * D.Dagger() * A * B
  //
  //  Uh = U.Power(0.5)
  //  Uq = U.Power(0.25)
  // 

  if ( !Refine(source,target) ) return false;

  int s[4];
  Matrix A, B, C, D;
  Matrix U, Uh, Uq;
  for ( s[0]=0; s[0]<target.sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<target.sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<target.sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<target.sites[3]; ++s[3] )
  if ( TwoCellRootSiteQ(s) )
  for (int mu=0; mu<4; ++mu)
  for (int nu=0; nu<mu; ++nu) {
    A = target.GaugeField(mu,s);
    D = target.GaugeField(nu,s);
    s[nu] += 2;
    C = target.GaugeField(mu,s);
    s[nu] -= 2;
    s[mu] += 2;
    B = target.GaugeField(nu,s);
    s[mu] -= 2;
    U = C.Dagger();
    U *= D.Dagger();
    U *= A;
    U *= B;
    Uh = U.Power(0.5);
    Uq = U.Power(0.25);
    s[nu]+=1;
    target.GaugeField(mu,s) = C*Uq;
    s[mu]+=1;
    target.GaugeField(mu,s) = Uq;
    s[nu]-=1;
    target.GaugeField(nu,s) = B/Uh;
    s[mu]-=1;
  }

  return true;

}




std::ostream& operator<<(std::ostream& out, const Lattice& lat)
{

  int s[4];
  for ( s[0]=0; s[0]<lat.sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<lat.sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<lat.sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<lat.sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu)  {
    out << lat.GaugeIndex(mu,s) <<  " : ";
    out << s[0] <<  " ";
    out << s[1] <<  " ";
    out << s[2] <<  " ";
    out << s[3] <<  " ";
    out << mu <<  " : ";
    out << lat.GaugeField(mu,s) << std::endl;
  }
  return out;
}

double Lattice::CoolUpdate()
{
  return CoolUpdate(Subsets::checker_board);
}

double Lattice::CoolUpdate(const Subset& subset)
{
  int s[4];
  Matrix S;
  double k;
  for ( int set=0; set<subset.NumSubsets(); ++set)
  for ( s[0]=0; s[0]<sites[0]; ++s[0] )
  for ( s[1]=0; s[1]<sites[1]; ++s[1] )
  for ( s[2]=0; s[2]<sites[2]; ++s[2] )
  for ( s[3]=0; s[3]<sites[3]; ++s[3] )
  for (int mu=0; mu<4; ++mu)
  if ( set==subset(mu,s) ) {
    S = Staple(mu,s).Dagger();
    k = sqrt( S.Det() );
    S /= k;
    GaugeField(mu,s) = S.Inverse();
  }
  return 1.0;
}

bool Lattice::Read(std::string s)
{
  std::ifstream file( s.c_str(), std::ios::binary);
  if (!file) return false;
  std::cout << "Reading lattice from file : " << s << std::endl;
  int t[4];
  file.read(reinterpret_cast<char*>(t), sizeof(int)*4);
  for (int mu=0;mu<4;++mu) {
    if (t[mu] != sites[mu]) return false;
  }
  file.read(reinterpret_cast<char*>(gauge_field), sizeof(Matrix)*gauge_field_size);
  file.close();
  return true;
}

bool Lattice::Write(std::string s)
{
  std::ofstream file( s.c_str(), std::ios::binary);
  if (!file) return false;
  std::cout << "Writing lattice to file : " << s << std::endl;
  file.write(reinterpret_cast<const char*>(sites), sizeof(int)*4);
  file.write(reinterpret_cast<const char*>(gauge_field), sizeof(Matrix)*gauge_field_size);
  file.close();
  return true;
}
