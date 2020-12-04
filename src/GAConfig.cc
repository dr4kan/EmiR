#include "GAConfig.h"

GAConfig::GAConfig() {
  m_nmax_iter = 1000;
  m_nmax_iter_scost = 100;
  m_population_size = 100;
  m_mutation_rate = 0.10;
  m_keep_fraction = 0.40;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setNMaxIterations(int t) {
  m_nmax_iter = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setNMaxIterationsAtSameCost(int t) {
  m_nmax_iter_scost = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int GAConfig::getNMaxIterations() const {
  return m_nmax_iter;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int GAConfig::getNMaxIterationsSameCost() const {
  return m_nmax_iter_scost;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setPopulationSize(int t) {
  m_population_size = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setMutationRate(double t) {
  m_mutation_rate = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setKeepFraction(double t) {
  m_keep_fraction = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setConfigCrossover() {
  m_keep   = floor(m_keep_fraction * m_population_size);
  double k = m_keep * (m_keep + 1) / 2;
  m_prob.push_back(m_keep / k);
  for (int i = 2; i <= m_keep; i++) {
    m_prob.push_back((m_keep - i + 1) / k + m_prob[i - 2]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int GAConfig::getPopulationSize() const {
  return m_population_size;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double GAConfig::getMutationRate() const {
  return m_mutation_rate;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double GAConfig::getKeepFraction() const {
  return m_keep_fraction;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int GAConfig::getKeep() const {
  return m_keep;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double GAConfig::getProb(int t) const {
  return m_prob[t];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
