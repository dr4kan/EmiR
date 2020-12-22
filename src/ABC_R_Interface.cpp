#include "ABC/ABC_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_abc(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  ABC_algorithm abc(obj_function, config);
  abc.setConstraints(constraints);
  abc.setParameters(parameters);
  abc.setSilent(silent_mode);
  abc.savePopulation(save_population);
  abc.setOOB(oob_method);
  abc.minimize();
  return abc.getResults();
}
