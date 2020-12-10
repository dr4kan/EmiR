#include <Rcpp.h>
using namespace Rcpp;

// [[depends(RcppProgress)]]
#include <progress.hpp>
#include "SAMinimization.h"
#include "Eval.h"

void ComputeCost(SAPopulation& pop, Function cost_function, List constraints, double penality) {
  double cost_value = 0.;
  for (size_t i = 0; i < pop.size(); ++i) {
    cost_value = Eval(pop[i].getPositionVector(), cost_function, constraints, penality);
    pop[i].setCost(cost_value);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


// [[Rcpp::export]]
S4 cstr_minimize_sa(Function cost_function, List constraints, List parameters, S4 config) {
  if (constraints.length() > 0) {
    Rcout << "Starting SA minimization...\n\n";
  } else {
    Rcout << "Starting constrained SA minimization...\n\n";
  }

  int n_iter = config.slot("iterations");
  Progress progress_bar(n_iter, true);

  int n = parameters.length();
  ParametersRange pr(n);
  std::vector<std::string> par_names;
  for (int i = 0; i < n; ++i) {
    S4 par = parameters[i];
    pr.setParameterRange(i, par.slot("name"), par.slot("min_val"), par.slot("max_val"));
    par_names.push_back(par.slot("name"));
  }

  // SA algorithm configuration
  SAConfig algo_config;
  algo_config.setNMaxIterations(n_iter);
  algo_config.setNumberOfParticles(config.slot("n_particles"));
  algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  algo_config.setCognitiveParameter(config.slot("cognitive"));
  algo_config.setSocialParameter(config.slot("social"));
  algo_config.setInertia(config.slot("dumping"));
  algo_config.setTemp(config.slot("temperature"));
  algo_config.setPenaltyParameter(config.slot("penalty_parameter"));

  double penality = config.slot("penalty_parameter");

  // Initialization of the minimizer
  SAMinimization minimizer;
  minimizer.setParametersRange(pr);
  minimizer.cost_history.clear();

  // Initialization of the population
  SAPopulation pop(algo_config, pr);

  std::random_device rd;
  std::mt19937 gen(rd());

  int n_sc = 0;
  for (size_t iter = 0; iter < n_iter; ++iter) {

    if (iter == 0) {
      ComputeCost(pop, cost_function, constraints, penality);
    } else{
      pop.setVelocity();

      double temperature = algo_config.getTemp();
      temperature = temperature / log(1 + iter);
      size_t n_dim = pr.getNumberOfParameters();

      std::uniform_real_distribution<double> uni(0, 1);
      for (size_t i = 0; i < n_dim; ++i) {
        Particle guess = pop.createGuess(i);
        guess.setCost(Eval(guess.getPositionVector(), cost_function, constraints, penality));

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

    // Update progress bar
    progress_bar.increment();
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
  result.slot("parameter_names") = par_names;
  result.slot("cost_history")    = minimizer.cost_history;

  return result;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
