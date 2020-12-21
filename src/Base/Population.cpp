#include "Population.h"

Population::Population(Function func) :
  m_mt((std::random_device())()),
  m_obj_func(func) {
    m_pt_0_1 = rand_pt{ 0., 1.};
    m_pt_1_1 = rand_pt{-1., 1.};
  };
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setSearchSpace(const SearchSpace& t_par_range) {
  m_search_space = t_par_range;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setConstraints(List constraints) {
  m_constraints = constraints;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Population::getRand_0_1() {
  return m_rand_0_1(m_mt, m_pt_0_1);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Population::getRand_1_1() {
  return m_rand_1_1(m_mt, m_pt_1_1);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


int Population::genIntRand(int tmin, int tmax) {
  rint_pt int_pt {tmin, tmax};
  return m_int_rand(m_mt, int_pt);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
