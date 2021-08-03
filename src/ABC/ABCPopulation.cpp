/*
###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021 Davide Pagano & Lorenzo Sostero                          #
#                                                                             #
# This program is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but         #
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  #
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    #
# for more details: <https://www.gnu.org/licenses/>.                          #
###############################################################################
*/


#include "ABCPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

ABCPopulation::ABCPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::init() {
  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();

  // Number of food sources: pop_size/2
  std::size_t f = (std::size_t) (m_config.getEmployedFraction() * pop_size);
  m_scouters = m_config.getNScoutBees();
  m_onlookers = pop_size - f - m_scouters;
  m_individuals.resize(f, Bee(d));
  m_prob.resize(f, 0);
  m_trial.resize(f, 0);

  if (m_initial_population.nrow() > 0) {

    // Load the positions provided by the user
    NumericVector v;
    for (std::size_t i = 0; i < (std::size_t) m_initial_population.nrow(); ++i) {
      v = m_initial_population.row(i);
      m_individuals[i].setPosition(Rcpp::as<std::vector<double> >(v));
    }

  } else {

    // Generate randomly the position of the individuals
    if (!m_silent) Rcout << "Generating the initial population...\n";
    Progress progress_bar(pop_size, !m_silent);
    for (std::size_t i = 0; i < m_individuals.size(); ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
    }

  }

  // Dummy assignment of the best bee. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];

  m_limit_scout = (std::size_t) (0.5 * pop_size * d);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::setConfig(const ABCConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > ABCPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Bee* ABCPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::size_t ABCPopulation::getRandomPopulationIndex(std::size_t i) {
  std::size_t j = i;
  do {
    j = m_random.randUInt(0, m_individuals.size()); // [0, m_individuals.size)
  } while(j == i);
  return j;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::generateSolution(Bee &tmp, std::size_t i) {
  // Random index in population with k != i
  std::size_t k = getRandomPopulationIndex(i);

  // Random index in the dimension
  std::size_t j = m_random.randUInt(0, m_search_space.getNumberOfParameters()); // [0, m_search_space.getNumberOfParameters)

  tmp[j] += m_random.rand(-1., 1.) * (tmp[j] - m_individuals[k][j]);

  // Boundary check
  checkBoundary(tmp);

  // Evaluate the new solution
  evaluate(tmp);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::employedBeesEvaluation() {
  // Each employed bee xi generates a new candidate solution
  // in the neighborhood of its present position
  Bee tmp;
  m_fitness_sum = 0.;
  for (std::size_t i = 0; i < m_individuals.size(); ++i) { // loop on population
    tmp = m_individuals[i];

    // Generate a new solution
    generateSolution(tmp, i);

    // Greedy selection: if the fitness value of tmp is better than m_individuals[i]
    // then update m_individuals[i] with tmp, otherwise keep m_individuals[i] unchanged
    if (tmp.getFitness() > m_individuals[i].getFitness()) {
      m_individuals[i] = tmp;
      m_trial[i] = 0;
    } else {
      m_trial[i]++;
    }

    m_fitness_sum += m_individuals[i].getFitness();
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::computeProbabilities() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) { // loop on population
    m_prob[i] = m_individuals[i].getFitness() / m_fitness_sum;
  }
}
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
  std::size_t sel = 0;
  for (std::size_t k = 0; k < m_onlookers; ++k) {
    sel = m_random.rand();
    tmp = m_individuals[sel];

    // generate a new solution
    generateSolution(tmp, k);

    // greedy selection: if the fitness value of tmp is better than m_individuals[i]
    // then update m_individuals[i] with tmp, otherwise keep m_individuals[i] unchanged
    if (tmp.getFitness() > m_individuals[sel].getFitness()) {
      m_individuals[sel] = tmp;
      m_trial[sel] = 0;
    } else {
      m_trial[sel]++;
    }

    // If a position cannot be improved over a predefined number (called limit)
    // of cycles, then the food source is abandoned
    if (m_trial[sel] > (int)m_limit_scout) {
      m_individuals[sel].setPosition(m_search_space.getRandom());
      evaluate(m_individuals[sel]);
      m_trial[sel] = 0;
      discarded_solutions = true;
    }
  }

  // if no solution was discarded, generate new random solutions
  if (discarded_solutions) return;

  std::size_t s = 0;
  for (std::size_t k = 0; k < m_scouters; ++k) {
    s = m_random.randUInt(0, m_individuals.size()); // [0, m_individuals.size)
    m_individuals[s].setPosition(m_search_space.getRandom());
    evaluate(m_individuals[s]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void ABCPopulation::evaluate(Bee& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
