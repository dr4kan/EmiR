#include "GSA/GSA_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_gsa(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  GSA_algorithm gsa(obj_function, config);
  gsa.setConstraints(constraints);
  gsa.setParameters(parameters);
  gsa.setSilent(silent_mode);
  gsa.savePopulation(save_population);
  gsa.setOOB(oob_method);
  gsa.minimize();
  return gsa.getResults();
}
