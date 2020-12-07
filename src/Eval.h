#ifndef EmiR_Eval_h
#define EmiR_Eval_h

#include <Rcpp.h>
using namespace Rcpp;

double Eval(std::vector<double>, Function, List, double);

#endif
