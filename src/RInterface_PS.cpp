#include <Rcpp.h>
using namespace Rcpp;

#include "PSMinimization.h"

NumericVector eval_PS(std::vector<double> x, Function f) {
  NumericVector res = f(x);
  return res;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// [[Rcpp::export]]
S4 minimize_PS(Function cost_function, List parameters) {
  int n = parameters.length();
  ParametersRange pr(n);
  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    pr.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
  }

  // PS algorithm configuration
  PSConfig algo_config;

  // Initialization of the minimizer
  PSMinimization minimizer;
  minimizer.setParametersRange(pr);
  minimizer.cost_history.clear();

  // Initialization of the population
  PSPopulation pop(algo_config, pr);

  int n_sc = 0;
  double cost_value = 0.;
  for (size_t i = 0; i < algo_config.getNMaxIterations(); ++i) {

    // Change the velocity of the paricles and move them
    if (i > 0) pop.moveParticles();

    // Compute the cost for the population
    for (size_t i = 0; i < pop.size(); ++i) {
      //      print(eval_PS(pop[i].getPositionVector(), func));
      cost_value = eval_PS(pop[i].getPositionVector(), cost_function)[0];
      pop[i].setCost(cost_value);
    }

    // Sort the population according to the best cost
    pop.sort();
    if (minimizer.cost_history.size() <= i) {
      minimizer.cost_history.push_back(pop[0].getBestCost());
    }

    // Check on parameters at boundary
    if (minimizer.verbose > minimizer.SILENT) {
      minimizer.checkParameterBoundary(pop[0].getBestPosition(), i);
    }

    // Check on same cost iterations
    if (i > 0 && Utility::areEqual(minimizer.cost_history[i-1], minimizer.cost_history[i], 2)) {
      n_sc++;
    } else {
      n_sc = 0;
    }
    if (n_sc > algo_config.getNMaxIterationsSameCost()) break;
  };

  if (std::isnan(minimizer.best_cost)) {
    minimizer.best_cost = pop[0].getBestCost();
    minimizer.fitted_parmaters = pop[0].getBestPosition();
    minimizer.checkParameterBoundary();
  } else {
    if (pop[0].getBestCost() < minimizer.best_cost) {
      minimizer.best_cost = pop[0].getBestCost();
      minimizer.fitted_parmaters = pop[0].getBestPosition();
      minimizer.checkParameterBoundary();
    }
  }

  S4 result("MinimizationResult");
  result.slot("best_cost") = minimizer.best_cost;
  result.slot("best_parameters") = minimizer.fitted_parmaters;
  result.slot("cost_history") = minimizer.cost_history;

  return result;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
