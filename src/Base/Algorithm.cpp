#include "Algorithm.h"
#include <Rcpp.h>
using namespace Rcpp;


Algorithm::Algorithm(Function obj_function) :
m_obj_function(obj_function),
m_mt((std::random_device())()),
m_save_population(false),
m_silent(false),
m_oob_sol(RBC) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setConstraints(List constraints) {
  m_constraints = constraints;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setParameters(List parameters) {
  int n = parameters.length();
  m_search_space = SearchSpace(n);
  m_parameter_range = std::vector<std::vector<double> >(n);

  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    m_search_space.setParameter(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
    m_parameter_range[i] = {par.slot("min_val"), par.slot("max_val")};
    m_parameter_names.push_back(par.slot("name"));
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::savePopulation(bool t) {
  m_save_population = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setSilent(bool t) {
  m_silent = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setOOB(std::string t) {
  if (t == "PBC") {
    m_oob_sol = PBC;
  } else if (t == "BAB") {
    m_oob_sol = BAB;
  } else if (t == "DIS") {
    m_oob_sol = DIS;
  } else if (t == "RBC") {
    m_oob_sol = RBC;
  } else {
    Rcout << "Unknown OOB method '" << t << "', using default.\n";
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
