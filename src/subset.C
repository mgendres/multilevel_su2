#include "subset.h"

Subset::Subset(){}

Subset::~Subset(){}



CompositeSubset::CompositeSubset(const Subset& x, const Subset& y) : A(x), B(y) {}

CompositeSubset::~CompositeSubset() {}

int CompositeSubset::NumSubsets() const { return A.NumSubsets() * B.NumSubsets(); }

int CompositeSubset::operator()(int mu, const int* s) const
{
  int a = A(mu,s);
  if (a<0) { return -1; }
  int b = B(mu,s);
  if (b<0) { return -1; }
  return a + A.NumSubsets() * b;
}



AllSubset::AllSubset() : num_subsets(1) {}

AllSubset::~AllSubset() {}

int AllSubset::NumSubsets() const { return num_subsets; }

int AllSubset::operator()(int, const int*) const
{
  return 0;
}



CheckerBoardSubset::CheckerBoardSubset() : num_subsets(2) {}

CheckerBoardSubset::~CheckerBoardSubset() {}

int CheckerBoardSubset::NumSubsets() const { return num_subsets; }

int CheckerBoardSubset::operator()(int mu, const int* s) const
{
  return ( (s[0]+s[1]+s[2]+s[3]) % 2 == 0 ? 0 : 1);
}



TwoCellBulkSubset::TwoCellBulkSubset() : num_subsets(1) {}

TwoCellBulkSubset::~TwoCellBulkSubset() {}

int TwoCellBulkSubset::NumSubsets() const { return num_subsets; }

int TwoCellBulkSubset::operator()(int mu, const int* s) const
{
  if ( !(TwoCellRootSiteQ(s)||TwoCellBoundaryLinkQ(mu,s)) ) {
    return 0;
  } else{ 
    return -1;
  }
}



TwoCellNoEdgeSubset::TwoCellNoEdgeSubset() : num_subsets(1) {}

TwoCellNoEdgeSubset::~TwoCellNoEdgeSubset() {}

int TwoCellNoEdgeSubset::NumSubsets() const { return num_subsets; }

int TwoCellNoEdgeSubset::operator()(int mu, const int* s) const
{

  bool b(false);

  for (int nu=0; nu<4; ++nu) {
    b = b || ( s[nu]%2!=0 );
  }
  if (!b) return -1;

  b = true;
  for (int nu=0; nu<4; ++nu) {
    if (nu!=mu) { b = b && (s[nu]%2==0); }
  }
  b = b && ( (s[mu]+1)%2==0 );
  if (b) return -1;

  return 0;

}


TwoCellNoRootEdgeSubset::TwoCellNoRootEdgeSubset() : num_subsets(1) {}

TwoCellNoRootEdgeSubset::~TwoCellNoRootEdgeSubset() {}

int TwoCellNoRootEdgeSubset::NumSubsets() const { return num_subsets; }

int TwoCellNoRootEdgeSubset::operator()(int mu, const int* s) const
{

  bool b(false);
  for (int nu=0; nu<4; ++nu) {
    b = b || ( s[nu]%2!=0 );
  }
  if (b) return 0;
  return -1;

}

namespace Subsets{
  const AllSubset all;
  const CheckerBoardSubset checker_board;
  const TwoCellBulkSubset two_cell_bulk;
  const TwoCellNoEdgeSubset two_cell_no_edge;
  const TwoCellNoRootEdgeSubset two_cell_no_root_edge;
  const CompositeSubset two_cell_bulk_checker_board(two_cell_bulk, checker_board);
  const CompositeSubset two_cell_no_edge_checker_board(two_cell_no_edge, checker_board);
  const CompositeSubset two_cell_no_root_edge_checker_board(two_cell_no_root_edge, checker_board);
}
