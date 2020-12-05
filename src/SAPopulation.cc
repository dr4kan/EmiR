#include "SAPopulation.h"

SAPopulation::SAPopulation(const SAConfig& t_config, const ParametersRange& t_par_range) : m_config(t_config), m_mt(std::random_device()()), m_par_range(t_par_range) {
  size_t pop_size = m_config.getNumberOfParticles();
  size_t psize = m_par_range.getNumberOfParameters();
  m_particles.resize(pop_size, Particle(psize));
  for (size_t i = 0; i < m_particles.size(); ++i) {
    for (size_t j = 0; j < psize; ++j) {
      std::uniform_real_distribution<double> uni1(m_par_range.getParameterMin(j), m_par_range.getParameterMax(j));
      m_particles[i].setPosition(j, uni1(m_mt));
      m_particles[i].setVelocity(j, 0);
    };
  };
};

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

size_t SAPopulation::size() const {
  return m_particles.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAPopulation::sort() {
  std::sort(m_particles.begin(), m_particles.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAPopulation::setVelocity()
{
  std::uniform_real_distribution<double> uni(0, 1);
  for (size_t i = 0; i < m_particles.size(); ++i) {
    for (size_t j = 0; j < m_particles[i].getDimension(); ++j) {
      double cognitive = m_config.getCognitiveParameter() * uni(m_mt) *
      (m_particles[i].getBestPosition(j) - m_particles[i].getPosition(j));
      double social = m_config.getSocialParameter() * uni(m_mt) *
      (m_particles[0].getBestPosition(j) - m_particles[i].getPosition(j));
      double vel = m_particles[i].getVelocity(j) * m_config.getInertia() + cognitive + social;
      m_particles[i].setVelocity(j, vel);
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

Particle SAPopulation::createGuess(size_t i) {
  size_t n_dim = m_par_range.getNumberOfParameters();

  Particle guess(n_dim);
  for (size_t j = 0; j < n_dim; ++j) {
    if (m_particles[i].getPosition(j) + m_particles[i].getVelocity(j) >= m_par_range.getParameterMax(j)) {
      guess.setPosition(j, m_par_range.getParameterMax(j));
    } else if (m_particles[i].getPosition(j) + m_particles[i].getVelocity(j) <= m_par_range.getParameterMin(j)) {
      guess.setPosition(j, m_par_range.getParameterMin(j));
    } else {
      guess.setPosition(j, m_particles[i].getPosition(j) + m_particles[i].getVelocity(j));
    }
  }
  return guess;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAPopulation::moveParticles(std::function<double (double*)> cost_function, int iter)
{
  if (iter > 0) {
    // Change the velocity of the particles
    setVelocity();

    double temperature = m_config.getTemp();
    temperature = temperature / log(1 + iter);
    size_t n_dim = m_par_range.getNumberOfParameters();

    std::uniform_real_distribution<double> uni(0, 1);
    for (size_t i = 0; i < n_dim; ++i) {
      Particle guess = createGuess(i);
      guess.setCost(cost_function(guess.getPosition()));

      double deltaF =  guess.getCost() - m_particles[i].getCost();
      if (exp(- deltaF / temperature) > uni(m_mt)) {
        for (size_t j = 0; j < n_dim; ++j) {
          m_particles[i].setPosition(j, guess.getPosition(j));
        };
        m_particles[i].setCost(guess.getCost());
      };
    };

  } else {

    for (size_t k = 0; k < m_particles.size(); ++k) {
      m_particles[k].setCost(cost_function(m_particles[k].getPosition()));
    };

  };
};
