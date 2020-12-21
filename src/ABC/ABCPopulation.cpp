#include "ABCPopulation.h"

ABCPopulation::ABCPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_bees.resize(pop_size, Bee(d));

  // Each Bee contains only an egg (Bee = solution)
  for (size_t i = 0; i < m_bees.size(); ++i) {
    m_bees[i].setPosition(m_search_space.getRandom());
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::setConfig(const ABCConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::sort() {
  std::sort(m_bees.begin(), m_bees.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t ABCPopulation::size() const {
  return m_bees.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double ABCPopulation::fitness(Bee& bee) {
  double f = bee.getCost();
  if (f >= 0) {
    return 1./(1. + f);
  }
  return 1. + fabs(f);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

////////FIXME
size_t ABCPopulation::getRandomPopulationIndex(size_t i) {
  return i;
};


void ABCPopulation::newEmployedBeesSolutions() {
  // Each employed bee xi generates a new candidate solution
  // vi in the neighborhood of its present position
  size_t d = m_search_space.getNumberOfParameters();
  size_t j, k = 0;
  for (size_t i = 0; i < m_bees.size(); ++i) { // loop on population

    // random index in population with j != i
    j = getRandomPopulationIndex(i);

  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::evaluate() {
  for (size_t i = 0; i < m_bees.size(); ++i) {
    evaluate(m_bees[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::evaluate(Bee& solution) {
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


std::vector<std::vector<double>> ABCPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_bees.size());
  for (size_t i = 0; i < m_bees.size(); ++i) positions[i] = m_bees[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
