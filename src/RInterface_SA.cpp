#include <Rcpp.h>
using namespace Rcpp;

#include "SAMinimization.h"

NumericVector eval_SA(std::vector<double> x, Function f) {
  NumericVector res = f(x);
  return res;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//' Simulated Annealing minimization
//'
//' Minimize a cost function using the Simulated Annealing (SA) algorithm.
//'
//' @param cost_function cost function to be minimized.
//' @param parameters a list of objects of class `Parameter` the cost function is minimized with respect to.
//' See \link[EmiR]{parameter}.
//' @param config an object of class `SAConfig` with the configuration parameters
//' for the PS algorithm. See \link[EmiR]{config_SA}.
//' @return `minimize_SA` returns an object of class `MinimizationResult`.
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
//' config <- config_SA(iterations = 250, n_particles = 100)
//' ps <- minimize_SA(cost_function = eggholder,
//'                   parameters = l,
//'                   config = config)
//' print(ps)
//' @export
// [[Rcpp::export]]
S4 minimize_SA(Function cost_function, List parameters, S4 config) {
  Rcout << "Staring SA minimization...\n";

  int n = parameters.length();
  ParametersRange pr(n);
  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    pr.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
  }

  // PS algorithm configuration
  SAConfig algo_config;
  algo_config.setNMaxIterations(config.slot("iterations"));
  algo_config.setNumberOfParticles(config.slot("n_particles"));
  algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  algo_config.setCognitiveParameter(config.slot("cognitive"));
  algo_config.setSocialParameter(config.slot("social"));
  algo_config.setInertia(config.slot("dumping"));
  algo_config.setTemp(config.slot("temperature"));

  // Initialization of the minimizer
  SAMinimization minimizer;
  minimizer.setParametersRange(pr);
  minimizer.cost_history.clear();

  // Initialization of the population
  SAPopulation pop(algo_config, pr);

  std::random_device rd;
  std::mt19937 gen(rd());

  int n_sc = 0;
  double cost_value = 0.;
  for (size_t iter = 0; iter < algo_config.getNMaxIterations(); ++iter) {

    if (iter == 0) {
      for (size_t k = 0; k < pop.size(); ++k) {
        cost_value = eval_SA(pop[k].getPositionVector(), cost_function)[0];
        pop[k].setCost(cost_value);
      }
    } else{
      pop.setVelocity();

      double temperature = algo_config.getTemp();
      temperature = temperature / log(1 + iter);
      size_t n_dim = pr.getNumberOfParameters();

      std::uniform_real_distribution<double> uni(0, 1);
      for (size_t i = 0; i < n_dim; ++i) {
        Particle guess = pop.createGuess(i);
        cost_value = eval_SA(guess.getPositionVector(), cost_function)[0];
        guess.setCost(cost_value);

        double deltaF =  guess.getCost() - pop[i].getCost();
        if (exp(- deltaF / temperature) > uni(gen)) {
          for (size_t j = 0; j < n_dim; ++j) {
            pop[i].setPosition(j, guess.getPosition(j));
          };
          pop[i].setCost(guess.getCost());
        };
      };
    }

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
  }

  if (pop[0].getBestCost() < minimizer.best_cost) {
    minimizer.best_cost = pop[0].getBestCost();
    minimizer.fitted_parmaters = pop[0].getBestPosition();
    minimizer.checkParameterBoundary();
  }

  S4 result("MinimizationResult");
  result.slot("algorithm")       = "SA";
  result.slot("best_cost")       = minimizer.best_cost;
  result.slot("best_parameters") = minimizer.fitted_parmaters;
  result.slot("cost_history")    = minimizer.cost_history;

  return result;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
