#include <Rcpp.h>
using namespace Rcpp;

#include "GAMinimization.h"

NumericVector eval_GA(std::vector<double> x, Function f) {
  NumericVector res = f(x);
  return res;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void ComputeCost(GAPopulation& pop, Function cost_function) {
  double cost_value = 0.;
  for (size_t i = 0; i < pop.size(); ++i) {
    cost_value = eval_GA(pop[i].getGenes(), cost_function)[0];
    pop[i].setCost(cost_value);
    pop[i].setIndicatorUp();
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


//' Genetic Algorithm minimization
//'
//' Minimize a cost function using the Genetic Algorithm (GA) algorithm.
//'
//' @param cost_function cost function to be minimized.
//' @param parameters a list of objects of class `Parameter` the cost function is minimized with respect to.
//' See \link[EmiR]{parameter}.
//' @param config an object of class `GAConfig` with the configuration parameters
//' for the GA algorithm. See \link[EmiR]{config_GA}.
//' @return `minimize_GA` returns an object of class `MinimizationResult`.
//' @examples
//' library(EmiR)
//'
//' eggholder <- function(x) {
//'   value = -(x[2]+47)*sin(sqrt(abs(x[1]/2+x[2]+47)))+x[1]*sin(sqrt(abs(x[1]-(x[2]+47))));
//'   return(value)
//' }
//'
//' x1 <- parameter("x1", -512, 512)
//' x2 <- parameter("x2", -512, 512)
//' l <- list(x1, x2)
//'
//' config <- config_GA(iterations = 250, n_particles = 100)
//' ga <- minimize_GA(cost_function = eggholder,
//'                   parameters = l,
//'                   config = config)
//' print(ga)
//' @export
// [[Rcpp::export]]
S4 minimize_GA(Function cost_function, List parameters, S4 config) {
  Rcout << "Staring GA minimization...\n";

  int n = parameters.length();
  ParametersRange pr(n);
  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    pr.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
  }

  // GA algorithm configuration
  GAConfig algo_config;
  algo_config.setNMaxIterations(config.slot("iterations"));
  algo_config.setPopulationSize(config.slot("population_size"));
  algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  algo_config.setKeepFraction(config.slot("keep_fraction"));
  algo_config.setMutationRate(config.slot("m_mutation_rate"));

  // Initialization of the minimizer
  GAMinimization minimizer;
  minimizer.setParametersRange(pr);
  minimizer.cost_history.clear();

  // Initialization of the population
  GAPopulation pop(algo_config, pr);

  // Compute the cost for the population
  ComputeCost(pop, cost_function);

  // Sort the population according to the best cost
  pop.sort();
  if (minimizer.cost_history.size() == 0) {
    minimizer.cost_history.push_back(pop[0].getCost());
  }

  int n_sc = 0;
  for (size_t iter = 1; iter < algo_config.getNMaxIterations(); ++iter) {
    pop.crossover();
    ComputeCost(pop, cost_function);
    pop.sort();
    pop.mutation();
    ComputeCost(pop, cost_function);
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
