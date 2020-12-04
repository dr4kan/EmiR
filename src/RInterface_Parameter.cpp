#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
S4 parameter(std::string name, double min_val, double max_val) {
  S4 p("Parameter");
  p.slot("name")    = name;
  p.slot("min_val") = min_val;
  p.slot("max_val") = max_val;
  return p;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
