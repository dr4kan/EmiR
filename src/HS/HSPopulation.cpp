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


#include "HSPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

HSPopulation::HSPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::init() {
  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();
  m_individuals.resize(pop_size, Individual(d));

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
      progress_bar.increment();
    }

  }

  // Dummy assignment of the best individual. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::setConfig(const HSConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > HSPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Individual* HSPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::sort() {
  std::sort(m_individuals.begin(), m_individuals.end());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::generateNewHarmony() {
  std::size_t d = m_search_space.getNumberOfParameters();
  double val = 0.;
  Individual new_solution(d);

  for (std::size_t j = 0; j < d; ++j) { // loop on dimension
    if (m_random.rand() < m_config.getHmcr()) {
      // choose from history
      val = m_individuals[m_random.randUInt(0, m_individuals.size())][j]; // [0, m_individuals.size)

      // check for pitch adjustment for recalled
      if (m_random.rand() < m_config.getPar()) {
        val += m_random.rand(-1., 1.)*m_config.getBw();
      }

      new_solution[j] = val;
    } else {
      // generate a new one
      new_solution[j] = m_search_space.getRandom(j);
    }
  }

  // boundary check
  checkBoundary(new_solution);

  // check if the new solution if better than the worst in the population
  evaluate(new_solution);
  if (new_solution.getCost() < m_individuals[m_individuals.size()-1].getCost()) {
    m_individuals[m_individuals.size()-1] = new_solution;
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void HSPopulation::evaluate(Individual& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
