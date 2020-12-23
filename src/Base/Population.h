#ifndef EmiR_Population_h
#define EmiR_Population_h

#include "SearchSpace.h"
#include "OOB.h"
#include <random>
#include <Rcpp.h>
using namespace Rcpp;

class Population {

  typedef typename std::uniform_real_distribution<double>::param_type rand_pt;
  typedef typename std::uniform_int_distribution<int>::param_type rint_pt;

public:

  Population(Function);

  void setSearchSpace(const SearchSpace&);

  void setConstraints(List);

  void setOOB(OOBMethod);

protected:

  double getRand_0_1();

  double getRand_1_1();

  int genIntRand(int, int);

  void checkBoundary(double&, double&, size_t);

  double evaluateCost(const std::vector<double>&);

  std::mt19937 m_mt;
  SearchSpace  m_search_space;
  Function     m_obj_func;
  List         m_constraints;
  OOBMethod    m_oob_sol;

  rand_pt      m_pt_0_1;
  rand_pt      m_pt_1_1;
  std::uniform_real_distribution<double> m_rand_0_1;
  std::uniform_real_distribution<double> m_rand_1_1;
  std::uniform_int_distribution<int>  m_int_rand;
};

#endif
