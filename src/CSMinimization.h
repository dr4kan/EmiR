#ifndef EmiR_CSMinimization_h
#define EmiR_CSMinimization_h

#include "CSConfig.h"
#include "CSPopulation.h"

class CSMinimization {
public:
  enum VerboseLevel {SILENT, LOW, HIGH};

  /// CSMinimization default constructor
  CSMinimization();

  CSConfig& algoConfig() {return m_algo_config;};

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
  CSConfig        m_algo_config;
};
#endif
