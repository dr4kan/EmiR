#include "SAConfig.h"

SAConfig::SAConfig() {
  m_nmax_iter = 1000;
  m_nmax_iter_scost = 100;
  m_nparticles = 100;
  m_cognitive = 2.0;
  m_social = 2.0;
  m_temp = 50;
  m_inertia = 0.1;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAConfig::setNMaxIterations(int t) {
  m_nmax_iter = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAConfig::setNMaxIterationsAtSameCost(int t) {
  m_nmax_iter_scost = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int SAConfig::getNMaxIterations() const {
  return m_nmax_iter;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int SAConfig::getNMaxIterationsSameCost() const {
  return m_nmax_iter_scost;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAConfig::setNumberOfParticles(int t) {
  m_nparticles = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAConfig::setCognitiveParameter(double t) {
  m_cognitive = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAConfig::setSocialParameter(double t) {
  m_social = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAConfig::setInertia(double t) {
  m_inertia = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAConfig::setTemp(double t) {
  m_temp = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAConfig::setPenaltyParameter(double t) {
  m_penalty_parameter = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int SAConfig::getNumberOfParticles() const {
  return m_nparticles;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double SAConfig::getCognitiveParameter() const {
  return m_cognitive;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double SAConfig::getSocialParameter() const {
  return m_social;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double SAConfig::getInertia() const {
  return m_inertia;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double SAConfig::getTemp() const {
  return m_temp;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double SAConfig::getPenaltyParameter() const {
  return m_penalty_parameter;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
