#include "SA/SA_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_sa(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  SA_algorithm sa(obj_function, config);
  sa.setConstraints(constraints);
  sa.setParameters(parameters);
  sa.setSilent(silent_mode);
  sa.savePopulation(save_population);
  sa.setOOB(oob_method);
  sa.minimize();
  return sa.getResults();
}
