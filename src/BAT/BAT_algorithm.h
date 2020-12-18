#ifndef EmiR_BAT_algorithm_h
#define EmiR_BAT_algorithm_h

#include "BATPopulation.h"

class BAT_algorithm : public Algorithm {
public:
  BAT_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  BATConfig m_algo_config;
  size_t m_iter;
  BATPopulation m_population;
};

#endif
