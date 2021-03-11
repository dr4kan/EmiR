#include "PS/PS_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_ps(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  PS_algorithm ps(obj_function, config);
  ps.setConstraints(constraints);
  ps.setParameters(parameters);
  ps.setSilent(silent_mode);
  ps.savePopulation(save_population);
  ps.setOOB(oob_method);
  ps.minimize();
  return ps.getResults();
}
