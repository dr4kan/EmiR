#include "HSPopulation.h"

HSPopulation::HSPopulation(Function func) :
  m_mt((std::random_device())()),
  m_obj_func(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_par_range.getNumberOfParameters();
  m_harmonies.resize(pop_size, Harmony(d));

  for (size_t j = 0; j < d; ++j) { // loop on dimension
    std::uniform_real_distribution<double> u_pos(m_par_range.getParameterMin(j), m_par_range.getParameterMax(j));

    for (size_t i = 0; i < m_harmonies.size(); ++i) { // loop on population
      m_harmonies[i].setPosition(j, u_pos(m_mt));
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::setConfig(const HSConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::setParRange(const ParametersRange& t_par_range) {
  m_par_range = t_par_range;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::setConstraints(List constraints) {
  m_constraints = constraints;
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
  size_t d = m_par_range.getNumberOfParameters();
  std::uniform_real_distribution<double> u_0_1(0., 1.);
  std::uniform_real_distribution<double> u_1_1(-1., 1.);
  std::uniform_int_distribution<> u_pop(0, m_harmonies.size()-1);
  double val = 0.;
  Harmony new_solution(d);

  for (size_t j = 0; j < d; ++j) { // loop on dimension
    std::uniform_real_distribution<double> u_pos(m_par_range.getParameterMin(j), m_par_range.getParameterMax(j));

    if (u_0_1(m_mt) < m_config.getHmcr()) {
      // choose from history
      val = m_harmonies[u_pop(m_mt)].getPosition(j);

      // check for pitch adjustment for recalled
      if (u_0_1(m_mt) < m_config.getPar()) {
        val += u_1_1(m_mt)*m_config.getBw();
      }

      new_solution.setPosition(j, val);
    } else {
      // generate a new one
      new_solution.setPosition(j, u_pos(m_mt));
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


void HSPopulation::evaluate(Harmony& solution) {
  // check if the solution is out of range
  for (size_t j = 0; j < m_par_range.getNumberOfParameters(); ++j) {
    if (solution.getPosition(j) < m_par_range.getParameterMin(j) ||
        solution.getPosition(j) > m_par_range.getParameterMax(j)) {
      solution.setCost(std::numeric_limits<double>::max());
      return;
    }
  }

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
