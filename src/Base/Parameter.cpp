#include "Parameter.h"

Parameter::Parameter() :
m_mt((std::random_device())()),
m_name(""),
m_min_val(0.),
m_max_val(0.) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Parameter::Parameter(const std::string& t_name) :
m_mt((std::random_device())()),
m_name(t_name),
m_min_val(0.),
m_max_val(0.) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Parameter::setName(const std::string& t_name) {
  m_name = t_name;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Parameter::setRange(double t_min,  double t_max) {
  m_min_val = t_min;
  m_max_val = t_max;
  m_range = r_pt{m_min_val, m_max_val};
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


const std::string& Parameter::getName() const {
  return m_name;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Parameter::getMin() const {
  return m_min_val;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Parameter::getMax() const {
  return m_max_val;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Parameter::getWidth() const {
  return 0.5*(m_max_val-m_min_val);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Parameter::getRandom() {
  return m_r_range(m_mt, m_range);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
