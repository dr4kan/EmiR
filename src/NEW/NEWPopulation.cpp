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
    tmp = m_charges[i];

    // new position
    for (size_t j = 0; j < d; ++j) { // loop on dimension
      m_charges[i][j] += m_charges[i].getVelocity(j);

      checkBoundary(m_charges[i][j], j);
    }

    // evaluate new solution
    evaluate(m_charges[i]);

    // neutral particles do not accelerate
    if (m_charges[i].getCharge() == 0) {
      if (m_charges[i].getCost() < m_best_solution.getCost()) m_best_solution = m_charges[i];
      continue;
    }

    // update the velocity
    deltaE = m_charges[i].getCost() - tmp.getCost();
    for (size_t j = 0; j < d; ++j) { // loop on dimension
      v = m_charges[i].getVelocity(j) + m_charges[i].getCharge() * Utility::sgn(deltaE) * sqrt(fabs(deltaE));
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
  NumericVector tmp_v = m_obj_func(solution.getPosition());
  double value = tmp_v[0];
  bool violated_constr = false;

  for (int i = 0; i < m_constraints.length(); ++i) {
    S4 constraint = m_constraints[i];
    Function g = constraint.slot("func");
    std::string inequality = constraint.slot("inequality");
    tmp_v = g(solution.getPosition());
    double tmp_d = tmp_v[0];

    if (inequality == "<" && tmp_d >= 0) {
      violated_constr = true;
    } else if (inequality == "<=" && tmp_d > 0) {
      violated_constr = true;
    } else if (inequality == ">=" && tmp_d < 0) {
      violated_constr = true;
    } else if (inequality == ">" && tmp_d <= 0) {
      violated_constr = true;
    }
  }

  if (violated_constr) value = std::numeric_limits<double>::max();

  solution.setCost(value);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> NEWPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_charges.size());
  for (size_t i = 0; i < m_charges.size(); ++i) positions[i] = m_charges[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
