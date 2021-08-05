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


#ifndef EmiR_Algorithm_h
#define EmiR_Algorithm_h

#include "SearchSpace.h"
#include "Utility.h"
#include "OOB.h"
#include "Population.h"
#include <Rcpp.h>
#include <vector>
#include <string>
#include <fstream>

using namespace Rcpp;

class Algorithm {
public:
  Algorithm(Function);

  void setConstraints(List);
  void setParameters(List);
  void savePopulation(bool);
  void setSilent(bool);
  void setMaximize(bool);
  void setOOB(std::string);
  void setSeed(uint64_t);
  void setConstrainedMethod(std::string);
  void setInitialPopulation(NumericMatrix);
  void setAlgoName(std::string);
  void setPenaltyScaling(double);
  void setStartPenaltyCoeff(double);
  void setMaxPenaltyCoeff(double);
  void setCostrInitPop(bool);
  S4   getResults();

protected:
  double rand();
  void addPopulationPosition(std::vector<std::vector<double> >);

  Function                          m_obj_function;
  List                              m_constraints;
  SearchSpace                       m_search_space;
  std::vector<std::string>          m_parameter_names;
  std::vector<std::vector<double> > m_parameter_range;
  std::vector<double>               m_cost_history;
  std::string                       m_pop_out_file_name;
  bool                              m_save_population;
  bool                              m_silent;
  bool                              m_maximize;
  OOBMethod                         m_oob_sol;
  std::string                       m_algo_name;
  std::size_t                       m_iter;
  Population                        *m_population_base;
  NumericMatrix                     m_initial_population;
  std::ofstream                     m_out_file;
  std::string                       m_constrained_method;
  double                            m_penalty_scaling;
  double                            m_start_penalty_param;
  double                            m_max_penalty_param;
  List                              m_population_history;
};

#endif
