#include "HSPopulation.h"

HSPopulation::HSPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_harmonies.resize(pop_size, Individual(d));

  for (size_t i = 0; i < m_harmonies.size(); ++i) {
    m_harmonies[i].setPosition(m_search_space.getRandom());
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::setConfig(const HSConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::sort() {
  std::sort(m_harmonies.begin(), m_harmonies.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t HSPopulation::size() const {
  return m_harmonies.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::generateNewHarmony() {
  size_t d = m_search_space.getNumberOfParameters();
  std::uniform_int_distribution<> u_pop(0, m_harmonies.size()-1);
  double val = 0.;
  Individual new_solution(d);

  for (size_t j = 0; j < d; ++j) { // loop on dimension
    if (getRand_0_1() < m_config.getHmcr()) {
      // choose from history
      val = m_harmonies[u_pop(m_mt)][j];

      // check for pitch adjustment for recalled
      if (getRand_0_1() < m_config.getPar()) {
        val += getRand_1_1()*m_config.getBw();
      }

      // if the position is not in the range a new solution is generated
      if (val < m_search_space[j].getMin() || val > m_search_space[j].getMax()) {
        val = m_search_space[j].getRandom();
      }

      new_solution[j] = val;
    } else {
      // generate a new one
      new_solution[j] = m_search_space[j].getRandom();
    }
  }

  // check if the new solution if better than the worst in the population
  evaluate(new_solution);
  if (new_solution.getCost() < m_harmonies[m_harmonies.size()-1].getCost()) {
    m_harmonies[m_harmonies.size()-1] = new_solution;
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::evaluate() {
  for (size_t i = 0; i < m_harmonies.size(); ++i) {
    evaluate(m_harmonies[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::evaluate(Individual& solution) {
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


std::vector<std::vector<double>> HSPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_harmonies.size());
  for (size_t i = 0; i < m_harmonies.size(); ++i) positions[i] = m_harmonies[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
