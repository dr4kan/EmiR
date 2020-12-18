#include "Population.h"

Population::Population(Function func) :
  m_mt((std::random_device())()),
  m_obj_func(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setParRange(const ParametersRange& t_par_range) {
  m_par_range = t_par_range;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setConstraints(List constraints) {
  m_constraints = constraints;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
