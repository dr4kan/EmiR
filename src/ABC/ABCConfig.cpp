#include "ABCConfig.h"

ABCConfig::ABCConfig() : Config() {
  m_frac_employed = 0.5;
  m_n_scout = 1;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCConfig::setEmployedFraction(double t) {
  m_frac_employed = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCConfig::setNScoutBees(size_t t) {
  m_n_scout = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double ABCConfig::getEmployedFraction() {
  return m_frac_employed;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t ABCConfig::getNScoutBees() {
  return m_n_scout;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
