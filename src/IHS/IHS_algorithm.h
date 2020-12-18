#ifndef EmiR_IHS_algorithm_h
#define EmiR_IHS_algorithm_h

#include "../Base/Algorithm.h"
#include "IHSConfig.h"
#include "IHSPopulation.h"

class IHS_algorithm : public Algorithm {
public:
  IHS_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  IHSConfig m_algo_config;
  size_t m_iter;
  IHSPopulation m_population;
};

#endif
