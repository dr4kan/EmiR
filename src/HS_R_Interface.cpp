#include "HS/HS_algorithm.h"
#include "Base/OOB.h"

// [[Rcpp::export]]
S4 cpp_minimize_hs(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");
  std::string oob_method = opt.slot("oob_solutions");

  HS_algorithm hs(obj_function, config);
  hs.setConstraints(constraints);
  hs.setParameters(parameters);
  hs.setSilent(silent_mode);
  hs.savePopulation(save_population);
  hs.setOOB(oob_method);
  hs.minimize();
  return hs.getResults();
}
