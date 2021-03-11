#include "ABCPopulation.h"


ABCPopulation::ABCPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::init() {
  size_t colony_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();

  // Number of food sources: colony_size/2
  size_t f = (size_t) (m_config.getEmployedFraction() * colony_size);
  m_scouters = m_config.getNScoutBees();
  m_onlookers = colony_size - f - m_scouters;
  m_food.resize(f, Bee(d));
  m_prob.resize(f, 0);
  m_trial.resize(f, 0);

  // Initialize the food sources randomly
  for (size_t i = 0; i < f; ++i) {
    m_food[i].setPosition(m_search_space.getRandom());
  }

  // Initialize best solution
  m_best_solution = m_food[0];

  m_limit_scout = (size_t) (0.5 * colony_size * d);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::setConfig(const ABCConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::sort() {
  std::sort(m_food.begin(), m_food.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t ABCPopulation::size() const {
  return m_food.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t ABCPopulation::getRandomPopulationIndex(size_t i) {
  size_t j = i;
  do {
    j = genIntRand(0, m_food.size()-1);
  } while(j == i);
  return j;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::generateSolution(Bee &tmp, size_t i) {
  // random index in population with k != i
  size_t k = getRandomPopulationIndex(i);

  // random inxdex in the dimension
  size_t j = genIntRand(0, m_search_space.getNumberOfParameters()-1);

  tmp[j] = m_food[i][j] + getRand_1_1() * (m_food[i][j] - m_food[k][j]);

  // evaluate the new solution
  evaluate(tmp);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::employedBeesEvalutaion() {
  // Each employed bee xi generates a new candidate solution
  // vi in the neighborhood of its present position
  Bee tmp;
  m_fitness_sum = 0.;
  for (size_t i = 0; i < m_food.size(); ++i) { // loop on population
    tmp = m_food[i];

    // generate a new solution
    generateSolution(tmp, i);

    // greedy selection: if the fitness value of tmp is better than m_food[i]
    // then update m_food[i] with tmp, otherwise keep m_food[i] unchanged
    if (tmp.getFitness() > m_food[i].getFitness()) {
      m_food[i] = tmp;
      m_trial[i] = 0;
    } else {
      m_trial[i]++;
    }

    m_fitness_sum += m_food[i].getFitness();
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::computeProbabilities() {
  for (size_t i = 0; i < m_food.size(); ++i) { // loop on population
    m_prob[i] = m_food[i].getFitness() / m_fitness_sum;
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::onlookerBeesEvaluation() {
  // After all employed bees complete the search process, they share the information of their
  // food sources with the onlooker bees. An onlooker bee evaluates the nectar information
  // taken from all employed bees and chooses a food source with a probability related to its
  // nectar amount. This probabilistic selection is a roulette wheel selection.
  computeProbabilities();

  bool discarded_solutions = false;
  std::discrete_distribution<> p(m_prob.begin(), m_prob.end());
  Bee tmp;
  size_t sel = 0;
  for (size_t k = 0; k < m_onlookers; ++k) {
    sel = p(m_mt);
    tmp = m_food[sel];

    // generate a new solution
    generateSolution(tmp, k);

    // greedy selection: if the fitness value of tmp is better than m_food[i]
    // then update m_food[i] with tmp, otherwise keep m_food[i] unchanged
    if (tmp.getFitness() > m_food[sel].getFitness()) {
      m_food[sel] = tmp;
      m_trial[sel] = 0;
    } else {
      m_trial[sel]++;
    }

    // If a position cannot be improved over a predefined number (called limit)
    // of cycles, then the food source is abandoned
    if (m_trial[sel] > (int)m_limit_scout) {
      m_food[sel].setPosition(m_search_space.getRandom());
      evaluate(m_food[sel]);
      m_trial[sel] = 0;
      discarded_solutions = true;
    }
  }

  // if no solution was discarded, generate new random solutions
  if (discarded_solutions) return;

  size_t s = 0;
  for (size_t k = 0; k < m_scouters; ++k) {
    s = genIntRand(0, m_food.size()-1);
    m_food[s].setPosition(m_search_space.getRandom());
    evaluate(m_food[s]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::evaluate() {
  for (size_t i = 0; i < m_food.size(); ++i) {
    evaluate(m_food[i]);
    if (m_food[i].getCost() < m_best_solution.getCost()) m_best_solution = m_food[i];
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::evaluate(Bee& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > ABCPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_food.size());
  for (size_t i = 0; i < m_food.size(); ++i) positions[i] = m_food[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
