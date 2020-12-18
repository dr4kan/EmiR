#include "ParametersRange.h"

ParametersRange::ParametersRange() : m_par(0) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

ParametersRange::ParametersRange(int n) : m_par(n) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void ParametersRange::setParameterRange(size_t t, const std::string& t_name, double t_min, double t_max) {
  if (t_name == "") {
    m_par[t].setName("p" + std::to_string(t));
  } else {
    m_par[t].setName(t_name);
  }
  m_par[t].setRange(t_min, t_max);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double ParametersRange::getParameterMin(size_t t) const {
  return m_par[t].getRangeMin();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double ParametersRange::getParameterMax(size_t t) const {
  return m_par[t].getRangeMax();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double ParametersRange::getRangeLenght(size_t t) const {
  return m_par[t].getRangeMax()-m_par[t].getRangeMin();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

size_t ParametersRange::getNumberOfParameters() const {
  return m_par.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

const std::string& ParametersRange::getParameterName(size_t t) const {
  return m_par[t].getName();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
