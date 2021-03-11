#ifndef EmiR_PS_algorithm_h
#define EmiR_PS_algorithm_h

#include "../Base/Algorithm.h"
#include "PSConfig.h"
#include "PSPopulation.h"

class PS_algorithm : public Algorithm {
public:
  PS_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  PSConfig m_algo_config;
  size_t m_iter;
  PSPopulation m_population;
};

#endif
