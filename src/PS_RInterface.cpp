#include <Rcpp.h>
using namespace Rcpp;

// [[depends(RcppProgress)]]
#include <progress.hpp>
#include "PSMinimization.h"
#include "Eval.h"

void ComputeCost(PSPopulation& pop, Function cost_function, List constraints, double penality) {
  double cost_value = 0.;
  for (size_t i = 0; i < pop.size(); ++i) {
    cost_value = Eval(pop[i].getPositionVector(), cost_function, constraints, penality);
    pop[i].setCost(cost_value);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


// [[Rcpp::export]]
S4 cstr_minimize_ps(Function cost_function, List constraints, List parameters, S4 config) {
  if (constraints.length() > 0) {
    Rcout << "Starting PS minimization...\n\n";
  } else {
    Rcout << "Starting constrained PS minimization...\n\n";
  }

  int n_iter = config.slot("iterations");
  Progress progress_bar(n_iter, true);

  int n = parameters.length();
  ParametersRange pr(n);
  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    pr.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
  }

  // PS algorithm configuration
  PSConfig algo_config;
  algo_config.setNMaxIterations(n_iter);
  algo_config.setNumberOfParticles(config.slot("n_particles"));
  algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  algo_config.setCognitiveParameter(config.slot("cognitive"));
  algo_config.setSocialParameter(config.slot("social"));
  algo_config.setInertia(config.slot("inertia"));
  algo_config.setVMaxParameter(config.slot("max_velocity"));
  algo_config.setPenaltyParameter(config.slot("penalty_parameter"));

  double penality = config.slot("penalty_parameter");

  // Initialization of the minimizer
  PSMinimization minimizer;
  minimizer.setParametersRange(pr);
  minimizer.cost_history.clear();

  // Initialization of the population
  PSPopulation pop(algo_config, pr);

  int n_sc = 0;
  for (size_t iter = 0; iter < n_iter; ++iter) {

    // Change the velocity of the paricles and move them
    if (iter > 0) pop.moveParticles();

    // Compute the cost for the population
    ComputeCost(pop, cost_function, constraints, penality);

    // Sort the population according to the best cost
    pop.sort();
    if (minimizer.cost_history.size() <= iter) {
      minimizer.cost_history.push_back(pop[0].getBestCost());
    }

    // Check on parameters at boundary
    if (minimizer.verbose > minimizer.SILENT) {
      minimizer.checkParameterBoundary(pop[0].getBestPosition(), iter);
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
  };

  if (pop[0].getBestCost() < minimizer.best_cost) {
    minimizer.best_cost = pop[0].getBestCost();
    minimizer.fitted_parmaters = pop[0].getBestPosition();
    minimizer.checkParameterBoundary();
  }

  S4 result("MinimizationResult");
  result.slot("algorithm")       = "PS";
  result.slot("best_cost")       = minimizer.best_cost;
  result.slot("best_parameters") = minimizer.fitted_parmaters;
  result.slot("cost_history")    = minimizer.cost_history;

  return result;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
