#include <Rcpp.h>
using namespace Rcpp;

// [[depends(RcppProgress)]]
#include <progress.hpp>
#include "GSA_algorithm.h"


GSA_algorithm::GSA_algorithm(Function obj_function, S4 config) :
Algorithm(obj_function),
m_population(GSAPopulation(obj_function)) {
  m_algo_config = GSAConfig();
  m_algo_config.setNMaxIterations(config.slot("iterations"));
  m_algo_config.setPopulationSize(config.slot("population_size"));
  m_algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  m_algo_config.setGrav(config.slot("gravitation"));
  m_algo_config.setVmaxParameter(config.slot("velocity_max"));
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSA_algorithm::addPopulationPosition() {
  std::vector<double> v;
  for (size_t i = 0; i < m_population.size(); ++i) {
    v = m_population[i].getPosition();
    v.push_back(m_iter);
    m_population_position.push_back(v);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSA_algorithm::minimize() {
  // Initialize the progress bar
  m_iter = 0;
  size_t n_iter = m_algo_config.getNMaxIterations();
  Progress progress_bar(n_iter, !m_silent);

  // Initialization of the population
  m_population.setConfig(m_algo_config);
  m_population.setSearchSpace(m_search_space);
  m_population.setOOB(m_oob_sol);
  m_population.init();

  // Evaluate the cost for the population
  m_population.evaluate();

  // Sort the planets in the population
  m_population.firstSort();

  // Update the cost history
  m_cost_history.push_back(m_population.getBestSolution().getCost());

  // Update the population position history
  if (m_save_population) addPopulationPosition();

  int n_sc = 0;
  for (m_iter = 1; m_iter < n_iter; ++m_iter) {

    // Change the velocity of the planets and move them
    m_population.movePlanets(m_iter - 1);

    // Update the cost history
    m_cost_history.push_back(m_population.getBestSolution().getCost());

    // Update the population position history
    if (m_save_population) addPopulationPosition();

    // Check on same cost iterations
    if (m_iter > 0 && Utility::areEqual(m_cost_history[m_iter-1], m_cost_history[m_iter], 2)) {
      n_sc++;
    } else {
      n_sc = 0;
    }
    if (n_sc > (size_t)m_algo_config.getNMaxIterationsSameCost()) break;

    // Update progress bar
    progress_bar.increment();
  }

};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


S4 GSA_algorithm::getResults() {
  S4 result("MinimizationResult");
  result.slot("algorithm")       = "GSA";
  result.slot("iterations")      = m_iter;
  result.slot("obj_function")    = m_obj_function;
  result.slot("best_cost")       = m_population.getBestSolution().getCost();
  result.slot("best_parameters") = m_population.getBestSolution().getPosition();
  result.slot("parameter_range") = m_parameter_range;
  result.slot("particles")       = m_population_position;
  result.slot("parameter_names") = m_parameter_names;
  result.slot("cost_history")    = m_cost_history;

  return result;
}
