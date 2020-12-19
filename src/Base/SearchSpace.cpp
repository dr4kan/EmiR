#include "SearchSpace.h"

SearchSpace::SearchSpace() : m_par(0) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


SearchSpace::SearchSpace(int n) : m_par(n) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SearchSpace::setParameter(size_t t, const std::string& t_name, double t_min, double t_max) {
  if (t_name == "") {
    m_par[t].setName("p" + std::to_string(t));
  } else {
    m_par[t].setName(t_name);
  }
  m_par[t].setRange(t_min, t_max);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t SearchSpace::getNumberOfParameters() const {
  return m_par.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<double> SearchSpace::getRandom() {
  size_t d = m_par.size();
  std::vector<double> point(d);
  for (size_t i = 0; i < d; ++i) point[i] = m_par[i].getRandom();
  return point;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
