#include "Particle.h"

Particle::Particle(int n) : m_position(n, 0), m_position_best(n, 0), m_velocity(n, 0), m_cost(0.) {
  m_cost_best = std::numeric_limits<double>::max();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void Particle::setPosition(size_t t, double t_x) {
  m_position[t] = t_x;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void Particle::setCost(double t) {
  // If the cost computed with the current position is smaller than the best cost,
  // then both the best position and the best cost are updated
  if (t < m_cost_best) {
    m_position_best = m_position;
    m_cost_best = t;
  }
  m_cost = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void Particle::setVelocity(size_t t, double t_x) {
  m_velocity[t] = t_x;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

size_t Particle::getDimension() const {
  return m_position.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double Particle::getPosition(size_t t) {
  return m_position[t];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double Particle::getBestPosition(size_t t) {
  return m_position_best[t];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double Particle::getVelocity(size_t t) {
  return m_velocity[t];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double Particle::getCost() {
  return m_cost;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double Particle::getBestCost() {
  return m_cost_best;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
