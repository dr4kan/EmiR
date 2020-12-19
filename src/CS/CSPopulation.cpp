#include "CSPopulation.h"

CSPopulation::CSPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_nests.resize(pop_size, Nest(d));

  for (size_t j = 0; j < d; ++j) { // loop on dimension
    std::uniform_real_distribution<double> u_pos(m_search_space[j].getMin(), m_search_space[j].getMax());

    for (size_t i = 0; i < m_nests.size(); ++i) { // loop on population
      m_nests[i][j] = u_pos(m_mt);
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::setConfig(const CSConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::sort() {
  std::sort(m_nests.begin(), m_nests.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t CSPopulation::size() const {
  return m_nests.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Nest& CSPopulation::chooseRndNest() {
  std::uniform_int_distribution<int> uni(1, m_nests.size()-1);
  return m_nests[uni(m_mt)];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::updateWithLevyFlight(size_t t) {
  size_t d = m_search_space.getNumberOfParameters();
  std::uniform_real_distribution<double> u_1_3(1., 3.);
  double lambda = 0.;

  for (size_t i = 0; i < m_nests.size(); ++i) {
    for (size_t j = 0; j < d; ++j) {

      // generate the levy exponent uniformly in [1, 3]
      lambda = u_1_3(m_mt);

      m_nests[i][j] = m_nests[i][j] + m_config.getAlpha() * pow(t, -lambda);

      // if the position is not in the range a new solution is generated
      if (m_nests[i][j] < m_search_space[j].getMin() ||
          m_nests[i][j] > m_search_space[j].getMax()) {

      }

    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::evaluate() {
  for (size_t i = 0; i < m_nests.size(); ++i) {
    evaluate(m_nests[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::evaluate(Nest& solution) {
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


std::vector<std::vector<double>> CSPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_nests.size());
  for (size_t i = 0; i < m_nests.size(); ++i) positions[i] = m_nests[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
