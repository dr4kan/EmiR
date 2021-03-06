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


#include "SAPopulation.h"
// [[depends(RcppProgress)]]
#include <progress.hpp>

SAPopulation::SAPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_individuals.resize(pop_size, SAParticle(d));

  if (m_initial_population.nrow() > 0) {
    NumericVector v;
    for (size_t i = 0; i < (size_t) m_initial_population.nrow(); ++i) {
      v = m_initial_population.row(i);
      m_individuals[i].setPosition(Rcpp::as<std::vector<double> >(v));
    }
  } else {

    Rcout << "Generating the initial population...\n";
    Progress progress_bar(pop_size);
    double delta = 0.;
    for (size_t i = 0; i < pop_size; ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
      for (size_t j = 0; j < d; ++j) {
        delta = m_search_space[j].getMax() - m_search_space[j].getMin();
        m_individuals[i].setVelocity(j, m_random.rand(0, delta));
      }
      progress_bar.increment();
    }
  }

  // Dummy assignment of the best solution. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAPopulation::setConfig(const SAConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> SAPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_individuals.size());
  for (size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAPopulation::move() {
  size_t d = m_search_space.getNumberOfParameters();
  SAParticle tmp;
  double cost_tmp;
  double cost_part;
  double temperature = m_config.getT0();

  for (size_t i = 0; i < m_individuals.size(); ++i) { // loop on population
    for (size_t h = 0; h < d; h++) { // loop on dimension
      tmp = m_individuals[i];
      tmp[h] += m_random.rand(-1., 1.) * m_individuals[i].getVelocity(h);

      checkBoundary(tmp);

      evaluate(tmp);
      cost_tmp = tmp.getCost();
      cost_part = m_individuals[i].getCost();

      if (cost_tmp < cost_part){
        m_individuals[i] = tmp;
        m_individuals[i].upSuccess(h);
      } else if (m_random.rand() < exp((cost_part - cost_tmp) / temperature)) {
        m_individuals[i] = tmp;
        m_individuals[i].upSuccess(h);
      };

    }
  }
}

void SAPopulation::setVelocity() {
  size_t d = m_search_space.getNumberOfParameters();
  size_t Ns = m_config.getNs();
  size_t c = m_config.getC();
  std::vector<size_t> success;
  double vel;

  for (size_t i = 0; i < m_individuals.size(); ++i) { // loop on population
    success = m_individuals[i].getSuccess();
    for (size_t h = 0; h < d; h++) { // loop on dimension
      if (success[h] > 0.6 * Ns){
        vel = m_individuals[i].getVelocity(h) * (1. + c * ((((double) success[h]) / ((double) Ns)) - 0.6) / 0.4);
        m_individuals[i].setVelocity(h, vel);
      } else if (success[h] < 0.4 * Ns) {
        vel = m_individuals[i].getVelocity(h) / (1. + c * (0.4 - (((double) success[h]) / ((double) Ns))) / 0.4);
        m_individuals[i].setVelocity(h, vel);
      };
    }
    m_individuals[i].resetSuccess();
  }

}

void SAPopulation::setStartingPoint(size_t iter) {
  size_t d = m_search_space.getNumberOfParameters();
  size_t n_pop = m_individuals.size();
  double w = m_config.getWmax() - ((double)iter / (double)m_config.getNMaxIterations()) * (m_config.getWmax() - m_config.getWmin());

  //select elite solutions by roulette wheel
  for (size_t i = 0; i < n_pop; ++i) {

    size_t elite1 = 0;
    double ra1 = m_random.rand();
    for (size_t u = 1; u < n_pop; u++) {
      if (ra1 > m_config.getProb(u - 1) && ra1 <= m_config.getProb(u)) elite1 = u;
    };

    size_t elite2 = 0;
    double ra2 = m_random.rand();
    for (size_t u = 1; u < n_pop; u++) {
      if (ra2 > m_config.getProb(u - 1) && ra2 <= m_config.getProb(u)) elite2 = u;
    };

    //set initial point on the basis of the current position and elite best position
    for (size_t j = 0; j < d; ++j) {
      double ra3 = m_random.rand();
      double ra4 = m_random.rand();

      double best_position = m_individuals[j].getBestPositionComponent(j);
      m_individuals[i][j] = best_position + w * (ra3 * (m_individuals[elite1].getBestPositionComponent(j) - best_position)
      + ra4 * (m_individuals[elite2].getBestPositionComponent(j) - best_position));

    }
    checkBoundary(m_individuals[i]);
  }

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAPopulation::sort() {
  std::sort(m_individuals.begin(), m_individuals.end());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAPopulation::evaluate() {
  for (size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAPopulation::evaluate(SAParticle& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (ckeckViolateConstraints(solution.getPosition()) == false) {
    solution.setBest();
    if (solution.getCost() < m_best_solution.getCost()){
      m_best_solution = solution;
    };
  };

}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
