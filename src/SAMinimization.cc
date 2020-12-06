#include "SAMinimization.h"
#include <Rcpp.h>
using namespace Rcpp;

SAMinimization::SAMinimization() : verbose(SILENT) {
  m_algo_config = SAConfig();
  best_cost = std::numeric_limits<double>::max();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAMinimization::setParametersRange(const ParametersRange &t) {
  m_parameters_range = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAMinimization::checkParameterBoundary() {
  fit_par_boundary.resize(fitted_parmaters.size());
  for (size_t i = 0; i < fitted_parmaters.size(); ++i) {
    if (Utility::areEqual(fitted_parmaters[i], m_parameters_range.getParameterMin(i), 2) ||
    Utility::areEqual(fitted_parmaters[i], m_parameters_range.getParameterMax(i), 2)) {
      fit_par_boundary[i] = true;
    } else {
      fit_par_boundary[i] = false;
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAMinimization::checkParameterBoundary(const std::vector<double>&  v, int it) {
  for (size_t i = 0; i < v.size(); ++i) {
    if (Utility::areEqual(v[i], m_parameters_range.getParameterMin(i)) ||
    Utility::areEqual(v[i], m_parameters_range.getParameterMax(i))) {
      Rcout << "EmiR::Warning - Iteration #" << it << ": parameter '"
      << m_parameters_range.getParameterName(i) << "' is at boundary." << std::endl;
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAMinimization::fit(std::function<double (double*)> func) {
  cost_history.clear();
  SAPopulation pop(m_algo_config, m_parameters_range);

  int n_sc = 0;
  for (int i = 0; i < m_algo_config.getNMaxIterations(); ++i) {
    // Change the velocity of the paricles, move them and calculate the cost
    pop.moveParticles(func, i);
    // Sort the population according to the best cost
    pop.sort();
    if (cost_history.size() <= (size_t) i) cost_history.push_back(pop[0].getBestCost());

    // Check on parameters at boundary
    if (verbose > SILENT) {
      checkParameterBoundary(pop[0].getBestPosition(), i);
    }

    // Check on same cost iterations
    if (i > 0 && Utility::areEqual(cost_history[i-1], cost_history[i], 2)) {
      n_sc++;
    } else {
      n_sc = 0;
    }
    if (n_sc > m_algo_config.getNMaxIterationsSameCost()) break;
  };

  if (std::isnan(best_cost)) {
    best_cost = pop[0].getBestCost();
    fitted_parmaters = pop[0].getBestPosition();
    checkParameterBoundary();
  } else {
    if (pop[0].getBestCost() < best_cost) {
      best_cost = pop[0].getBestCost();
      fitted_parmaters = pop[0].getBestPosition();
      checkParameterBoundary();
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void SAMinimization::print() {
  // Rcout << "\n     MINIMIZER: SA\n";
  // Rcout << m_algo_config << "\n";
  // Rcout << "    PARAMETERS: " << "+" << std::string(11, '-') << "+" << std::string(15, '-') << "+" << std::string(32, '-') << "+" << "\n";
  // Rcout << std::string(16, ' ') << "| PARAMETER | FITTED VALUE  |             RANGE              |" << "\n";
  // Rcout << std::string(16, ' ') << "+" << std::string(11, '-') << "+" << std::string(15, '-') << "+" << std::string(32, '-') << "+" << "\n";
  //
  // for (size_t i = 0; i < fitted_parmaters.size(); ++i) {
  //   Rcout << std::string(16, ' ') << "|" << Utility::rightAlign(m_parameters_range.getParameterName(i), 10)
  //   << " | " << std::setw(14) << std::left << Utility::toStringScientific(fitted_parmaters[i]) << "|";
  //   Rcout << " " << std::setw(30) << std::left << m_parameters_range[i].sciPrint() << " |";
  //
  //   if (fit_par_boundary[i]) Rcout << " <- at boundary";
  //   Rcout << "\n";
  // }
  // Rcout << std::string(16, ' ') << "+" << std::string(11, '-') << "+" << std::string(15, '-') << "+" << std::string(32, '-') << "+" << "\n";
  // Rcout << "\n     BEST COST: " << Utility::toStringScientific(best_cost) << "\n\n";
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
