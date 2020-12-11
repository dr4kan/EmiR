#include "PSPopulation.h"

PSPopulation::PSPopulation(const PSConfig& t_config, const ParametersRange& t_par_range) : m_config(t_config), m_mt(std::random_device()()), m_par_range(t_par_range) {
  size_t pop_size = m_config.getNumberOfParticles();
  size_t psize = m_par_range.getNumberOfParameters();
  m_particles.resize(pop_size, Particle(psize));
  for (size_t i = 0; i < m_particles.size(); ++i) {
    for (size_t j = 0; j < psize; ++j) {
      std::uniform_real_distribution<double> uni1(m_par_range.getParameterMin(j), m_par_range.getParameterMax(j));
      std::uniform_real_distribution<double> uni2(-m_config.getVMaxParameter(), m_config.getVMaxParameter());
      m_particles[i].setPosition(j, uni1(m_mt));
      m_particles[i].setVelocity(j, uni2(m_mt));
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

size_t PSPopulation::size() const {
  return m_particles.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSPopulation::sort() {
  std::sort(m_particles.begin(), m_particles.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSPopulation::setVelocity() {
  std::uniform_real_distribution<double> uni(0, 1);
  for (size_t i = 0; i < m_particles.size(); ++i) {
    for (size_t j = 0; j < m_particles[i].getDimension(); ++j) {
      double cognitive = m_config.getCognitiveParameter() * uni(m_mt) *
      (m_particles[i].getBestPosition(j) - m_particles[i].getPosition(j));
      double social = m_config.getSocialParameter() * uni(m_mt) *
      (m_particles[0].getBestPosition(j) - m_particles[i].getPosition(j));
      double vel = (m_particles[i].getVelocity(j) * m_config.getInertia() + cognitive + social);
      if (abs(vel) < m_config.getVMaxParameter()) {
        m_particles[i].setVelocity(j, vel);
      } else {
        if (vel > m_config.getVMaxParameter()) {
          m_particles[i].setVelocity(j, m_config.getVMaxParameter());
        } else {
          m_particles[i].setVelocity(j, -m_config.getVMaxParameter());
        }
      };
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSPopulation::moveParticles() {
  // Change the velocity of the particles
  setVelocity();

  for (size_t i = 0; i < m_particles.size(); ++i) {
    for (size_t j = 0; j < m_particles[i].getDimension(); ++j) {
      if (m_particles[i].getPosition(j) + m_particles[i].getVelocity(j) >= m_par_range.getParameterMax(j)) {
        m_particles[i].setPosition(j, m_par_range.getParameterMax(j));
      } else if (m_particles[i].getPosition(j) + m_particles[i].getVelocity(j) <= m_par_range.getParameterMin(j)) {
        m_particles[i].setPosition(j, m_par_range.getParameterMin(j));
      } else
      m_particles[i].setPosition(j, m_particles[i].getPosition(j) + m_particles[i].getVelocity(j));
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSPopulation::ComputeCost(std::function<double (double*)> cost_function) {
  for (size_t i = 0; i < m_particles.size(); ++i) {
    m_particles[i].setCost(cost_function(m_particles[i].getPosition()));
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

std::vector<std::vector<double>> PSPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_particles.size());
  for (size_t i = 0; i < m_particles.size(); ++i) positions[i] = m_particles[i].getPositionVector();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
