#include "NEWPopulation.h"
#include "../Base/Utility.h"

NEWPopulation::NEWPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void NEWPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_charges.resize(pop_size, Particle(d));

  std::vector<int> charges = {-1, 0, 1};
  std::discrete_distribution<> p({0.4, 0.2, 0.4});

  std::normal_distribution<> rnorm{0, 0.2};
  size_t sel = 0.;
  for (size_t i = 0; i < m_charges.size(); ++i) {
    sel = p(m_mt);
    m_charges[i].setCharge(charges[sel]);

    for (size_t j = 0; j < d; ++j) {
      m_charges[i][j] = m_search_space[j].getRandom();
      m_charges[i].setVelocity(j, rnorm(m_mt));
    }
  }

  m_best_solution = m_charges[0];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void NEWPopulation::setConfig(const NEWConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void NEWPopulation::sort() {
  std::sort(m_charges.begin(), m_charges.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t NEWPopulation::size() const {
  return m_charges.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void NEWPopulation::moveParicles() {
  size_t d = m_search_space.getNumberOfParameters();
  double deltaE, v = 0.;
  Particle tmp;
  for (size_t i = 0; i < m_charges.size(); ++i) { // loop on population

    // new position
    for (size_t j = 0; j < d; ++j) { // loop on dimension
      // set the tmp solution equale to initial state so that
      // only one component at the time is changed
      tmp = m_charges[i];

      // only changing the j-th component
      tmp[j] += m_charges[i].getVelocity(j);

      checkBoundary(tmp[j], tmp.getVelocity(j), j);

      // evaluate new solution
      evaluate(tmp);

      // update the velocity of the j-th component
      deltaE = 0.01 * (m_charges[i].getCost() - tmp.getCost());
      v = tmp.getVelocity(j) + m_charges[i].getCharge() * Utility::sgn(deltaE) * sqrt(fabs(deltaE));
      m_charges[i][j] = tmp[j];
      m_charges[i].setVelocity(j, v);
    }

    if (m_charges[i].getCost() < m_best_solution.getCost()) m_best_solution = m_charges[i];
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void NEWPopulation::evaluate() {
  for (size_t i = 0; i < m_charges.size(); ++i) {
    evaluate(m_charges[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void NEWPopulation::evaluate(Individual& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> NEWPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_charges.size());
  for (size_t i = 0; i < m_charges.size(); ++i) positions[i] = m_charges[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
