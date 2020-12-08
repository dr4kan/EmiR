#ifndef EmiR_Eval_h
#define EmiR_Eval_h

#include <Rcpp.h>
using namespace Rcpp;

double Eval(std::vector<double> x, Function obj_func, List constraints, double r) {
  // r = penalty parameter
  NumericVector tmp_v = obj_func(x);
  double value = tmp_v[0];
  double penalty = 0.;

  for (int i = 0; i < constraints.length(); ++i) {
    S4 constraint = constraints[i];
    Function g = constraint.slot("func");
    std::string inequality = constraint.slot("inequality");
    tmp_v = g(x);
    double tmp_d = tmp_v[0];
    if (inequality == "<=" || inequality == "<") {
      penalty += pow(std::max(0., tmp_d), 2);
    } else {
      penalty += pow(std::min(0., tmp_d), 2);
    }
  }
  value += r*penalty;

  return value;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#endif
