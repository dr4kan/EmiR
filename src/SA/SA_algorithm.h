#ifndef EmiR_SA_algorithm_h
#define EmiR_SA_algorithm_h

#include "../Base/Algorithm.h"
#include "SAConfig.h"
#include "SAPopulation.h"

class SA_algorithm : public Algorithm {
public:
  SA_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  SAConfig m_algo_config;
  size_t m_iter;
  SAPopulation m_population;
};

#endif
