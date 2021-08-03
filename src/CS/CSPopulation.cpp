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


#include "CSPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

CSPopulation::CSPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::init() {
  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();
  m_individuals.resize(pop_size, Nest(d));

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


void CSPopulation::setConfig(const CSConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > CSPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Nest* CSPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::sort() {
  std::sort(m_individuals.begin(), m_individuals.end());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::generateCuckooEgg() {

  // new solution by Lévy flights around the current best solutions
  double beta = 1.5;
  double sigma = 0.6966;
  double step = 0.;
  std::size_t d = m_search_space.getNumberOfParameters();
  Nest tmp(d);
  for (std::size_t j = 0; j < d; ++j) {
    step = m_config.getAlpha() * m_random.norm(0., sigma) / (pow(fabs(m_random.norm()), 1 / beta));
    tmp[j] = m_individuals[0][j] + step;
  }

  // boundary check
  checkBoundary(tmp);

  // evaluate the new solution
  evaluate(tmp);

  // choose a random nest (excluding the best)
  int k = m_random.randUInt(1, m_individuals.size()); // [1, m_individuals.size)

  // if the new solution is better replace the selected nest
  if (tmp.getCost() < m_individuals[k].getCost()) m_individuals[k] = tmp;

  // a pa fraction of the sub-optimal solution are replaced by new ones
  std::size_t to_replace = std::round(m_config.getPa()*m_individuals.size());
  for (std::size_t i = 1; i <= to_replace; ++i) {
    m_individuals[m_individuals.size()-i].setPosition(m_search_space.getRandom());

    // evaluate the new solutions
    evaluate(m_individuals[m_individuals.size()-i]);
  }

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CSPopulation::evaluate(Nest& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
