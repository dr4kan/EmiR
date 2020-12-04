#include <Rcpp.h>
using namespace Rcpp;

#include "PSMinimization.h"

// [[Rcpp::export]]
NumericVector eval(NumericVector x, Function f) {
  NumericVector res = f(x);
  print(res);
  return res;
}

// [[Rcpp::export]]
void minimize_PS(Function func, List parameters) {
  int n = parameters.length();
  ParametersRange pr(n);
  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    pr.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
  }

  PSMinimization minimizer;
  minimizer.setParametersRange(pr);
  minimizer.cost_history.clear();
  // PSPopulation pop(m_algo_config, m_parameters_range);
  //
  // int n_sc = 0;
  // for (int i = 0; i < m_algo_config->getNMaxIterations(); ++i) {
  //   // Change the velocity of the paricles and move them
  //   if (i > 0) pop.moveParticles();
  //
  //   // Compute the cost for the population
  //   pop.ComputeCost(func);
  //
  //   // Sort the population according to the best cost
  //   pop.sort();
  //   if (cost_history.size() <= (size_t) i) cost_history.push_back(pop[0].getBestCost());
  //
  //   // Check on parameters at boundary
  //   if (verbose > SILENT) {
  //     checkParameterBoundary(pop[0].getBestPosition(), i);
  //   }
  //
  //   // Check on same cost iterations
  //   if (i > 0 && Utility::areEqual(cost_history[i-1], cost_history[i], 2)) {
  //     n_sc++;
  //   } else {
  //     n_sc = 0;
  //   }
  //   if (n_sc > m_algo_config->getNMaxIterationsSameCost()) break;
  // };
  //
  // if (std::isnan(best_cost)) {
  //   best_cost = pop[0].getBestCost();
  //   fitted_parmaters = pop[0].getBestPosition();
  //   checkParameterBoundary();
  // } else {
  //   if (pop[0].getBestCost() < best_cost) {
  //     best_cost = pop[0].getBestCost();
  //     fitted_parmaters = pop[0].getBestPosition();
  //     checkParameterBoundary();
  //   }
  // }

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
