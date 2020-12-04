#ifndef EmiR_PSMinimization_h
#define EmiR_PSMinimization_h

#include "PSConfig.h"
#include "PSPopulation.h"

class PSMinimization {
public:
  enum VerboseLevel {SILENT, LOW, HIGH};

  /// PSMinimization default constructor
  PSMinimization();

  PSConfig* algoConfig() {return static_cast<PSConfig*>(m_algo_config);};

  void fit(std::function<double (double*)>);

  /// Set the range on the parameters of the model to be fitted
  void setParametersRange(const ParametersRange&);

  void print();

  std::vector<double>      cost_history;
  VerboseLevel             verbose;
  double                   best_cost;
  std::vector<double>      fitted_parmaters;
  std::vector<bool>        fit_par_boundary;

private:
  /// Check if any parameter is at boundary
  void checkParameterBoundary();
  void checkParameterBoundary(const std::vector<double>&, int);

  ParametersRange          m_parameters_range;

  PSConfig *m_algo_config;
};
#endif
