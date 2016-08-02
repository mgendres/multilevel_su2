#include "utils.h"

#ifndef INCLUDED_SUBSET
#define INCLUDED_SUBSET

class Subset
{
  private:

    Subset& operator=(const Subset&);
    Subset(const Subset&);

  public:
    explicit Subset();
    ~Subset();

    virtual int NumSubsets() const = 0;
    virtual int operator()(int, const int*) const = 0;

};

class CompositeSubset : public Subset
{
  private:

    int num_subsets;
    const Subset & A;
    const Subset & B;

    CompositeSubset& operator=(const CompositeSubset&);
    CompositeSubset(const Subset&);
    CompositeSubset();

  public:
    explicit CompositeSubset(const Subset&, const Subset&);
    ~CompositeSubset();

    virtual int NumSubsets() const;
    virtual int operator()(int, const int*) const;

};


class AllSubset : public Subset
{
  private:

    int num_subsets;

    AllSubset& operator=(const AllSubset&);
    AllSubset(const Subset&);

  public:
    explicit AllSubset();
    ~AllSubset();

    virtual int NumSubsets() const;
    virtual int operator()(int, const int*) const;

};



class CheckerBoardSubset : public Subset 
{
  private:
    int num_subsets;

    CheckerBoardSubset& operator=(const CheckerBoardSubset&);
    CheckerBoardSubset(const CheckerBoardSubset&);

  public:
    explicit CheckerBoardSubset();
    ~CheckerBoardSubset();

    int NumSubsets() const; 
    int operator()(int, const int*) const;

};

class TwoCellBulkSubset : public Subset 
{
  private:
    int num_subsets;

    TwoCellBulkSubset& operator=(const TwoCellBulkSubset&);
    TwoCellBulkSubset(const TwoCellBulkSubset&);

  public:
    explicit TwoCellBulkSubset();
    ~TwoCellBulkSubset();

    int NumSubsets() const; 
    int operator()(int, const int*) const;

};

class TwoCellNoEdgeSubset : public Subset 
{
  private:
    int num_subsets;

    TwoCellNoEdgeSubset& operator=(const TwoCellNoEdgeSubset&);
    TwoCellNoEdgeSubset(const TwoCellNoEdgeSubset&);

  public:
    explicit TwoCellNoEdgeSubset();
    ~TwoCellNoEdgeSubset();

    int NumSubsets() const; 
    int operator()(int, const int*) const;

};

class TwoCellNoRootEdgeSubset : public Subset 
{
  private:
    int num_subsets;

    TwoCellNoRootEdgeSubset& operator=(const TwoCellNoRootEdgeSubset&);
    TwoCellNoRootEdgeSubset(const TwoCellNoRootEdgeSubset&);

  public:
    explicit TwoCellNoRootEdgeSubset();
    ~TwoCellNoRootEdgeSubset();

    int NumSubsets() const; 
    int operator()(int, const int*) const;

};

namespace Subsets{
  extern const AllSubset all;
  extern const CheckerBoardSubset checker_board;
  extern const TwoCellBulkSubset two_cell_bulk;
  extern const TwoCellNoEdgeSubset two_cell_no_edge;
  extern const TwoCellNoRootEdgeSubset two_cell_no_root_edge;
  extern const CompositeSubset two_cell_bulk_checker_board;
  extern const CompositeSubset two_cell_no_edge_checker_board;
  extern const CompositeSubset two_cell_no_root_edge_checker_board;
}

#endif
