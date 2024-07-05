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


#include "Algorithm.h"
#include <Rcpp.h>
using namespace Rcpp;


Algorithm::Algorithm(Function obj_function) :
  m_obj_function(obj_function),
  m_pop_out_file_name(""),
  m_save_population(false),
  m_silent(false),
  m_maximize(false),
  m_oob_sol(RBC),
  m_algo_name("") {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setConstraints(List constraints) {
  m_constraints = constraints;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setParameters(List parameters) {
  int n = parameters.length();
  m_search_space = SearchSpace(n);
  m_search_space.setConstraints(m_constraints);
  m_parameter_range = std::vector<std::vector<double> >(n);

  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    m_search_space.setParameter(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"), par.slot("integer"));
    m_parameter_range[i] = {par.slot("min_val"), par.slot("max_val")};
    m_parameter_names.push_back(par.slot("name"));
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::savePopulation(bool t) {
  m_save_population = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setSilent(bool t) {
  m_silent = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setMaximize(bool t) {
  m_maximize = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setOOB(std::string t) {
  if (t == "PBC") {
    m_oob_sol = PBC;
  } else if (t == "BAB") {
    m_oob_sol = BAB;
  } else if (t == "DIS") {
    m_oob_sol = DIS;
  } else if (t == "RBC") {
    m_oob_sol = RBC;
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setConstrainedMethod(std::string t) {
  m_constrained_method = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setInitialPopulation(NumericMatrix t) {
  m_initial_population = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setAlgoName(std::string t) {
  m_algo_name = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setPenaltyScaling(double t) {
  m_penalty_scaling = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setStartPenaltyCoeff(double t) {
  m_start_penalty_param = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setMaxPenaltyCoeff(double t) {
  m_max_penalty_param = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setCostrInitPop(bool t) {
  m_search_space.setCostrInitPop(t);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void Algorithm::setGeneratorFunction(Function t) {
  m_search_space.setGeneratorFunction(t);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Algorithm::rand() {
  return m_search_space.rand();
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::addPopulationPosition(std::vector<std::vector<double> > v) {
  m_population_history.push_back(v);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


S4 Algorithm::getResults() {
  S4 result("OptimizationResults");
  result.slot("algorithm")       = m_algo_name;
  result.slot("iterations")      = m_iter;
  result.slot("population_size") = m_population_base->getSize();
  result.slot("obj_function")    = m_obj_function;
  result.slot("constraints")     = m_constraints;
  result.slot("best_cost")       = m_maximize ? -m_population_base->getBestSolution()->getCost() : m_population_base->getBestSolution()->getCost();
  result.slot("best_parameters") = m_population_base->getBestSolution()->getParameters();
  result.slot("parameter_range") = m_parameter_range;
  result.slot("pop_history")     = m_population_history;
  result.slot("parameter_names") = m_parameter_names;
  result.slot("cost_history")    = m_cost_history;
  result.slot("is_maximization") = m_maximize;

  return result;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
