#include "utils.h"

bool TwoCellRootSiteQ(const int* s)
{
  if ( (s[0]%2==0)&&(s[1]%2==0)&&(s[2]%2==0)&&(s[3]%2==0) ) {
    return true;
  }
  return false;
}

bool TwoCellBoundaryLinkQ(int sigma, const int* t)
{
  int s[4]; for (int i=0; i<4; ++i) s[i] = t[i];
  if ( TwoCellRootSiteQ(s) ) return true;
  for (int mu=0; mu<4; ++mu) {
    s[mu]++;
    if ( TwoCellRootSiteQ(s) ) return true;
    for (int nu=0; nu<mu; ++nu) {
      s[nu]++;
      if ( TwoCellRootSiteQ(s) ) {
        if ( (sigma==mu)||(sigma==nu) ) return true;
      }
      s[nu]--;
    }
    s[mu]--;
  }
  return false;
}
