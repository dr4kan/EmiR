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


#include "PS/PS_algorithm.h"
#include "Base/OOB.h"

// [[Rcpp::export]]
S4 cpp_minimize_ps(Function obj_function,
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

  PS_algorithm ps(obj_function, config);
  ps.setConstraints(constraints);
  ps.setParameters(parameters);
  ps.setSilent(silent_mode);
  ps.setMaximize(maximize);
  ps.savePopulation(save_pop_history);
  ps.setConstrainedMethod(constrained_method);
  ps.setPenaltyScaling(penalty_scale);
  ps.setStartPenaltyCoeff(start_penalty_param);
  ps.setMaxPenaltyCoeff(max_penalty_param);
  ps.setCostrInitPop(constr_init_pop);
  ps.setOOB(oob_method);
  ps.setSeed(seed);
  ps.setInitialPopulation(initial_population);
  ps.setAlgoName("PS");
  if (use_generation_func) ps.setGeneratorFunction(generation_function);
  ps.minimize();
  return ps.getResults();
}
