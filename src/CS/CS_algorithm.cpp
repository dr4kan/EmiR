#include <Rcpp.h>
using namespace Rcpp;

// [[depends(RcppProgress)]]
#include <progress.hpp>
#include "CS_algorithm.h"


CS_algorithm::CS_algorithm(Function obj_function, S4 config) :
Algorithm(obj_function),
m_population(CSPopulation(obj_function)) {
  m_algo_config = CSConfig();
  m_algo_config.setNMaxIterations(config.slot("iterations"));
  m_algo_config.setPopulationSize(config.slot("population_size"));
  m_algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  m_algo_config.setPa(config.slot("discovery_rate"));
  m_algo_config.setAlpha(config.slot("step_size"));
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CS_algorithm::addPopulationPosition() {
  std::vector<double> v;
  for (size_t i = 0; i < m_population.size(); ++i) {
    v = m_population[i].getPosition();
    v.push_back(m_iter);
    m_population_position.push_back(v);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void CS_algorithm::minimize() {
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

  // Sort the population
  m_population.sort();

  // Update the cost history
  m_cost_history.push_back(m_population[0].getCost());

  // Update the population position history
  if (m_save_population) addPopulationPosition();

  int n_sc = 0;
  for (m_iter = 1; m_iter < n_iter; ++m_iter) {

    // Generate a cuckoo egg
    m_population.generateCuckooEgg();

    // Sort the population
    m_population.sort();

    // Update the cost history
    m_cost_history.push_back(m_population[0].getCost());

    // Update the population position history
    if (m_save_population) addPopulationPosition();

    // Check on same cost iterations
    if (m_iter > 0 && Utility::areEqual(m_cost_history[m_iter-1], m_cost_history[m_iter], 2)) {
      n_sc++;
    } else {
      n_sc = 0;
    }
    if (n_sc > m_algo_config.getNMaxIterationsSameCost()) break;

    // Update progress bar
    progress_bar.increment();
  }

};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


S4 CS_algorithm::getResults() {
  S4 result("MinimizationResult");
  result.slot("algorithm")       = "CS";
  result.slot("iterations")      = m_iter;
  result.slot("obj_function")    = m_obj_function;
  result.slot("best_cost")       = m_population[0].getCost();
  result.slot("best_parameters") = m_population[0].getPosition();
  result.slot("parameter_range") = m_parameter_range;
  result.slot("particles")       = m_population_position;
  result.slot("parameter_names") = m_parameter_names;
  result.slot("cost_history")    = m_cost_history;

  return result;
}
