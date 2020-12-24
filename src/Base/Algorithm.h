#ifndef EmiR_Algorithm_h
#define EmiR_Algorithm_h

#include "SearchSpace.h"
#include "Utility.h"
#include "OOB.h"
#include <Rcpp.h>
#include <vector>
#include <string>
#include <random>

using namespace Rcpp;

class Algorithm {
public:
  Algorithm(Function);

  void setConstraints(List);
  void setParameters(List);
  void savePopulation(bool);
  void setSilent(bool);
  void setOOB(std::string);

protected:

  Function m_obj_function;
  List                              m_constraints;
  SearchSpace                       m_search_space;
  std::mt19937                      m_mt;
  std::vector<std::string>          m_parameter_names;
  std::vector<std::vector<double> > m_parameter_range;
  std::vector<double>               m_cost_history;
  List                              m_population_position;
  bool                              m_save_population;
  bool                              m_silent;
  OOBMethod                         m_oob_sol;
};

#endif
