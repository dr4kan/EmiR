#include "CSConfig.h"

CSConfig::CSConfig() {
  m_nmax_iter = 1000;
  m_nmax_iter_scost = 100;
  m_population_size = 50;
  m_mutation_rate = 0.25;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSConfig::setNMaxIterations(int t) {
  m_nmax_iter = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSConfig::setNMaxIterationsAtSameCost(int t) {
  m_nmax_iter_scost = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int CSConfig::getNMaxIterations() const {
  return m_nmax_iter;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int CSConfig::getNMaxIterationsSameCost() const {
  return m_nmax_iter_scost;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSConfig::setPopulationSize(int t) {
  m_population_size = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSConfig::setMutationRate(double t) {
  m_mutation_rate = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int CSConfig::getPopulationSize() const {
  return m_population_size;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double CSConfig::getMutationRate() const {
  return m_mutation_rate;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
