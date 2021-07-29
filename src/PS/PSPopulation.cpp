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


#include "PSPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

PSPopulation::PSPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  NumericVector alpha = m_config.getAlpha();

  // check on the size of alpha_vel
  if (alpha.length() == 1 && (size_t) alpha.length() < d) {
    std::vector<double> v(d);
    std::fill(v.begin(), v.end(), alpha[0]);
    alpha = v;
    m_config.setAlpha(alpha);
  } else if (alpha.length() > 1 && (size_t) alpha.length() != d) {
    stop("Wrong size for parameter alpha_vel.\n");
  }
  //////////////////////////////////////

  m_individuals.resize(pop_size, PSParticle(d));

  if (m_initial_population.nrow() > 0) {
    NumericVector v;
    for (size_t i = 0; i < (size_t) m_initial_population.nrow(); ++i) {
      v = m_initial_population.row(i);
      m_individuals[i].setPosition(Rcpp::as<std::vector<double> >(v));
    }
  } else {

    // Generate randomly the position of the Planets
    if (!m_silent) Rcout << "Generating the initial population...\n";
    Progress progress_bar(pop_size, !m_silent);
    double delta = 0.;
    for (size_t i = 0; i < m_individuals.size(); ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
      for (size_t j = 0; j < d; ++j) {
        delta = m_search_space[j].getMax()-m_search_space[j].getMin();
        m_individuals[i].setVelocity(j, m_random.rand(-delta*alpha[j], delta*alpha[j]));
      }
      progress_bar.increment();
    }
  }

  // Dummy assignment of the best planet. When the cost of
  // the population is actually evaluated this is fixed.
    m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::setConfig(const PSConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> PSPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_individuals.size());
  for (size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


PSParticle* PSPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::setVelocity(size_t iter) {
  NumericVector alpha = m_config.getAlpha();
  double inertia_initial = m_config.getInertia();
  double h = m_config.getAlphaEvolution();
  size_t iter_max = m_config.getNMaxIterations();

  double cognitive_par = m_config.getCognitiveParameter();
  double social_par = m_config.getSocialParameter();
  double inertia = inertia_initial * (1.0 - 0.5 * ((double)(iter)/(double)iter_max));
  double k = std::pow(1.0 - ((double)(iter)/(double)iter_max), h);

  std::transform(alpha.begin(), alpha.end(), alpha.begin(), [k](double &c) { return c*k; });

  for (size_t j = 0; j < m_individuals[0].getDimension(); ++j) {

    double delta = m_search_space[j].getMax() - m_search_space[j].getMin();

    for (size_t i = 0; i < m_individuals.size(); ++i) {
      // Compute the step and assign if it satisfies the constraint on the maximum velocity
      double cognitive = cognitive_par * m_random.rand() *
      (m_individuals[i].getBestPositionParticle(j) - m_individuals[i][j]);
      double social = social_par * m_random.rand() *
      (m_best_solution[j] - m_individuals[i][j]);
      double vel = (m_individuals[i].getVelocity(j) * inertia + cognitive + social);

      if (fabs(vel) < alpha[j] * delta) {
        m_individuals[i].setVelocity(j, vel);
      } else {
        if (vel > alpha[j] * delta) {
          m_individuals[i].setVelocity(j, alpha[j] * delta);
        } else {
          m_individuals[i].setVelocity(j, - alpha[j] * delta);
        }
      }

    }
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::moveParticles(size_t iter) {
  // Change the velocity of the particles
  setVelocity(iter);

  for (size_t i = 0; i < m_individuals.size(); ++i) {
    for (size_t j = 0; j < m_individuals[0].getDimension(); ++j) {
      m_individuals[i][j] = m_individuals[i][j] + m_individuals[i].getVelocity(j);
    }

    // boundary check
    checkBoundary(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::evaluate() {
  for (size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::evaluate(PSParticle& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (ckeckViolateConstraints(solution.getPosition()) == false) {

    // Update personal best solution
    solution.setPersonalBest();

    // Update the global best solution
    if (value < m_best_solution.getCost()) {
      m_best_solution = solution;
    }

  };
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
