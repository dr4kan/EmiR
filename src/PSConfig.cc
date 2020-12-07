#include "PSConfig.h"

PSConfig::PSConfig() {
  m_nmax_iter = 1000;
  m_nmax_iter_scost = 100;
  m_nparticles = 100;
  m_cognitive = 2.0;
  m_social = 2.0;
  m_vmax = 0.1;
  m_inertia = 0.4;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setNMaxIterations(int t) {
  m_nmax_iter = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setNMaxIterationsAtSameCost(int t) {
  m_nmax_iter_scost = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int PSConfig::getNMaxIterations() const {
  return m_nmax_iter;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int PSConfig::getNMaxIterationsSameCost() const {
  return m_nmax_iter_scost;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setNumberOfParticles(int t) {
  m_nparticles = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setCognitiveParameter(double t) {
  m_cognitive = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setSocialParameter(double t) {
  m_social = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setInertia(double t) {
  m_inertia = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setVMaxParameter(double t) {
  m_vmax = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSConfig::setPenaltyParameter(double t) {
  m_penalty_parameter = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int PSConfig::getNumberOfParticles() const {
  return m_nparticles;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double PSConfig::getCognitiveParameter() const {
  return m_cognitive;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double PSConfig::getSocialParameter() const {
  return m_social;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double PSConfig::getInertia() const {
  return m_inertia;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double PSConfig::getVMaxParameter() const {
  return m_vmax;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double PSConfig::getPenaltyParameter() const {
  return m_penalty_parameter;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
