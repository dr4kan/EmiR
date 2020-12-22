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


void Population::setOOB(OOBMethod t) {
  m_oob_sol = t;
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


void Population::checkBoundary(double& t, size_t j) {
  if (m_oob_sol == PBC) {

    // Periodic Boundary Condition (PBC)
    if (t < m_search_space[j].getMin()) t = m_search_space[j].getMax() - fabs(t - m_search_space[j].getMin());
    if (t > m_search_space[j].getMax()) t = m_search_space[j].getMin() + fabs(m_search_space[j].getMax() - t);

  } else if (m_oob_sol == BAB) {

    // Place out-of-bound solutions back at the boundaries (BAB)
    if (t < m_search_space[j].getMin()) t = m_search_space[j].getMin();
    if (t > m_search_space[j].getMax()) t = m_search_space[j].getMax();

  } else if (m_oob_sol == DIS) {

    // Disregard the out-of-bound solution and generate new ones (DIS)
    if (t < m_search_space[j].getMin() || t > m_search_space[j].getMax()) t = m_search_space[j].getRandom();

  } else if (m_oob_sol == RBC) {

    // Reflective Boundary Condition (RBC)
    if (t < m_search_space[j].getMin()) t = m_search_space[j].getMin() + (m_search_space[j].getMin() - t);
    if (t > m_search_space[j].getMax()) t = m_search_space[j].getMax() - (t - m_search_space[j].getMax());

  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
