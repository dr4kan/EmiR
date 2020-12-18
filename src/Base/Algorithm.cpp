#include "Algorithm.h"


Algorithm::Algorithm(Function obj_function) :
  m_obj_function(obj_function),
  m_mt((std::random_device())()),
  m_save_population(false),
  m_silent(false) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setConstraints(List constraints) {
  m_constraints = constraints;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setParameters(List parameters) {
  int n = parameters.length();
  m_parameters = ParametersRange(n);
  m_parameter_range = std::vector<std::vector<double>>(n);

  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    m_parameters.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
    m_parameter_range[i] = {par.slot("min_val"), par.slot("max_val")};
    m_parameter_names.push_back(par.slot("name"));
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setSilent(bool t) {
  m_silent = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::savePopulation(bool t) {
  m_save_population = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
