#include "SAPopulation.h"

SAPopulation::SAPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  size_t t = m_config.getNMaxIterations();
  m_particles.resize(pop_size, SAParticle(d));
  m_step_sizes.resize(d);

  m_temperature = m_config.getT0();
  m_beta = (double) (m_temperature/t);

  double L = 0.;
  for (size_t j = 0; j < d; ++j) { // loop on dimension

    // Compute the step size for the random walk
    L = m_search_space[j].getWidth();
    m_step_sizes[j] = 10*(L/10.)/sqrt(t*d);

    for (size_t i = 0; i < m_particles.size(); ++i) { // loop on population
      m_particles[i][j] = m_search_space[j].getRandom();
    }
  }

  // [HAL]sort?

  m_best_solution = m_particles[0];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::setConfig(const SAConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::sort() {
  std::sort(m_particles.begin(), m_particles.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t SAPopulation::size() const {
  return m_particles.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::evaluate() {
  for (size_t i = 0; i < m_particles.size(); ++i) {
    evaluate(m_particles[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::evaluate(Individual& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> SAPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_particles.size());
  for (size_t i = 0; i < m_particles.size(); ++i) positions[i] = m_particles[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::updateTemperature(size_t t) {
  if (m_config.getAnnealingSchedule() == SAConfig::LINEAR) {
    m_temperature = m_config.getT0() - m_beta*t;
  } else { // GEOMETRIC
    m_temperature = m_config.getT0()*pow(m_config.getAlpha(), t);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::randomWalk() {
  double shift = 0.;
  double deltaF = 0.;
  size_t d = m_search_space.getNumberOfParameters();
  SAParticle tmp;
  for (size_t i = 0; i < m_particles.size(); ++i) { // loop on population
    tmp = m_particles[i];

    for (size_t j = 0; j < d; ++j) { // loop on dimension
      shift = getRand_1_1();
      tmp[j] += m_step_sizes[j]*shift;

      checkBoundary(tmp[j], shift, j);
    }

    evaluate(tmp);

    // If the new solution is better, it is accepted
    if (tmp.getCost() < m_particles[i].getCost()) {
      m_particles[i] = tmp;
    } else {
      // If not it could be accepted by chance
      deltaF = tmp.getCost() - m_particles[i].getCost();
      if (exp(-deltaF/m_temperature) > getRand_0_1()) {
        m_particles[i] = tmp;
      }
    }

    // Updating the best solution
    if (m_particles[i].getCost() < m_best_solution.getCost()) m_best_solution = m_particles[i];
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
