#include "BAT/BAT_algorithm.h"

// [[Rcpp::export]]
S4 cpp_minimize_bat(Function obj_function,
  List constraints,
  List parameters,
  S4 config,
  S4 opt) {
  bool silent_mode = opt.slot("silent_mode");

  BAT_algorithm bat(obj_function, config);
  bat.setConstraints(constraints);
  bat.setParameters(parameters);
  bat.setSilent(silent_mode);
  bat.minimize();
  return bat.getResults();
}
