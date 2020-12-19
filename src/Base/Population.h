#ifndef EmiR_Population_h
#define EmiR_Population_h

#include "SearchSpace.h"
#include <random>
#include <Rcpp.h>
using namespace Rcpp;

class Population {
public:

  Population(Function);

  void setSearchSpace(const SearchSpace&);

  void setConstraints(List);

protected:

  std::mt19937 m_mt;
  SearchSpace  m_search_space;
  Function     m_obj_func;
  List         m_constraints;
};

#endif
