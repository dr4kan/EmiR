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


#include "WOAPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>


WOAPopulation::WOAPopulation(Function func) : Population(func) {
  m_a = 0.;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void WOAPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_individuals.resize(pop_size, Whale(d));

  if (m_initial_population.nrow() > 0) {

    // Load the positions provided by the user
    NumericVector v;
    for (size_t i = 0; i < (size_t) m_initial_population.nrow(); ++i) {
      v = m_initial_population.row(i);
      m_individuals[i].setPosition(Rcpp::as<std::vector<double> >(v));
    }

  } else {

    // Generate randomly the position of the individuals
    if (!m_silent) Rcout << "Generating the initial population...\n";
    Progress progress_bar(pop_size, !m_silent);
    for (size_t i = 0; i < m_individuals.size(); ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
      progress_bar.increment();
    }

  }

  // Dummy assignment of the best individual. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void WOAPopulation::setConfig(const WOAConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > WOAPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Whale* WOAPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void WOAPopulation::updateParameters(size_t t) {
  m_a  = 2. - t*(2./m_config.getNMaxIterations());
  m_a2 = -1. + t*((-1.)/m_config.getNMaxIterations());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void WOAPopulation::moveWhales() {
  double r1, r2, A, C, b, l, rw, p, D_tmp, D_best, distance;
  Whale tmp;
  // Loop on the population of whales
  for (size_t i = 0; i < m_individuals.size(); ++i) {

    r1 = m_random.rand();
    r2 = m_random.rand();
    A  = 2*m_a*r1-m_a;
    C  = 2*r2;
    b  = 1.;
    l  = (m_a2-1)*m_random.rand()+1;
    p  = m_random.rand();

    // Loop on dimension
    for (size_t j = 0; j < m_individuals[0].getDimension(); ++j) {

      if (p < 0.5) {

        if (fabs(A) >= 1) {
          // random whale
          rw             = m_random.randUInt(0, m_individuals.size());
          tmp            = m_individuals[rw];
          D_tmp          = fabs(C*tmp[j] - m_individuals[i][j]);
          m_individuals[i][j] = tmp[j] - A*D_tmp;

        } else {
          // encircling prey
          D_best         = fabs(C*m_best_solution[j] - m_individuals[i][j]);
          m_individuals[i][j] = m_best_solution[j]-A*D_best;
        }

      } else {
        // distance whale to the prey
        distance       = fabs(m_best_solution[j] - m_individuals[i][j]);
        m_individuals[i][j] = distance*exp(b*l)*cos(l*2*M_PI) + m_best_solution[j];
      }
    }

    // boundary check
    checkBoundary(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void WOAPopulation::evaluate() {
  for (size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void WOAPopulation::evaluate(Whale& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
