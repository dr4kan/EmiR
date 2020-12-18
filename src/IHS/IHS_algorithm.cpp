#include <Rcpp.h>
using namespace Rcpp;

// [[depends(RcppProgress)]]
#include <progress.hpp>
#include "IHS_algorithm.h"


IHS_algorithm::IHS_algorithm(Function obj_function, S4 config) :
  Algorithm(obj_function),
  m_population(IHSPopulation(obj_function)) {
  m_algo_config = IHSConfig();
  m_algo_config.setNMaxIterations(config.slot("iterations"));
  m_algo_config.setPopulationSize(config.slot("population_size"));
  m_algo_config.setNMaxIterationsAtSameCost(config.slot("iterations_same_cost"));
  m_algo_config.setHmcr(config.slot("considering_rate"));
  m_algo_config.setParMin(config.slot("min_adjusting_rate"));
  m_algo_config.setParMax(config.slot("max_adjusting_rate"));
  m_algo_config.setBwMin(config.slot("min_distance_bandwidth"));
  m_algo_config.setBwMax(config.slot("max_distance_bandwidth"));
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void IHS_algorithm::addPopulationPosition() {
  std::vector<double> v;
  for (size_t i = 0; i < m_population.size(); ++i) {
    v = m_population[i].getPosition();
    v.push_back(m_iter);
    m_population_position.push_back(v);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void IHS_algorithm::minimize() {
  // Initialize the progress bar
  m_iter = 0;
  size_t n_iter = m_algo_config.getNMaxIterations();
  Progress progress_bar(n_iter, !m_silent);

  // Initialization of the population
  m_population.setConfig(m_algo_config);
  m_population.setParRange(m_parameters);
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
  for (m_iter = 0; m_iter < n_iter; ++m_iter) {

    // Update parameters
    m_population.updateParameters(m_iter+1);

    // Generate a new harmony
    m_population.generateNewHarmony();

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


S4 IHS_algorithm::getResults() {
  S4 result("MinimizationResult");
  result.slot("algorithm")       = "HS";
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
