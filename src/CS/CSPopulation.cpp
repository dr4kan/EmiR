#include "CSPopulation.h"

CSPopulation::CSPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_nests.resize(pop_size, Nest(d));

  // Each nest contains only an egg (nest = solution)
  for (size_t i = 0; i < m_nests.size(); ++i) {
    m_nests[i].setPosition(m_search_space.getRandom());
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


void CSPopulation::generateCuckooEgg() {

  // new solution by Lévy flights around the current best solutions
  double beta = 1.5;
  double sigma = 0.6966;
  std::normal_distribution<double> norm_v{0, 1};
  std::normal_distribution<double> norm_u{0, sigma};

  double step = 0.;
  size_t d = m_search_space.getNumberOfParameters();
  Nest tmp(d);
  for (size_t j = 0; j < d; ++j) {
    step = m_config.getAlpha() * norm_u(m_mt) / (pow(fabs(norm_v(m_mt)), 1 / beta));
    tmp[j] = m_nests[0][j] + step;

    // if the position is not in the range
    if (tmp[j] < m_search_space[j].getMin()) tmp[j] = m_search_space[j].getMin();
    if (tmp[j] > m_search_space[j].getMax()) tmp[j] = m_search_space[j].getMax();

    // if the position is not in the range
    // if (tmp[j] < m_search_space[j].getMin() || tmp[j] > m_search_space[j].getMax()) {
    //   tmp[j] = m_search_space[j].getRandom();
    // }
  }

  // evaluate the new solution
  evaluate(tmp);

  // choose a random nest (excluding the best)
  std::uniform_int_distribution<int> r_int(1, m_nests.size() - 1);
  int k = r_int(m_mt);

  // if the new solution is better replace the selected nestå
  if (tmp.getCost() < m_nests[k].getCost()) m_nests[k] = tmp;

  // a pa fraction of the sub-optimal solution are replaced by new ones
  size_t to_replace = std::round(m_config.getPa()*m_nests.size());
  for (size_t i = 1; i <= to_replace; ++i) {
    m_nests[m_nests.size()-i].setPosition(m_search_space.getRandom());

    // evaluate the new solutions
    evaluate(m_nests[m_nests.size()-i]);
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
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> CSPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_nests.size());
  for (size_t i = 0; i < m_nests.size(); ++i) positions[i] = m_nests[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
