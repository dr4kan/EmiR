#include "CS/CS_algorithm.h"
#include "Base/OOB.h"

// [[Rcpp::export]]
S4 cpp_minimize_cs(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  CS_algorithm cs(obj_function, config);
  cs.setConstraints(constraints);
  cs.setParameters(parameters);
  cs.setSilent(silent_mode);
  cs.savePopulation(save_population);
  cs.setOOB(oob_method);
  cs.minimize();
  return cs.getResults();
}
