#include "NEW/NEW_algorithm.h"
#include "Base/OOB.h"

// [[Rcpp::export]]
S4 cpp_minimize_new(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  NEW_algorithm new_algo(obj_function, config);
  new_algo.setConstraints(constraints);
  new_algo.setParameters(parameters);
  new_algo.setSilent(silent_mode);
  new_algo.savePopulation(save_population);
  new_algo.setOOB(oob_method);
  new_algo.minimize();
  return new_algo.getResults();
}
