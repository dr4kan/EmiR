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


#include "BATPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

BATPopulation::BATPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_loudness = m_config.getInitialLoudness();
  m_pulse_rate = m_config.getInitialPulseRate() * (1 - exp(-m_config.getGamma()));
  m_individuals.resize(pop_size, Bat(d));

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
      m_individuals[i].setFrequency(m_random.rand(m_config.getMinFrequency(), m_config.getMaxFrequency()));
      m_individuals[i].setPosition(m_search_space.getRandom());
    }

  }

  // Dummy assignment of the best individual. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::setConfig(const BATConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > BATPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Bat* BATPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::updateLoudnessAndPulse(size_t t) {
  m_loudness = m_config.getAlpha() * m_loudness;
  m_pulse_rate = m_config.getInitialPulseRate() * (1 - exp(-m_config.getGamma() * (t+1)));
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::moveBats() {
  size_t d = m_search_space.getNumberOfParameters();
  double v = 0.;
  bool update_p = false;
  bool update_l = false;
  Bat tmp(d);

  for (size_t i = 0; i < m_individuals.size(); ++i) { // loop on population

    update_p = m_random.rand() < m_pulse_rate ? true : false;
    update_l = m_random.rand() < m_loudness ? true : false;

    // update the frequency
    tmp.setFrequency(m_random.rand(m_config.getMinFrequency(), m_config.getMaxFrequency()));

    // update position and velocity
    for (size_t j = 0; j < d; ++j) { // loop on dimension
      v = tmp.getVelocity(j) + (tmp[j] - m_best_solution[j])*tmp.getFrequency();
      tmp.setVelocity(j, v);
      tmp[j] = tmp[j] + v;

      // improving the best solution
      if (update_p) {
        tmp[j] = m_best_solution[j] + m_random.rand(-1., 1.)*m_loudness;
      }
    }

    // boundary check
    checkBoundary(tmp);

    // evaluate
    evaluate(tmp);

    // conditionally save of the new solution
    if (update_l && tmp.getCost() < m_individuals[i].getCost()) {
      m_individuals[i] = tmp;
    }

    // update the best solution
    // this is done automatically when evaluating tmp
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double BATPopulation::getPulseRate() const {
  return m_pulse_rate;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double BATPopulation::getLoudness() const {
  return m_loudness;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::evaluate() {
  for (size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::evaluate(Bat& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
