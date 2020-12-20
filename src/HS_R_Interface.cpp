#include "HS/HS_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_hs(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");

  HS_algorithm hs(obj_function, config);
  hs.setConstraints(constraints);
  hs.setParameters(parameters);
  hs.setSilent(silent_mode);
  hs.minimize();
  return hs.getResults();
}
