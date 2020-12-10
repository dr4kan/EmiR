#include <Rcpp.h>
using namespace Rcpp;

// [[depends(RcppProgress)]]
#include <progress.hpp>
#include "GAMinimization.h"
#include "Eval.h"


void ComputeCost(GAPopulation& pop, Function cost_function, List constraints, double penality) {
  double cost_value = 0.;
  for (size_t i = 0; i < pop.size(); ++i) {
    cost_value = Eval(pop[i].getGenes(), cost_function, constraints, penality);
    pop[i].setCost(cost_value);
    pop[i].setIndicatorUp();
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


// [[Rcpp::export]]
S4 cstr_minimize_ga(Function cost_function, List constraints, List parameters, S4 config) {
  if (constraints.length() > 0) {
    Rcout << "Starting GA minimization...\n\n";
  } else {
    Rcout << "Starting constrained GA minimization...\n\n";
  }

  int n_iter = config.slot("iterations");
  Progress progress_bar(n_iter, true);

  int n = parameters.length();
  ParametersRange pr(n);
  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    pr.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
  }

  // GA algorithm configuration
  GAConfig algo_config;
  algo_config.setNMaxIterations(n_iter);
  algo_config.setPopulationSize(config.slot("population_size"));
  algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  algo_config.setKeepFraction(config.slot("keep_fraction"));
  algo_config.setMutationRate(config.slot("mutation_rate"));
  algo_config.setPenaltyParameter(config.slot("penalty_parameter"));

  double penality = config.slot("penalty_parameter");

  // Initialization of the minimizer
  GAMinimization minimizer;
  minimizer.setParametersRange(pr);
  algo_config.setConfigCrossover();
  minimizer.cost_history.clear();

  // Initialization of the population
  GAPopulation pop(algo_config, pr);

  // Compute the cost for the population
  ComputeCost(pop, cost_function, constraints, penality);

  // Sort the population according to the best cost
  pop.sort();
  if (minimizer.cost_history.size() == 0) {
    minimizer.cost_history.push_back(pop[0].getCost());
  }

  int n_sc = 0;
  for (size_t iter = 1; iter < (size_t) n_iter; ++iter) {
    pop.crossover();
    ComputeCost(pop, cost_function, constraints, penality);
    pop.sort();
    pop.mutation();
    ComputeCost(pop, cost_function, constraints, penality);
    pop.sort();
    if (minimizer.cost_history.size() <= iter) {
      minimizer.cost_history.push_back(pop[0].getCost());
    }

    // Check on parameters at boundary
    if (minimizer.verbose > minimizer.SILENT) {
      minimizer.checkParameterBoundary(pop[0].getGenes(), iter);
    }

    // Check on same cost iterations
    if (iter > 0 && Utility::areEqual(minimizer.cost_history[iter-1], minimizer.cost_history[iter], 2)) {
      n_sc++;
    } else {
      n_sc = 0;
    }
    if (n_sc > algo_config.getNMaxIterationsSameCost()) break;

    // Update progress bar
    progress_bar.increment();
  }

  if (pop[0].getCost() < minimizer.best_cost) {
    minimizer.best_cost = pop[0].getCost();
    minimizer.fitted_parmaters = pop[0].getGenes();
    minimizer.checkParameterBoundary();
  }

  S4 result("MinimizationResult");
  result.slot("algorithm")       = "GA";
  result.slot("best_cost")       = minimizer.best_cost;
  result.slot("best_parameters") = minimizer.fitted_parmaters;
  result.slot("cost_history")    = minimizer.cost_history;

  return result;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
