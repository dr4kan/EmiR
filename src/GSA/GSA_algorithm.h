#ifndef EmiR_GSA_algorithm_h
#define EmiR_GSA_algorithm_h

#include "../Base/Algorithm.h"
#include "GSAConfig.h"
#include "GSAPopulation.h"

class GSA_algorithm : public Algorithm {
public:
  GSA_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  GSAConfig m_algo_config;
  size_t m_iter;
  GSAPopulation m_population;
};

#endif
