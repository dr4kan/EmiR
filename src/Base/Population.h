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


#ifndef EmiR_Population_h
#define EmiR_Population_h

#include "SearchSpace.h"
#include "OOB.h"
#include "Random.h"
#include "Individual.h"
#include <random>
#include <Rcpp.h>
using namespace Rcpp;

class Population {
public:

  Population(Function);

  void setSearchSpace(const SearchSpace&);

  /// Set the seed for the random generator
  void setSeed(uint64_t);

  void setConstraints(List);

  void setOOB(OOBMethod);

  void setMaximization(bool);

  void setSilent(bool);

  void setConstrainedMethod(std::string);

  void scalePenaltyCoeff();

  void setPenaltyScaling(double t) {m_penalty_scaling = t;};

  void setStartPenaltyCoeff(double t) {m_penalty_coeff = t;};

  void setMaxPenaltyCoeff(double t) {m_max_penalty_param = t;};

  void setInitialPopulation(NumericMatrix);

  virtual Individual* getBestSolution() {return nullptr;};

  virtual std::size_t getSize() {return 0;};

protected:

  bool ckeckViolateConstraints(std::vector<double>&);

  double constraintsPenaltyMethod(std::vector<double>&);

  double constraintsBarrierMethod(std::vector<double>&);

  void checkBoundary(Individual&);

  double evaluateCost(std::vector<double>&);

  Random        m_random;
  SearchSpace   m_search_space;
  Function      m_obj_func;
  List          m_constraints;
  OOBMethod     m_oob_sol;
  bool          m_maximization;
  NumericMatrix m_initial_population;
  double        m_penalty_coeff;
  double        m_penalty_scaling;
  double        m_max_penalty_param;
  std::string   m_constrained_method;
  bool          m_silent;
  std::size_t   m_n_constraints;
};

#endif
