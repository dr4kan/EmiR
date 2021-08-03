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


#include "GAPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

GAPopulation::GAPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::init() {
  m_config.setConfigCrossover();

  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();
  m_individuals.resize(pop_size, GAChromosome(d));

  if (m_initial_population.nrow() > 0) {
    NumericVector v;
    for (std::size_t i = 0; i < (std::size_t) m_initial_population.nrow(); ++i) {
      v = m_initial_population.row(i);
      m_individuals[i].setPosition(Rcpp::as<std::vector<double> >(v));
    }
  } else {

    // Generate randomly the position of the whales
    if (!m_silent) Rcout << "Generating the initial population...\n";
    Progress progress_bar(pop_size, !m_silent);
    for (std::size_t i = 0; i < m_individuals.size(); ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
      progress_bar.increment();
    }

  }

  // Dummy assignment of the best solution. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::setConfig(const GAConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > GAPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


GAChromosome* GAPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::sort() {
  std::sort(m_individuals.begin(), m_individuals.end());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::crossover() {
  // generate offspring
  double size = m_individuals.size();
  double ndof = m_search_space.getNumberOfParameters();
  std::size_t keep = m_config.getKeep();

  for (std::size_t i = 0; i < (size - keep); i = i + 2) {
    m_individuals[size - 1 - i].setIndicatorDown();
    m_individuals[size - 2 - i].setIndicatorDown();
    int    ma = 0, pa = 0;

    // mother
    double ra1 = m_random.rand();
    for (std::size_t u = 1; u < keep; u++) {
      if (ra1 > m_config.getProb(u - 1) && ra1 <= m_config.getProb(u)) ma = u;
    }

    // father
    double ra2 = m_random.rand();
    for (std::size_t u = 1; u < keep; u++) {
      if (ra2 > m_config.getProb(u - 1) && ra2 <= m_config.getProb(u)) pa = u;
    }
    for (std::size_t k = 0; k < ndof; k++) {
      double beta = m_random.rand();
      m_individuals[size - 1 - i][k] = m_individuals[ma][k] -
      beta * (m_individuals[ma][k] - m_individuals[pa][k]);
      m_individuals[size - 2 - i][k] = m_individuals[pa][k] +
      beta * (m_individuals[ma][k] - m_individuals[pa][k]);
    }
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::mutation() {
  double ndof = m_search_space.getNumberOfParameters();
  double size = m_individuals.size();
  int mutat = floor(m_config.getMutationRate() * m_config.getPopulationSize() * ndof);

  for (int i = 0; i < mutat; i++) {
    int ra1 = m_random.randUInt(0, ndof); // [0, ndof)
    int ra2 = m_random.randUInt(1, size); // [1, size)  elitism
    m_individuals[ra2][ra1] = m_search_space.getRandom(ra1);
    m_individuals[ra2].setIndicatorDown();
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::evaluate(GAChromosome& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);
  solution.setIndicatorDown();

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
