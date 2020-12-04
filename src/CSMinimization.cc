#include "CSMinimization.h"

CSMinimization::CSMinimization() : verbose(SILENT) {
  m_algo_config = CSConfig();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSMinimization::setParametersRange(const ParametersRange &t) {
  m_parameters_range = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSMinimization::checkParameterBoundary() {
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

void CSMinimization::checkParameterBoundary(const std::vector<double>&  v, int it) {
  for (size_t i = 0; i < v.size(); ++i) {
    if (Utility::areEqual(v[i], m_parameters_range.getParameterMin(i)) ||
    Utility::areEqual(v[i], m_parameters_range.getParameterMax(i))) {
      std::cout << "EmiR::Warning - Iteration #" << it << ": parameter '"
      << m_parameters_range.getParameterName(i) << "' is at boundary." << std::endl;
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSMinimization::fit(std::function<double (double*)> func) {
  cost_history.clear();
  CSPopulation pop(m_algo_config, m_parameters_range);

  // Compute the cost for the population
  pop.ComputeCost(func);

  // Sort the population according to the best cost
  pop.sort();

  if (cost_history.size() == 0) cost_history.push_back(pop[0].getCost());

  int n_sc = 0;
  for (int i = 1; i < m_algo_config.getNMaxIterations(); ++i) {
    pop.newNest();
    pop.ComputeCost(func);
    pop.sort();
    pop.mutation();
    pop.ComputeCost(func);
    pop.sort();
    if (cost_history.size() <= (size_t) i) cost_history.push_back(pop[0].getCost());

    // Check on parameters at boundary
    if (verbose > SILENT) {
      checkParameterBoundary(pop[0].getEggs(), i);
    }

    // Check on same cost iterations
    if (Utility::areEqual(cost_history[i-1], cost_history[i], 2)) {
      n_sc++;
    } else {
      n_sc = 0;
    }
    if (n_sc > m_algo_config.getNMaxIterationsSameCost()) break;
  }

  if (std::isnan(best_cost)) {
    best_cost = pop[0].getCost();
    fitted_parmaters = pop[0].getEggs();
    checkParameterBoundary();
  } else {
    if (pop[0].getCost() < best_cost) {
      best_cost = pop[0].getCost();
      fitted_parmaters = pop[0].getEggs();
      checkParameterBoundary();
    }
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSMinimization::print() {
  std::cout << "\n     MINIMIZER: CS\n";
  std::cout << m_algo_config << "\n";
  std::cout << "    PARAMETERS: " << "+" << std::string(11, '-') << "+" << std::string(15, '-') << "+" << std::string(32, '-') << "+" << "\n";
  std::cout << std::string(16, ' ') << "| PARAMETER | FITTED VALUE  |             RANGE              |" << "\n";
  std::cout << std::string(16, ' ') << "+" << std::string(11, '-') << "+" << std::string(15, '-') << "+" << std::string(32, '-') << "+" << "\n";

  for (size_t i = 0; i < fitted_parmaters.size(); ++i) {
    std::cout << std::string(16, ' ') << "|" << Utility::rightAlign(m_parameters_range.getParameterName(i), 10)
    << " | " << std::setw(14) << std::left << Utility::toStringScientific(fitted_parmaters[i]) << "|";
    std::cout << " " << std::setw(30) << std::left << m_parameters_range[i].sciPrint() << " |";

    if (fit_par_boundary[i]) std::cout << " <- at boundary";
    std::cout << "\n";
  }
  std::cout << std::string(16, ' ') << "+" << std::string(11, '-') << "+" << std::string(15, '-') << "+" << std::string(32, '-') << "+" << "\n";
  std::cout << "\n     BEST COST: " << Utility::toStringScientific(best_cost) << "\n\n";
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
