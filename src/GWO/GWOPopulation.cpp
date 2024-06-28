/*
###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021-2024 Davide Pagano & Lorenzo Sostero                     #
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


#include "GWOPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

GWOPopulation::GWOPopulation(Function func) : Population(func) {
  m_a = 0.;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GWOPopulation::init() {
  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();
  m_individuals.resize(pop_size, Wolf(d));

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

  // Dummy assignment of the alpha, beta and delta wolves and best solution.
  // When the cost of the population is actually evaluated this is fixed.
  m_alpha = m_individuals[0];
  m_beta  = m_individuals[1];
  m_delta = m_individuals[2];
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GWOPopulation::setConfig(const GWOConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > GWOPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Wolf* GWOPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GWOPopulation::updateAParameter(std::size_t t) {
  m_a = 2 - t*(2./m_config.getNMaxIterations());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GWOPopulation::moveWolves() {
  double r1, r2, A1, A2, A3, C1, C2, C3, D_alpha, D_beta, D_delta, X1, X2, X3;

  // Loop on the population of wolves
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {

    // Loop on dimension
    for (std::size_t j = 0; j < m_individuals[0].getDimension(); ++j) {
      r1      = m_random.rand();
      r2      = m_random.rand();
      A1      = 2*m_a*r1-m_a;
      C1      = 2*r2;
      D_alpha = fabs(C1*m_alpha[j]-m_individuals[i][j]);
      X1      = m_alpha[j]-A1*D_alpha;

      r1     = m_random.rand();
      r2     = m_random.rand();
      A2     = 2*m_a*r1-m_a;
      C2     = 2*r2;
      D_beta = fabs(C2*m_beta[j]-m_individuals[i][j]);
      X2     = m_beta[j]-A2*D_beta;

      r1      = m_random.rand();
      r2      = m_random.rand();
      A3      = 2*m_a*r1-m_a;
      C3      = 2*r2;
      D_delta = fabs(C3*m_delta[j]-m_individuals[i][j]);
      X3      = m_delta[j]-A3*D_delta;

      m_individuals[i][j] = (X1+X2+X3)/3.;
    }

    // boundary check
    checkBoundary(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GWOPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GWOPopulation::evaluate(Wolf& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  // Update the alpha, beta and delta wolves
  if (value < m_alpha.getCost()) {
    m_alpha = solution;
  }

  if (value > m_alpha.getCost() &&
  value < m_beta.getCost()) {
    m_beta = solution;
  }

  if (value > m_alpha.getCost() &&
  value > m_beta.getCost() &&
  value < m_delta.getCost()) {
    m_delta = solution;
  }

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
