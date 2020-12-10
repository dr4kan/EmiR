#ifndef EmiR_GAMinimization_h
#define EmiR_GAMinimization_h

#include "GAConfig.h"
#include "GAPopulation.h"
#include <functional>

class GAMinimization {
public:
  enum VerboseLevel {SILENT, LOW, HIGH};

  /// GAMinimization default constructor
  GAMinimization();

  GAConfig& algoConfig() {return m_algo_config;};

  void fit(std::function<double (double*)>);

  /// Set the range on the parameters of the model to be fitted
  void setParametersRange(const ParametersRange&);

  void print();

  std::vector<double>      cost_history;
  VerboseLevel             verbose;
  double                   best_cost;
  std::vector<double>      fitted_parmaters;
  std::vector<bool>        fit_par_boundary;

  /// Check if any parameter is at boundary
  void checkParameterBoundary();
  void checkParameterBoundary(const std::vector<double>&, int);

private:

  ParametersRange m_parameters_range;
  GAConfig        m_algo_config;
};
#endif
