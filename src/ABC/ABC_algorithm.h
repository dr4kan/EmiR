#ifndef EmiR_ABC_algorithm_h
#define EmiR_ABC_algorithm_h

#include "../Base/Algorithm.h"
#include "ABCConfig.h"
#include "ABCPopulation.h"

class ABC_algorithm : public Algorithm {
public:
  ABC_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  ABCConfig m_algo_config;
  size_t m_iter;
  ABCPopulation m_population;
};

#endif
