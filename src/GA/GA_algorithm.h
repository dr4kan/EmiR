#ifndef EmiR_GA_algorithm_h
#define EmiR_GA_algorithm_h

#include "../Base/Algorithm.h"
#include "GAConfig.h"
#include "GAPopulation.h"

class GA_algorithm : public Algorithm {
public:
  GA_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  GAConfig m_algo_config;
  size_t m_iter;
  GAPopulation m_population;
};

#endif
