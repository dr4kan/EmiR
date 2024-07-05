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


#include "HS/HS_algorithm.h"
#include "Base/OOB.h"

// [[Rcpp::export]]
S4 cpp_minimize_hs(Function obj_function,
                   List constraints,
                   List parameters,
                   S4 config,
                   S4 opt) {
  bool maximize = opt.slot("maximize");
  bool silent_mode = opt.slot("silent_mode");
  bool save_pop_history = opt.slot("save_pop_history");
  std::string constrained_method = opt.slot("constrained_method");
  double penalty_scale = opt.slot("penalty_scale");
  double start_penalty_param = opt.slot("start_penalty_param");
  double max_penalty_param = opt.slot("max_penalty_param");
  bool constr_init_pop = opt.slot("constr_init_pop");
  std::string oob_method = opt.slot("oob_solutions");
  auto seed = opt.slot("seed");
  NumericMatrix initial_population = opt.slot("initial_population");
  Function generation_function = opt.slot("generation_function");
  bool use_generation_func = opt.slot("use_generation_func");

  HS_algorithm hs(obj_function, config);
  hs.setConstraints(constraints);
  hs.setParameters(parameters);
  hs.setSilent(silent_mode);
  hs.setMaximize(maximize);
  hs.savePopulation(save_pop_history);
  hs.setConstrainedMethod(constrained_method);
  hs.setPenaltyScaling(penalty_scale);
  hs.setStartPenaltyCoeff(start_penalty_param);
  hs.setMaxPenaltyCoeff(max_penalty_param);
  hs.setCostrInitPop(constr_init_pop);
  hs.setOOB(oob_method);
  hs.setSeed(seed);
  hs.setInitialPopulation(initial_population);
  hs.setAlgoName("HS");
  if (use_generation_func) hs.setGeneratorFunction(generation_function);
  hs.minimize();
  return hs.getResults();
}
