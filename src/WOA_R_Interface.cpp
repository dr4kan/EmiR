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


#include "WOA/WOA_algorithm.h"
#include "Base/OOB.h"

// [[Rcpp::export]]
S4 cpp_minimize_woa(Function obj_function,
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

  WOA_algorithm woa(obj_function, config);
  woa.setConstraints(constraints);
  woa.setParameters(parameters);
  woa.setSilent(silent_mode);
  woa.setMaximize(maximize);
  woa.savePopulation(save_pop_history);
  woa.setConstrainedMethod(constrained_method);
  woa.setPenaltyScaling(penalty_scale);
  woa.setStartPenaltyCoeff(start_penalty_param);
  woa.setMaxPenaltyCoeff(max_penalty_param);
  woa.setCostrInitPop(constr_init_pop);
  woa.setOOB(oob_method);
  woa.setSeed(seed);
  woa.setInitialPopulation(initial_population);
  woa.setAlgoName("WOA");
  woa.minimize();
  return woa.getResults();
}
