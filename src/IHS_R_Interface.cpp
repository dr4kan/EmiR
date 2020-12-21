#include "IHS/IHS_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_ihs(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");
  bool save_population = opt.slot("save_population");

  IHS_algorithm ihs(obj_function, config);
  ihs.setConstraints(constraints);
  ihs.setParameters(parameters);
  ihs.setSilent(silent_mode);
  ihs.savePopulation(save_population);
  ihs.minimize();
  return ihs.getResults();
}
