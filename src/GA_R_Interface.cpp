#include "GA/GA_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_ga(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  GA_algorithm ga(obj_function, config);
  ga.setConstraints(constraints);
  ga.setParameters(parameters);
  ga.setSilent(silent_mode);
  ga.savePopulation(save_population);
  ga.setOOB(oob_method);
  ga.minimize();
  return ga.getResults();
}
