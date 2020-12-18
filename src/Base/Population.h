#ifndef EmiR_Population_h
#define EmiR_Population_h

#include "ParametersRange.h"
#include <random>
#include <Rcpp.h>
using namespace Rcpp;

class Population {
public:

  Population(Function);

  void setParRange(const ParametersRange&);

  void setConstraints(List);

protected:

  std::mt19937        m_mt;
  ParametersRange     m_par_range;
  Function            m_obj_func;
  List                m_constraints;
};

#endif
