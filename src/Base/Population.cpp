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


#include "Population.h"

Population::Population(Function func) :
  m_obj_func(func),
  m_maximization(false),
  m_penalty_coeff(2.),
  m_penalty_scaling(10.),
  m_max_penalty_param(1.e10),
  m_silent(false) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setSeed(uint64_t t_seed) {
  if (t_seed > 0) m_random = Random(t_seed);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void Population::setSearchSpace(const SearchSpace& t_search_space) {
  m_search_space = t_search_space;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setConstraints(List constraints) {
  m_constraints = constraints;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setOOB(OOBMethod t) {
  m_oob_sol = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setConstrainedMethod(std::string t) {
  m_constrained_method = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setInitialPopulation(NumericMatrix t) {
  m_initial_population = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setMaximization(bool t) {
  m_maximization = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::setSilent(bool t) {
  m_silent = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::scalePenaltyCoeff() {
  m_penalty_coeff = std::min(m_max_penalty_param, m_penalty_coeff*m_penalty_scaling);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


bool Population::ckeckViolateConstraints(std::vector<double>& v) {
  for (int i = 0; i < m_constraints.length(); ++i) {
    S4 constraint = m_constraints[i];
    Function g = constraint.slot("func");
    std::string inequality = constraint.slot("inequality");
    NumericVector tmp_costraint = g(v);
    double tmp_d = tmp_costraint[0];

    if (inequality == "<" && tmp_d >= 0) {
      return true;
    } else if (inequality == "<=" && tmp_d > 0) {
      return true;
    } else if (inequality == ">=" && tmp_d < 0) {
      return true;
    } else if (inequality == ">" && tmp_d <= 0) {
      return true;
    }
  }

  return false;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Population::constraintsBarrierMethod(std::vector<double>& v) {
  if (ckeckViolateConstraints(v)) return std::numeric_limits<double>::max();
  NumericVector tmp_v = m_obj_func(v);
  return tmp_v[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Population::constraintsPenaltyMethod(std::vector<double>& v) {
  NumericVector tmp_v;
  double penalty = 0.;

  for (int i = 0; i < m_constraints.length(); ++i) {
    S4 constraint = m_constraints[i];
    Function g = constraint.slot("func");
    std::string inequality = constraint.slot("inequality");
    NumericVector tmp_costraint = g(v);
    double tmp_d = tmp_costraint[0];

    if ((inequality == "<" && tmp_d >= 0) ||
        (inequality == "<=" && tmp_d > 0) ||
        (inequality == ">=" && tmp_d < 0) ||
        (inequality == ">" && tmp_d <= 0)) {
      penalty += fabs(tmp_d);
    }
  }

  if (m_maximization) penalty = -penalty;

  tmp_v = m_obj_func(v);
  return (tmp_v[0] + m_penalty_coeff*penalty);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Population::evaluateCost(std::vector<double>& v) {
  double value;

  // In case of integer parameters
  for (std::size_t j = 0; j < v.size(); ++j) {
    if (m_search_space[j].isInteger()) {
      v[j] = round(v[j]); // floor the parameter
      if (v[j] < m_search_space[j].getMin()) {
        v[j]++;
      } else if (v[j] > m_search_space[j].getMax()) {
        v[j]--;
      }
    }
  }

  if (m_constrained_method == "PENALTY") {

    value = constraintsPenaltyMethod(v);

  } else if (m_constrained_method == "BARRIER") {

    value = constraintsBarrierMethod(v);

  } else {

    // if violate any of the contraints, regenerate
    if (ckeckViolateConstraints(v)) {
      v = m_search_space.getNew(v);
    }

    NumericVector tmp_v = m_obj_func(v);
    value = tmp_v[0];

  }

  // If performing a maximization change the sign of the value
  if (m_maximization) return -value;

  return value;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Population::checkBoundary(Individual& t) {
  std::size_t d = m_search_space.getNumberOfParameters();

  if (m_constraints.length() > 0 && m_oob_sol == DIS) { // Disregard the out-of-bound solution and generate new ones (DIS)

    t.setPosition(m_search_space.getRandom());

  } else {

    // loop on dimension
    for (std::size_t j = 0; j < d; ++j) {

      if (m_oob_sol == PBC) { // Periodic Boundary Condition (PBC)

        if (t[j] < m_search_space[j].getMin()) t[j] = m_search_space[j].getMax() - fabs(t[j] - m_search_space[j].getMin());
        if (t[j] > m_search_space[j].getMax()) t[j] = m_search_space[j].getMin() + fabs(m_search_space[j].getMax() - t[j]);

        if (t[j] < m_search_space[j].getMin() || t[j] > m_search_space[j].getMax()) t[j] = m_search_space.getRandom(j);

      } else if (m_oob_sol == BAB) { // Place out-of-bound solutions back at the boundaries (BAB)

        if (t[j] < m_search_space[j].getMin()) t[j] = m_search_space[j].getMin();
        if (t[j] > m_search_space[j].getMax()) t[j] = m_search_space[j].getMax();

      } else if (m_oob_sol == DIS) { // Disregard the out-of-bound solution and generate new ones (DIS)

        if (t[j] < m_search_space[j].getMin() ||
            t[j] > m_search_space[j].getMax()) t[j] = m_random.rand(m_search_space[j].getMin(), m_search_space[j].getMax());

      } else if (m_oob_sol == RBC) { // Reflective Boundary Condition (RBC)

        if (t[j] < m_search_space[j].getMin()) t[j] = 2 * m_search_space[j].getMin() - t[j];
        if (t[j] > m_search_space[j].getMax()) t[j] = 2 * m_search_space[j].getMax() - t[j];

        if (t[j] < m_search_space[j].getMin() || t[j] > m_search_space[j].getMax()) t[j] = m_search_space.getRandom(j);

        if (t.hasVelocity()) t.setVelocity(j, -t.getVelocity(j));
      }

    }
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
