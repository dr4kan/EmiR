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


#include "GSAPopulation.h"
#include <limits>
// [[depends(RcppProgress)]]
#include <progress.hpp>

GSAPopulation::GSAPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::init() {
  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();

  m_individuals.resize(pop_size, Planet(d));

  if (m_initial_population.nrow() > 0) {
    NumericVector v;
    for (std::size_t i = 0; i < (std::size_t) m_initial_population.nrow(); ++i) {
      v = m_initial_population.row(i);
      m_individuals[i].setPosition(Rcpp::as<std::vector<double> >(v));
    }
  } else {

    // Generate randomly the position of the Planets
    if (!m_silent) Rcout << "Generating the initial population...\n";
    Progress progress_bar(pop_size, !m_silent);
    double delta = 0.;
    for (std::size_t i = 0; i < m_individuals.size(); ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
      for (std::size_t j = 0; j < d; ++j) {
        delta = m_search_space[j].getMax()-m_search_space[j].getMin();
        m_individuals[i].setVelocity(j, m_random.rand(-delta, delta));
      }
      progress_bar.increment();
    }
  }

  // Dummy assignment of the best planet. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::setConfig(const GSAConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > GSAPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Planet* GSAPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::setMass() {
  double sum_mass = 0.;
  std::vector<double> mass;
  double size = m_individuals.size();
  double worst_cost = m_individuals[size - 1].getCost();
  double best_cost = m_individuals[0].getCost();
  double delta_mass = worst_cost - best_cost;

  for (std::size_t i = 0; i < size ; ++i) {
    mass.push_back((worst_cost - m_individuals[i].getCost())/delta_mass);
    sum_mass += mass[i];
  }
  for (std::size_t j = 0; j < size; ++j) {
    m_individuals[j].setMass(mass[j] / sum_mass);
  }
}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::setVelocity(std::size_t iter) {
  double beta = m_config.getGravEvolution();
  std::size_t iter_max = m_config.getNMaxIterations();

  double grav = m_config.getGrav() * exp(- beta * (double)(iter)/(double)iter_max);

  double Kbest = m_individuals.size() * (iter_max - iter) / (double)iter_max;

  std::size_t d = m_search_space.getNumberOfParameters();
  std::size_t pop_size = m_config.getPopulationSize();

  double accel = 0.;

  /// Compute distances between planets
  std::vector<std::vector<double>> distance;
  distance.resize(pop_size, std::vector<double>(pop_size, 0.));
  for (std::size_t i = 0; i < pop_size; i++) {
    for (std::size_t j = 0; j < pop_size; j++) {
      distance[i][j] = 0.;
      if (i < j) {
        for (std::size_t v = 0; v < d; v++) {
          distance[i][j] += pow(m_individuals[j][v] - m_individuals[i][v], 2);
        }
        distance[i][j] = pow(distance[i][j], 0.5);
      }
      if (i > j) {
        distance [i][j] = distance [j][i];
      }
    }
  }

  /// Compute the resulting acceleration of the i-planet due to the external gravitational forces
  for (std::size_t i = 0; i < pop_size; i++) {

    for (std::size_t k = 0; k < d; k++) {
      double ref_accel    = 0.;
      for (std::size_t j = 0; j < pop_size; j++) {
        if (distance[i][j] > 0. && j < Kbest) {
          accel = grav * m_individuals[j].getMass() / (distance[i][j]) * (m_individuals[j][k] - m_individuals[i][k]);
          ref_accel += m_random.rand() * accel;
        }
      }

      /// Compute the velocity taking into account the previous velocity and the forces applied
      double vel = m_individuals[i].getVelocity(k) * m_random.rand() + ref_accel;

      m_individuals[i].setVelocity(k, vel);
    }
  }
}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::move(std::size_t iter) {
  // Change the mass of planets
  setMass();

  // Change the velocity of planets
  setVelocity(iter);

  std::size_t d = m_search_space.getNumberOfParameters();
  std::size_t pop_size = m_config.getPopulationSize();

  for (std::size_t i = 0; i < pop_size; ++i) {
    for (std::size_t j = 0; j < d; ++j) {
      m_individuals[i][j] = m_individuals[i][j] + m_individuals[i].getVelocity(j);
    }

    // boundary check
    checkBoundary(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::evaluate(Planet& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  // Update the best solution
  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GSAPopulation::sort() {
  std::sort(m_individuals.begin(), m_individuals.end());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
