#ifndef EmiR_Population_h
#define EmiR_Population_h

#include "SearchSpace.h"
#include <random>
#include <Rcpp.h>
using namespace Rcpp;

class Population {

  typedef typename std::uniform_real_distribution<double>::param_type rand_pt;

public:

  Population(Function);

  void setSearchSpace(const SearchSpace&);

  void setConstraints(List);

protected:

  double getRand_0_1();

  double getRand_1_1();

  std::mt19937 m_mt;
  SearchSpace  m_search_space;
  Function     m_obj_func;
  List         m_constraints;

  rand_pt      m_pt_0_1;
  rand_pt      m_pt_1_1;
  std::uniform_real_distribution<double> m_rand_0_1;
  std::uniform_real_distribution<double> m_rand_1_1;
};

#endif
